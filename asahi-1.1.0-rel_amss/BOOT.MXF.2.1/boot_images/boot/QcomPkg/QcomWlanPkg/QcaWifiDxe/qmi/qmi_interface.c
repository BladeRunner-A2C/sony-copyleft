/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */
 
// SPDX-License-Identifier: ISC
/*
 * Copyright (C) 2017 Linaro Ltd.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 19/10/21  zxue     bypass the qrtr
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <qdf/qbase.h>
#include <qdf/idr.h>
#include <qdf/pr_debug.h>
#include "qmi.h"

/**
 * qmi_recv_new_server() - handler of NEW_SERVER control message
 * @qmi:	qmi handle
 * @service:	service id of the new server
 * @instance:	instance id of the new server
 * @node:	node of the new server
 * @port:	port of the new server
 *
 * Calls the new_server callback to inform the client about a newly registered
 * server matching the currently registered service lookup.
 */
static void qmi_recv_new_server(struct qmi_handle *qmi,
				unsigned int service, unsigned int instance,
				unsigned int node, unsigned int port)
{
	struct qmi_ops *ops = &qmi->ops;
	struct qmi_service *svc;
	int ret;

	if (!ops->new_server)
		return;

	/* Ignore EOF marker */
	if (!node && !port)
		return;

	svc = kzalloc(sizeof(*svc), GFP_KERNEL);
	if (!svc)
		return;

    pr_debug("received new server [%d:%x]\n", service, instance);

	svc->service = service;
	svc->version = instance & 0xff;
	svc->instance = instance >> 8;
	svc->node = node;
	svc->port = port;

	ret = ops->new_server(qmi, svc);
	if (ret < 0)
		kfree(svc);
	else
		list_add_tail(&svc->list_node, &qmi->lookup_results);
}

/**
 * qmi_recv_del_server() - handler of DEL_SERVER control message
 * @qmi:	qmi handle
 * @node:	node of the dying server, a value of -1 matches all nodes
 * @port:	port of the dying server, a value of -1 matches all ports
 *
 * Calls the del_server callback for each previously seen server, allowing the
 * client to react to the disappearing server.
 */
static void qmi_recv_del_server(struct qmi_handle *qmi,
				unsigned int node, unsigned int port)
{
	struct qmi_ops *ops = &qmi->ops;
	struct qmi_service *svc;
	struct qmi_service *tmp;

	list_for_each_entry_safe(svc, tmp, &qmi->lookup_results, struct qmi_service, list_node) {
		if (node != -1 && svc->node != node)
			continue;
		if (port != -1 && svc->port != port)
			continue;

		if (ops->del_server)
			ops->del_server(qmi, svc);

		list_del(&svc->list_node);
		kfree(svc);
	}
}

/**
 * qmi_recv_bye() - handler of BYE control message
 * @qmi:	qmi handle
 * @node:	id of the dying node
 *
 * Signals the client that all previously registered services on this node are
 * now gone and then calls the bye callback to allow the client client further
 * cleaning up resources associated with this remote.
 */
static void qmi_recv_bye(struct qmi_handle *qmi,
			 unsigned int node)
{
	struct qmi_ops *ops = &qmi->ops;

	qmi_recv_del_server(qmi, node, 0xFFFFFFFF/*-1*/);

	if (ops->bye)
		ops->bye(qmi, node);
}

/**
 * qmi_recv_del_client() - handler of DEL_CLIENT control message
 * @qmi:	qmi handle
 * @node:	node of the dying client
 * @port:	port of the dying client
 *
 * Signals the client about a dying client, by calling the del_client callback.
 */
static void qmi_recv_del_client(struct qmi_handle *qmi,
				unsigned int node, unsigned int port)
{
	struct qmi_ops *ops = &qmi->ops;

	if (ops->del_client)
		ops->del_client(qmi, node, port);
}

static int qmi_recv_hello(u32 src_proc_id, u32 src_port_id)
{
	int ret;
	struct ipcr_ctrl_pkt pkt;
	struct ipcr_addr_v1 to, from;

	to.proc_id = src_proc_id;
	to.port_id = IPCR_PORT_CTRL;

	from.proc_id = IPCR_PROC_LOCAL;
	from.port_id = IPCR_PORT_CTRL;


	memset(&pkt, 0, sizeof(pkt));
	pkt.cmd = cpu_to_le32(IPCR_CONTROL_HELLO);

	ret = qcom_mhi_ipcr_sendmsg(&pkt, sizeof(pkt), IPCR_CONTROL_HELLO, &to, &from);
	if (ret < 0)
		pr_err("failed to send hello msg\n");

	return ret;
}

static void qmi_recv_ctrl_pkt(struct qmi_handle *qmi,
			      const void *buf, size_t len)
{
	const struct ipcr_ctrl_pkt *pkt = buf;
	if (len < sizeof(struct ipcr_ctrl_pkt)) {
		pr_debug("ignoring short control packet\n");
		return;
	}

	switch (le32_to_cpu(pkt->cmd)) {
	case IPCR_CONTROL_HELLO:
		qmi_recv_hello(le32_to_cpu(pkt->u.server.addr.proc_id),
			       le32_to_cpu(pkt->u.server.addr.port_id));
		break;
	case IPCR_CONTROL_BYE:
		qmi_recv_bye(qmi, le32_to_cpu(pkt->u.client.addr.proc_id));
 		break;
	case IPCR_CONTROL_NEW_SERVER:
		qmi_recv_new_server(qmi,
					le32_to_cpu(pkt->u.server.service_id),
					le32_to_cpu(pkt->u.server.instance_id),
					le32_to_cpu(pkt->u.server.addr.proc_id),
					le32_to_cpu(pkt->u.server.addr.port_id));
		break;
	case IPCR_CONTROL_DEL_SERVER:
		qmi_recv_del_server(qmi,
				    le32_to_cpu(pkt->u.server.addr.proc_id),
				    le32_to_cpu(pkt->u.server.addr.port_id));
		break;
	case IPCR_CONTROL_DEL_CLIENT:
		qmi_recv_del_client(qmi,
				    le32_to_cpu(pkt->u.client.addr.proc_id),
				    le32_to_cpu(pkt->u.client.addr.port_id));
		break;
	}
}

/**
 * qmi_add_lookup() - register a new lookup with the name service
 * @qmi:	qmi handle
 * @service:	service id of the request
 * @instance:	instance id of the request
 * @version:	version number of the request
 *
 * Registering a lookup query with the name server will cause the name server
 * to send NEW_SERVER and DEL_SERVER control messages to this socket as
 * matching services are registered.
 *
 * Return: 0 on success, negative errno on failure.
 */
int qmi_add_lookup(struct qmi_handle *qmi, unsigned int service,
 		   unsigned int version, unsigned int instance)
{
 	return 0;
 }
EXPORT_SYMBOL(qmi_add_lookup);

/**
 * qmi_add_server() - register a service with the name service
 * @qmi:	qmi handle
 * @service:	type of the service
 * @instance:	instance of the service
 * @version:	version of the service
 *
 * Register a new service with the name service. This allows clients to find
 * and start sending messages to the client associated with @qmi.
 *
 * Return: 0 on success, negative errno on failure.
 */
int qmi_add_server(struct qmi_handle *qmi, unsigned int service,
		   unsigned int version, unsigned int instance)
{
	return 0;
}
EXPORT_SYMBOL(qmi_add_server);

/**
 * qmi_txn_init() - allocate transaction id within the given QMI handle
 * @qmi:	QMI handle
 * @txn:	transaction context
 * @ei:		description of how to decode a matching response (optional)
 * @c_struct:	pointer to the object to decode the response into (optional)
 *
 * This allocates a transaction id within the QMI handle. If @ei and @c_struct
 * are specified any responses to this transaction will be decoded as described
 * by @ei into @c_struct.
 *
 * A client calling qmi_txn_init() must call either qmi_txn_wait() or
 * qmi_txn_cancel() to free up the allocated resources.
 *
 * Return: Transaction id on success, negative errno on failure.
 */
int qmi_txn_init(struct qmi_handle *qmi, struct qmi_txn *txn,
		 struct qmi_elem_info *ei, void *c_struct)
{
	int ret;

	memset(txn, 0, sizeof(*txn));

	mutex_init(&txn->lock);
	init_completion(&txn->completion);
	txn->qmi = qmi;
	txn->ei = ei;
	txn->dest = c_struct;

    pr_debug("txn->dest=0x%p, txn->ei=0x%p\n", txn->dest, txn->ei);

	mutex_lock(&qmi->txn_lock);
	ret = idr_alloc_cyclic(&qmi->txns, txn, 0, 0xFFFF/*U16_MAX*/);
	if (ret < 0)
		pr_err("failed to allocate transaction id\n");

	txn->id = (u16)ret;
	mutex_unlock(&qmi->txn_lock);

	return ret;
}
EXPORT_SYMBOL(qmi_txn_init);

/**
 * qmi_txn_wait() - wait for a response on a transaction
 * @txn:	transaction handle
 * @timeout:	timeout, in jiffies
 *
 * If the transaction is decoded by the means of @ei and @c_struct the return
 * value will be the returned value of qmi_decode_message(), otherwise it's up
 * to the specified message handler to fill out the result.
 *
 * Return: the transaction response on success, negative errno on failure.
 */
int qmi_txn_wait(struct qmi_txn *txn, unsigned long timeout)
{
	struct qmi_handle *qmi = txn->qmi;
	unsigned long time_left;

	time_left = wait_for_completion_timeout(&txn->completion, timeout);

	mutex_lock(&qmi->txn_lock);
	mutex_lock(&txn->lock);
	idr_remove(&qmi->txns, txn->id);
	mutex_unlock(&txn->lock);
	mutex_unlock(&qmi->txn_lock);

	if (!time_left)
		return -ETIMEDOUT;
	else
		return txn->result;
}
EXPORT_SYMBOL(qmi_txn_wait);

/**
 * qmi_txn_cancel() - cancel an ongoing transaction
 * @txn:	transaction id
 */
void qmi_txn_cancel(struct qmi_txn *txn)
{
	struct qmi_handle *qmi = txn->qmi;

	mutex_lock(&qmi->txn_lock);
	mutex_lock(&txn->lock);
	idr_remove(&qmi->txns, txn->id);
	mutex_unlock(&txn->lock);
	mutex_unlock(&qmi->txn_lock);
}
EXPORT_SYMBOL(qmi_txn_cancel);

/**
 * qmi_invoke_handler() - find and invoke a handler for a message
 * @qmi:	qmi handle
 * @sq:		sockaddr of the sender
 * @txn:	transaction object for the message
 * @buf:	buffer containing the message
 * @len:	length of @buf
 *
 * Find handler and invoke handler for the incoming message.
 */
static void qmi_invoke_handler(struct qmi_handle *qmi,
			       struct qmi_txn *txn, const void *buf, size_t len)
{
	const struct qmi_msg_handler *handler;
	const struct qmi_header *hdr = buf;
	void *dest;
	int ret;

	if (!qmi->handlers)
		return;

	for (handler = qmi->handlers; handler->fn; handler++) {
		if (handler->type == hdr->type &&
		    handler->msg_id == hdr->msg_id)
			break;
	}

	if (!handler->fn)
		return;

	dest = kzalloc(handler->decoded_size, GFP_KERNEL);
	if (!dest)
		return;

	ret = qmi_decode_message(buf, len, handler->ei, dest);
	if (ret < 0)
		pr_err("failed to decode incoming message\n");
	else
		handler->fn(qmi, txn, dest);

	kfree(dest);
}

static void qmi_handle_message(struct qmi_handle *qmi,
			       const void *buf, size_t len)
{
	const struct qmi_header *hdr;
	struct qmi_txn tmp_txn;
	struct qmi_txn *txn = NULL;
	int ret;

	if (len < sizeof(*hdr)) {
		pr_err("ignoring short QMI packet\n");
		return;
	}

	hdr = buf;

    pr_debug("type=%u\n", hdr->type);

	/* If this is a response, find the matching transaction handle */
	if (hdr->type == QMI_RESPONSE) {
		mutex_lock(&qmi->txn_lock);
		txn = idr_find(&qmi->txns, hdr->txn_id);

		/* Ignore unexpected responses */
		if (!txn) {
			mutex_unlock(&qmi->txn_lock);
			return;
		}

		mutex_lock(&txn->lock);
		mutex_unlock(&qmi->txn_lock);

        pr_debug("txn->dest=0x%p, txn->ei=0x%p\n", 
            txn->dest, txn->ei);

		if (txn->dest && txn->ei) {
			ret = qmi_decode_message(buf, len, txn->ei, txn->dest);
			if (ret < 0)
				pr_err("failed to decode incoming message\n");

			txn->result = ret;
			complete(&txn->completion);
		} else  {
			qmi_invoke_handler(qmi, txn, buf, len);
		}

		mutex_unlock(&txn->lock);
	} else {
		/* Create a txn based on the txn_id of the incoming message */
		memset(&tmp_txn, 0, sizeof(tmp_txn));
		tmp_txn.id = hdr->txn_id;

		qmi_invoke_handler(qmi, &tmp_txn, buf, len);
	}
}

static void qmi_data_ready_work(void *context)
{
	struct qmi_handle *qmi = (struct qmi_handle *)context;
	struct qmi_ops *ops = &qmi->ops;
	struct ipcr_cb *cb;
	struct sk_buff *skb;
	
	while ((skb = skb_dequeue(&qmi->queue)) != NULL) {
		cb = (struct ipcr_cb *)skb->cb;
		
		memcpy(qmi->recv_buf, skb->data, skb->len);
	
		if (cb->dst_port_id == IPCR_PORT_CTRL) {
			qmi_recv_ctrl_pkt(qmi, qmi->recv_buf, skb->len);
		} else if (ops->msg_handler) {
			ops->msg_handler(qmi, qmi->recv_buf, skb->len);
		} else {
			qmi_handle_message(qmi, qmi->recv_buf, skb->len);
		}

		consume_skb(skb);
	}
}

static int qmi_enqueue_skb(struct sk_buff *skb, void *data)
{
    struct qmi_handle *qmi = (struct qmi_handle *)data;
	skb_queue_tail(&qmi->queue, skb);

	schedule_work(&qmi->work);

	return 0;
}

/**
 * qmi_handle_init() - initialize a QMI client handle
 * @qmi:	QMI handle to initialize
 * @recv_buf_size: maximum size of incoming message
 * @ops:	reference to callbacks for IPCR notifications
 * @handlers:	NULL-terminated list of QMI message handlers
 *
 * This initializes the QMI client handle to allow sending and receiving QMI
 * messages. As messages are received the appropriate handler will be invoked.
 *
 * Return: 0 on success, negative errno on failure.
 */
int qmi_handle_init(struct qmi_handle *qmi, size_t recv_buf_size,
		    const struct qmi_ops *ops,
		    const struct qmi_msg_handler *handlers)
{
	mutex_init(&qmi->txn_lock);
	
	idr_init(&qmi->txns);

	list_init_head(&qmi->lookups);
    list_init_head(&qmi->lookup_results);
    list_init_head(&qmi->services);

	init_work(&qmi->work, qmi_data_ready_work, qmi);

	skb_queue_head_init(&qmi->queue);

	qmi->handlers = handlers;
	if (ops)
		qmi->ops = *ops;

	/* Make room for the header */
	recv_buf_size += sizeof(struct qmi_header);
	/* Must also be sufficient to hold a control packet */
	if (recv_buf_size < sizeof(struct ipcr_ctrl_pkt))
		recv_buf_size = sizeof(struct ipcr_ctrl_pkt);

	qmi->recv_buf_size = recv_buf_size;
	qmi->recv_buf = kzalloc(recv_buf_size, GFP_KERNEL);
	if (!qmi->recv_buf)
		return -ENOMEM;

	qcom_mhi_interface_init(qmi_enqueue_skb, qmi);

	return 0;
}
EXPORT_SYMBOL(qmi_handle_init);

/**
 * qmi_handle_release() - release the QMI client handle
 * @qmi:	QMI client handle
 *
 * This closes the underlying socket and stops any handling of QMI messages.
 */
void qmi_handle_release(struct qmi_handle *qmi)
{
	struct qmi_service *svc, *tmp;

	cancel_work_sync(&qmi->work);

	qmi_recv_del_server(qmi, 0xFFFFFFFF/*-1*/, 0xFFFFFFFF/*-1*/);

	//destroy_workqueue(qmi->wq);

	idr_destroy(&qmi->txns);

	kfree(qmi->recv_buf);

	/* Free registered lookup requests */
	list_for_each_entry_safe(svc, tmp, &qmi->lookups, struct qmi_service, list_node) {
		list_del(&svc->list_node);
		kfree(svc);
	}

	/* Free registered service information */
	list_for_each_entry_safe(svc, tmp, &qmi->services, struct qmi_service, list_node) {
		list_del(&svc->list_node);
		kfree(svc);
	}
}
EXPORT_SYMBOL(qmi_handle_release);

/**
 * qmi_send_message() - send a QMI message
 * @qmi:	QMI client handle
 * @txn:	transaction object to use for the message
 * @type:	type of message to send
 * @msg_id:	message id
 * @len:	max length of the QMI message
 * @ei:		QMI message description
 * @c_struct:	object to be encoded
 *
 * This function encodes @c_struct using @ei into a message of type @type,
 * with @msg_id and @txn into a buffer of maximum size @len, and sends this to
 * @sq.
 *
 * Return: 0 on success, negative errno on failure.
 */
static int qmi_send_message(struct qmi_handle *qmi,
				struct qmi_txn *txn,
				int type, int msg_id, size_t len,
				struct qmi_elem_info *ei, const void *c_struct)
{
	void *msg;
	int ret;
	struct ipcr_addr_v1 to, from;

	to.proc_id = qmi->server.addr.proc_id;
	to.port_id = qmi->server.addr.port_id;;

	from.proc_id = IPCR_PROC_LOCAL;
	from.port_id = IPCR_PORT_DATA;

	msg = qmi_encode_message(type,
				 msg_id, &len,
				 txn->id, ei,
				 c_struct);
	if (IS_ERR(msg))
		return PTR_ERR(msg);

	ret = qcom_mhi_ipcr_sendmsg(msg, (int)len, IPCR_CONTROL_DATA, &to, &from);

	kfree(msg);

	return ret < 0 ? ret : 0;
}

/**
 * qmi_send_request() - send a request QMI message
 * @qmi:	QMI client handle
 * @txn:	transaction object to use for the message
 * @msg_id:	message id
 * @len:	max length of the QMI message
 * @ei:		QMI message description
 * @c_struct:	object to be encoded
 *
 * Return: 0 on success, negative errno on failure.
 */
int qmi_send_request(struct qmi_handle *qmi,
			 struct qmi_txn *txn, int msg_id, size_t len,
			 struct qmi_elem_info *ei, const void *c_struct)
{
    pr_debug("msg_id 0x%x, len=%u\n", msg_id, len);

	return qmi_send_message(qmi, txn, QMI_REQUEST, msg_id, len, ei,
				c_struct);
}
EXPORT_SYMBOL(qmi_send_request);

