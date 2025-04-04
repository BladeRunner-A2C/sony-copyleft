/*
** Copyright 2023 Sony Corporation
*
* R8168 sony extension driver
*  dummy net device for eth0
*/

#include <linux/module.h>
#include <linux/version.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>


#define SLOGD(format, arg...)           \
    do { \
        printk("D r8168dmy:(%3s,%5d) %s.%4d: " format, \
               (in_interrupt()!=0)? "int":"pid", current->pid, __func__, __LINE__, ##arg); \
    } while (0)


static int r8168_s_dmy_eth_open(struct net_device *ndev)
{
	SLOGD("dev=%p\n",ndev);
	return 0;
}

static int r8168_s_dmy_eth_stop(struct net_device *ndev)
{
	SLOGD("dev=%p\n",ndev);
	netif_stop_queue(ndev);
	return 0;
}

static int r8168_s_dmy_eth_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	SLOGD("dev=%p\n",ndev);
	dev_kfree_skb(skb);
	return NETDEV_TX_OK ;
}

static int r8168_s_dmy_eth_init(struct net_device *ndev)
{
	SLOGD("dev=%p\n",ndev);
	return 0;
}

static const struct net_device_ops dmy_netdev_ops = {
	.ndo_init = r8168_s_dmy_eth_init,
	.ndo_open = r8168_s_dmy_eth_open,
	.ndo_stop = r8168_s_dmy_eth_stop,
	.ndo_start_xmit = r8168_s_dmy_eth_xmit,
	.ndo_validate_addr = eth_validate_addr,
};

struct net_device *r8168_s_dmy_eth_register(void)
{
	int ret;
	struct net_device *dmy_ndev;

	/* create net_device eth as dummy */
	dmy_ndev = alloc_etherdev(sizeof(struct net_device));
	if (!dmy_ndev) {
		pr_err("%s: failed to alloc_etehrdev\n", __func__);
		goto end;
	}

	/* setup netdev ops */
	dmy_ndev->netdev_ops = &dmy_netdev_ops ;

	/* register the net_device object */
	ret = register_netdev(dmy_ndev);
	if(ret) {
		pr_err("%s: failed to register_netdev ret=%d\n", __func__, ret);
		free_netdev(dmy_ndev);
		dmy_ndev = NULL;
	}

	SLOGD("dmy_ndev=%p\n", dmy_ndev);
 end:
	return dmy_ndev;
}

void r8168_s_dmy_eth_unregister(struct net_device *ndev)
{
	SLOGD("dmy_ndev=%p\n", ndev);
	unregister_netdev(ndev);
	free_netdev(ndev);
	return;
}
