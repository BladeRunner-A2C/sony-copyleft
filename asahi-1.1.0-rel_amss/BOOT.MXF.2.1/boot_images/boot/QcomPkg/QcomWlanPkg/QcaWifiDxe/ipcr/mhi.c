/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

// SPDX-License-Identifier: ISC
/*
 * Copyright(c) 2018-2020 The Linux Foundation.All rights reserved.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 21/12/21  zxue     refine code
 19/10/21  zxue     new file to bypass the qrtr

=============================================================================*/

#include <qdf/wait.h>
#include <qdf/sock.h>
#include <qdf/kref.h>
#include <qdf/sk_buff.h>
#include <ipcr/ipcr.h>
#include <mhi/mhi.h>

#define IPCR_V1 1
#define IPCR_V2 3

#pragma pack(1)
struct ipcr_v1_header {
    u32 ver;
	u32 pkt_type;
	struct ipcr_addr_v1 src;
	u32 ack_rx;
	u32 size;
	struct ipcr_addr_v1 dst;
} __packed;

struct ipcr_v2_header {
	u8 ver;
	u8 pkt_type;
	u8 flags;
	u8 optlen;
	u32 size;
	struct ipcr_addr_v2 src;
	struct ipcr_addr_v2 dst;
};
#pragma pack()

#define IPCR_FLAGS_ACK_RX	BIT(0)
#define IPCR_HDR_ROOM max_t(size_t, sizeof(struct ipcr_v1_header), \
					sizeof(struct ipcr_v2_header))

struct ipcr_mhi_dev {
	struct mhi_device *mhi_dev;
};

/* From MHI to QRTR */

static struct {
    atomic_t initialized;

    void *cntrl_dev;
    struct ipcr_mhi_dev *ipcr_dev;

    int(*enqueue_skb)(struct sk_buff *, void *);
    void *priv;
} ipcr;

void qcom_mhi_interface_init(int (*fn)(struct sk_buff *, void *), void *data)
{
	ipcr.enqueue_skb = fn;
	ipcr.priv = data;
}

EXPORT_SYMBOL(qcom_mhi_interface_init);

static void qcom_mhi_tx_resume(struct sk_buff *skb)
{
	consume_skb(skb);
}

static int qcom_mhi_ipcr_send_resume_tx(struct ipcr_cb *cb)
{
	int ret;
	struct ipcr_ctrl_pkt pkt;
	struct ipcr_addr_v1 to, from;

	to.proc_id = cb->src_proc_id;
	to.port_id = cb->src_port_id;

	from.proc_id = IPCR_PROC_LOCAL;
	from.port_id = IPCR_PORT_DATA;
	
	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = cpu_to_le32(IPCR_CONTROL_RESUME_TX);
	pkt.u.client.addr.proc_id = cpu_to_le32(IPCR_PROC_LOCAL);
	pkt.u.client.addr.port_id = cpu_to_le32(IPCR_PORT_DATA);

	ret = qcom_mhi_ipcr_sendmsg(&pkt, sizeof(pkt), IPCR_CONTROL_RESUME_TX, &to, &from);
	if (ret < 0)
		pr_err("failed to send resume tx  msg\n");

	return ret;
}

static int qcom_mhi_post(const void *data, size_t len)
{
	const struct ipcr_v1_header *v1;
	const struct ipcr_v2_header *v2;
	struct sk_buff *skb;
	struct ipcr_cb *cb;
	unsigned int size;
	unsigned int ver;
	size_t hdrlen;

	if (len == 0 || len & 3)
		return -EINVAL;

	skb = alloc_skb((u32)len);
	if (!skb)
		return -ENOMEM;

	cb = (struct ipcr_cb *)skb->cb;

	ver = *(u8*)data;

	switch (ver) {
	case IPCR_V1:
		if (len < sizeof(*v1))
			goto err;
		
		v1 = data;
		hdrlen = sizeof(*v1);

		cb->pkt_type = (u8)le32_to_cpu(v1->pkt_type);
		cb->src_proc_id = le32_to_cpu(v1->src.proc_id);
		cb->src_port_id = le32_to_cpu(v1->src.port_id);
		cb->ack_rx = !!v1->ack_rx;
		cb->dst_proc_id = le32_to_cpu(v1->dst.proc_id);
		cb->dst_port_id = le32_to_cpu(v1->dst.port_id);

		size = le32_to_cpu(v1->size);
		break;
	case IPCR_V2:
		if (len < sizeof(*v2))
			goto err;
		v2 = data;
		hdrlen = sizeof(*v2) + v2->optlen;

		cb->pkt_type = v2->pkt_type;
		cb->ack_rx = !!(v2->flags & IPCR_FLAGS_ACK_RX);
		cb->src_proc_id = le16_to_cpu(v2->src.proc_id);
		cb->src_port_id = le16_to_cpu(v2->src.port_id);
		cb->dst_proc_id = le16_to_cpu(v2->dst.proc_id);
		cb->dst_port_id = le16_to_cpu(v2->dst.port_id);

		if (cb->src_port_id == IPCR_PORT_CTRL)
			cb->src_port_id = IPCR_PORT_CTRL;
		if (cb->dst_port_id == IPCR_PORT_CTRL)
			cb->dst_port_id = IPCR_PORT_CTRL;

		size = le32_to_cpu(v2->size);
		break;
	default:
		pr_err("ipcr: Invalid version %d\n", ver);
		goto err;
	}

	if (len != ALIGN(size, 4) + hdrlen)
		goto err;

	if (cb->dst_port_id != IPCR_PORT_CTRL && cb->pkt_type != IPCR_CONTROL_DATA &&
	    cb->pkt_type != IPCR_CONTROL_RESUME_TX)
		goto err;

	if(cb->ack_rx)
		qcom_mhi_ipcr_send_resume_tx(cb);
		
	skb_put_data(skb, (u8*)data + hdrlen, size);

	if (cb->pkt_type == IPCR_CONTROL_RESUME_TX) {
		qcom_mhi_tx_resume(skb);
	} else {
		if(!ipcr.enqueue_skb)
			goto err;
		
		if (ipcr.enqueue_skb(skb, ipcr.priv))
			goto err;
	}

	return 0;

err:
	kfree_skb(skb);
	return -EINVAL;

}

static void qcom_mhi_ipcr_dl_callback(struct mhi_device *mhi_dev,
				      struct mhi_result *mhi_res)
{
    struct ipcr_mhi_dev *ipcr_dev = mhi_dev->driver_data;
	int rc;

	if (!ipcr_dev || mhi_res->transaction_status)
		return;

    mhi_dbg("received a packet: buf_addr=0x%p, bytes_xfered=%u\n", 
        mhi_res->buf_addr, mhi_res->bytes_xferd);

	rc = qcom_mhi_post(mhi_res->buf_addr, mhi_res->bytes_xferd);
	if (rc == -EINVAL)
		mhi_err("invalid ipcrouter packet\n");
}

/* From QRTR to MHI */
static void qcom_mhi_ipcr_ul_callback(struct mhi_device *mhi_dev,
				      struct mhi_result *mhi_res)
{
	struct sk_buff *skb = mhi_res->buf_addr;

	if (skb->sk)
		sock_put(skb->sk);
	consume_skb(skb);
}

/* Send data over MHI */
static int qcom_mhi_ipcr_send(struct sk_buff *skb)
{
	//struct qrtr_mhi_dev *qdev = container_of(ep, struct qrtr_mhi_dev, ep);
	int rc;

	rc = skb_linearize(skb);
	if (rc)
		goto free_skb;

	rc = mhi_queue_skb(ipcr.ipcr_dev->mhi_dev, DMA_TO_DEVICE, skb, skb->len,
			   MHI_EOT);
	if (rc)
		goto free_skb;

	if (skb->sk)
		sock_hold(skb->sk);

	return rc;

free_skb:
	kfree_skb(skb);

	return rc;
}


static int qcom_mhi_ipcr_tx_wait(u32 type)
{
	static u32 cnt = 0;
	if(type != IPCR_CONTROL_DATA)
		return 0;
	
	cnt++;
	if(cnt == 5) {
		cnt = 0;
		return 1;
	}

	return 0;
}

static int qcom_mhi_tx_ipcr_flow_failed(void)
{
	return 0;
}

int qcom_mhi_ipcr_sendmsg(void *pkt, int len, u32 type, struct ipcr_addr_v1 *to, struct ipcr_addr_v1 *from)
{
	struct sk_buff *skb;
	size_t plen;
	struct ipcr_v1_header *hdr;
	int rc, ack_rx;
	size_t pktlen;

	if (len > 65535)
		return -EMSGSIZE;

	plen = (len + 3) & ~3;
	skb = dev_alloc_skb(ipcr.cntrl_dev, (u32)(plen + IPCR_HDR_ROOM));
	if(!skb)
		return -ENOMEM;
	
	skb_reserve(skb, IPCR_HDR_ROOM);
	skb_put_data(skb, pkt, len);
	pktlen = skb->len;

	ack_rx = qcom_mhi_ipcr_tx_wait(type);
	if (ack_rx < 0) {
		kfree_skb(skb);
		return ack_rx;
	}

	hdr = skb_push(skb, sizeof(*hdr));
	hdr->ver = cpu_to_le32(IPCR_V1);
	hdr->pkt_type = cpu_to_le32(type);
	hdr->src.proc_id = cpu_to_le32(from->proc_id);
	hdr->src.port_id = cpu_to_le32(from->port_id);

	hdr->dst.proc_id = cpu_to_le32(to->proc_id);
	hdr->dst.port_id = cpu_to_le32(to->port_id);


	hdr->size = cpu_to_le32(pktlen);
	hdr->ack_rx = !!ack_rx;

	rc = skb_put_padto(skb, ALIGN(pktlen, 4) + sizeof(*hdr));
	if (rc)
		return rc;

	rc = qcom_mhi_ipcr_send(skb);
	if (rc && ack_rx)
		qcom_mhi_tx_ipcr_flow_failed();

	return rc;
}
EXPORT_SYMBOL(qcom_mhi_ipcr_sendmsg);

static int qcom_mhi_ipcr_probe(
    struct mhi_device *mhi_dev, 
    const struct mhi_device_id *id)
{
    struct ipcr_mhi_dev *ipcr_dev;
	int rc;

	ipcr_dev = kzalloc(sizeof(*ipcr_dev), GFP_KERNEL);
	if (!ipcr_dev)
		return -ENOMEM;

	ipcr_dev->mhi_dev = mhi_dev;

    mhi_dev->driver_data = ipcr_dev;
	rc = mhi_prepare_for_transfer(mhi_dev);
    if (rc) {
        mhi_dbg("Mhi prepare for transfer fail rc=%d\n", rc);
        return rc;
    }

    /* register */
    ipcr.ipcr_dev = ipcr_dev;

	mhi_dbg("Qualcomm MHI IPCR driver probed\n");

	return 0;
}

static void qcom_mhi_ipcr_remove(struct mhi_device *mhi_dev)
{
    struct ipcr_mhi_dev *ipcr_dev = mhi_dev->driver_data;

    mhi_unprepare_from_transfer(mhi_dev);

    /* unregister */
    if (ipcr.ipcr_dev == ipcr_dev) {
        ipcr.ipcr_dev = NULL;
    }

    kfree(ipcr_dev);
    mhi_dev->driver_data = NULL;
}

static const struct mhi_device_id qcom_mhi_ipcr_id_table[] = {
	{ .chan = "IPCR" },
	{ .chan = 0 }
};

struct mhi_driver qcom_mhi_qrtr_driver = {
    .name = "qcom_mhi_ipcr",
	.probe = qcom_mhi_ipcr_probe,
	.remove = qcom_mhi_ipcr_remove,
	.dl_xfer_cb = qcom_mhi_ipcr_dl_callback,
	.ul_xfer_cb = qcom_mhi_ipcr_ul_callback,
	.id_table = qcom_mhi_ipcr_id_table,
};

/* module initialize and uninitialize */
int ipcr_init(void *cntrl_dev)
{
    /* initialize the global variables */
    if (atomic_cmpxchg(&ipcr.initialized, 0, 1))
        return 0;

    mhi_dbg("initialize IPCR\n");

    ipcr.cntrl_dev = cntrl_dev;

    return 0;
}

void ipcr_fini(void)
{
    if (!atomic_cmpxchg(&ipcr.initialized, 1, 0))
        return;
}