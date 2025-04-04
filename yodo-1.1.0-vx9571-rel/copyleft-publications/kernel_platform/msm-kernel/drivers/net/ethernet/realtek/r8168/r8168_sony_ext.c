/*
** Copyright 2023 Sony Corporation
*
* R8168 sony extension driver
*
*/

#include <linux/module.h>
#include <linux/version.h>
#include <linux/pci.h>
#include <linux/proc_fs.h>
#include <linux/interrupt.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/netdevice.h>
#include <linux/pm_wakeup.h>
#include <linux/pm_runtime.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>

#include <linux/msm_pcie.h>

#include "r8168.h"

#define SLOGI(format, arg...)           \
    do { \
        printk("I r8168s:%s: " format, __func__, ##arg); \
    } while (0)


#define SLOGD(format, arg...)           \
    do { \
        printk("D r8168s:(%3s,%5d) %s.%4d: " format, \
               (in_interrupt()!=0)? "int":"pid", current->pid, __func__, __LINE__, ##arg); \
    } while (0)


/*
 *  extern functions for r8168_n
*/
extern int rtl8168_init_module(void);
extern void rtl8168_cleanup_module(void);

void r8168_sony_set_drvdata_rp (struct rtl8168_private *p);

/*
 *  extern functions for r8168_sony_ext_dmy_eth
*/
extern struct net_device *r8168_s_dmy_eth_register(void);
extern void r8168_s_dmy_eth_unregister(struct net_device *ndev);


/*
 *  rtl8168 private instance pointer
 */
static struct rtl8168_private *r8168_p;

/* Interface for r8168_n */
void r8168_sony_set_drvdata_rp (struct rtl8168_private *p)
{
	r8168_p = p;
}

/*
 *  r8168 sony extension definitions.
 */
/* r8168 sony test command on sysfs */
enum R8168_SONY_POWER_LEVEL {
	R8168_POWER_LEVEL_PS1 = 1, /* D0: Default on state */
	R8168_POWER_LEVEL_PS2 = 2, /* D2/D3h standby: Not used */
	R8168_POWER_LEVEL_PS3 = 3, /* DeEnumerate (+PERSTB Low) */
	R8168_POWER_LEVEL_PS4 = 4, /* DeEnumerate + ISOLATEB Low */
	R8168_POWER_LEVEL_PS5 = 5, /* DeEnumerate + VPH_OFF */
};

enum R8168_SONY_POWER_STATE {
	R8168_POWER_OFF = 0,
	R8168_POWER_ON,
};

enum R8168_SONY_PARAMETER {
	/* Parameters decision at Jan.15/2024 */
	/* - Use Power Keep Alive Time (15 min) after Display-Off */
	R8168_POWER_UP_TIME  = 0,
	R8168_POWER_DOWN_TIME = 0,
	R8168_POWER_KEEP_ALIVE_SUS_TIME = 30,
	R8168_POWER_KEEP_ALIVE_TIME = 900,
	/* Power Keep Alive Time API value */
	/* n>0:valid, 0:always on */
	R8168_POWER_ALWAYS_ON  = 0,

	/* wakelock hold 100 ms */
	R8168_POWER_WAKEUP_HOLD = 1 * 100,

	/* PCIe bus number (HW fixed) */
	R8168_PCI_BUSN = 1,
};

/*
 *  r8168 sony private
 */
struct r8168_sony_private {
	struct device *dev;
	struct device *device;
	struct class  *class;

	/* power state control */
	unsigned int		power_level;
	unsigned int		power_state;
	unsigned int		power_request;
	unsigned int		power_timer_en;
	unsigned int		disp_state;

	/* on duration */
	unsigned int		power_up_time;
	/* off duration */
	unsigned int		power_dn_time;
	/* keep alive pre-duration suspendable time */
	unsigned int		power_keep_alive_sus_time;
	/* keep alive duration after display off/link-down */
	unsigned int		power_keep_alive_time;

	/* work queue */
	struct workqueue_struct	*power_wq;
	struct work_struct	power_work;
	struct alarm		power_timer;
	struct wakeup_source	*power_wakeup;
	/* wakeup for keep alive */
	struct alarm		wakeup_ka_pre_timer;
	struct wakeup_source	*power_wakeup_ka;
	/* locks */
	struct mutex		power_mlock;

	/* gpio */
	u32 isolateb_gpio;
	u32 vph_power_gpio;

	/* dummy netdev eth */
	bool dmy_eth_en;
	struct net_device *dmy_eth;

	/* debug */
	int debug;
};

/*
 *  r8168 sony extension prototypes.
 */
static int  r8168_s_power_on(struct r8168_sony_private *rp2, int pow);
static int  r8168_s_restart_power_work(struct r8168_sony_private *rp2, int powreq);
static void r8168_s_stop_power_work(struct r8168_sony_private *rp2);
static void r8168_s_reserve_ndev_eth(struct r8168_sony_private *rp2, bool rsv);

static inline struct rtl8168_private *r8168_get_drvdata_rp (void)
{
	return r8168_p;
}

static inline void _start_alarm_pow_timer(struct r8168_sony_private *rp2, int ts)
{
	alarm_start_relative(&rp2->power_timer, ms_to_ktime(ts*1000));
}

static inline void _stop_alarm_pow_timer(struct r8168_sony_private *rp2)
{
	alarm_cancel(&rp2->power_timer);
}

static inline void _start_alarm_pre_timer(struct r8168_sony_private *rp2, int ts)
{
	alarm_start_relative(&rp2->wakeup_ka_pre_timer, ms_to_ktime(ts*1000));
}

static inline void _stop_alarm_pre_timer(struct r8168_sony_private *rp2)
{
	alarm_cancel(&rp2->wakeup_ka_pre_timer);
}

static inline bool _is_ether_link_on(struct r8168_sony_private *rp2)
{
        struct rtl8168_private *rp = r8168_get_drvdata_rp();
	if (!rp || !rp->link_ok || !rp2 || !rp2->power_state) {
		return false;
	}
	return rp->link_ok(rp->dev);
}

static inline bool _is_vph_power_on(struct r8168_sony_private *rp2)
{
	if (!rp2 || !gpio_is_valid(rp2->vph_power_gpio)) {
		pr_err("%s: vph_power_gpio pin:%d is invalid!\n",
		       __func__, rp2->vph_power_gpio);
		return false;
	}
	return (gpio_get_value(rp2->vph_power_gpio) > 0) ? true : false;
}

static inline bool _is_valid_keep_alivet(int val)
{
	// Keep Alive Timer Spec.
	//  1-n(int max) : Keep Alive Timer value.
	//  0 : Power always On.
	return (val > 0)? true : false;
}

static inline bool _is_always_on_keep_alivet(int val)
{
	// Keep Alive Timer Spec.
	//  1-n(int max) : Keep Alive Timer value.
	//  0 : Power always On.
	return (val == R8168_POWER_ALWAYS_ON)? true : false;
}

static inline int _min_to_sec_keep_alivet(int val)
{
	if (_is_valid_keep_alivet(val))
		return val * 60;
	else
		return val;
}

static inline int _sec_to_min_keep_alivet(int val)
{
	if (_is_valid_keep_alivet(val))
		return val / 60;
	else
		return val;
}

static inline void _wakeup_keep_alive_time(struct r8168_sony_private *rp2, bool get)
{
	if (get) {
		// get wakeup_source.
		__pm_stay_awake(rp2->power_wakeup_ka);
	}
	else {
		// release wakeup_source.
		__pm_relax(rp2->power_wakeup_ka);
	}
}

/* r8168 sony test command on sysfs */
enum R8168_DBG_TEST_CMD {
	R8168_TCMD_INFO = 0,

	R8168_TCMD_PCI_ISOLATE_ASSERT_L   =148,
	R8168_TCMD_PCI_ISOLATE_DEASSERT_H =248,
	R8168_TCMD_VPH_POWER_ON_H   = 149,
	R8168_TCMD_VPH_POWER_OFF_L  = 249,
};

static void r8168_s_show_status (struct device *dev)
{
	struct pci_dev *p_dev;
	struct pci_bus *p_bus = NULL;
	struct net_device *net_dev = NULL;
	struct msm_pcie_dev_t *msm_p_dev = NULL;
	struct rtl8168_private *rp = r8168_get_drvdata_rp();
	struct r8168_sony_private *rp2 = dev_get_drvdata(dev);

	SLOGI("rtl8168_private(%p) :\n", rp);
	if (!rp) {
		goto r8168_sony;
	}

	p_dev = rp->pci_dev;
	net_dev = rp->dev;
	if (p_dev)
		p_bus = p_dev->bus;

	SLOGI("rtl8168: iomem(%p)\n", rp->mmio_addr);
	SLOGI("rtl8168: pci_dev(%p)\n", rp->pci_dev);
	if (p_dev) {
	    SLOGI("rtl8168: pci_dev->bus(%p)\n", p_bus);
	    if (p_bus) {
		    SLOGI("rtl8168:  bus->number:%d\n", p_bus->number);
		    SLOGI("rtl8168:  bus->primary:%d\n", p_bus->primary);
		    SLOGI("rtl8168:  bus->cur_bus_speed:%d\n", p_bus->cur_bus_speed);
		    msm_p_dev = (struct msm_pcie_dev_t *)(p_bus->sysdata);
		    SLOGI("rtl8168:  bus->sysdata=msm_pcie_dev(%p)\n", msm_p_dev);
	    }
	    SLOGI("rtl8168: pci_dev->root(%p)\n", pcie_find_root_port(p_dev));
	    SLOGI("rtl8168: pci_dev->vendor: %04x\n", p_dev->vendor);
	    SLOGI("rtl8168: pci_dev->device: %04x\n", p_dev->device);
	    SLOGI("rtl8168: pci_dev->class : %08x\n", p_dev->class);
	    SLOGI("rtl8168: pci_dev->devcap: %08x\n", p_dev->devcap);
	    SLOGI("rtl8168: pci_dev->pin   : %02x\n", p_dev->pin);
	    SLOGI("rtl8168: pci_dev->link_state(%p)\n", p_dev->link_state);
	    SLOGI("rtl8168: pci_dev->l1ss  : %04x\n", p_dev->l1ss);
	}

	SLOGI("rtl8168: net_dev(%p)\n", rp->dev);
	if (rp->dev) {
		SLOGI("rtl8168:  name: %s\n", rp->dev->name);
		SLOGI("rtl8168:  state: %lu\n", rp->dev->state);
		SLOGI("rtl8168:  type: %u\n", rp->dev->type);
		SLOGI("rtl8168:  link_mode: %u\n", rp->dev->link_mode);
	}
	SLOGI("\n");

 r8168_sony:
	SLOGI("r8168_sony_private(%p)\n", rp2);
	if (rp2) {
		SLOGI("r8168_sony: isolateb_gpio : %lu (value = %d)\n",
		      rp2->isolateb_gpio, gpio_get_value(rp2->isolateb_gpio));
		SLOGI("r8168_sony: vph_power_gpio: %lu (value = %d)\n",
		      rp2->vph_power_gpio, gpio_get_value(rp2->vph_power_gpio));
		SLOGI("r8168_sony: debug : %lu\n", rp2->debug);
	}
	return;
}


static int r8168_s_tcmd_exec (struct device *dev, int tcmd)
{
	int ret = 0;
	struct r8168_sony_private *rp2;

	if (!dev)
		return -EINVAL;

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: Could not get_drvdata(r8168_sony)\n", __func__);
		return -ENODEV;
	}

	switch (tcmd) {
	case R8168_TCMD_INFO:
		SLOGD("[TCMD %03d] Driver Status\n", tcmd);
		r8168_s_show_status(dev);
		break;

	case R8168_TCMD_PCI_ISOLATE_ASSERT_L:
		ret = gpio_direction_output(rp2->isolateb_gpio, 0);
		if (ret) {
			pr_err("%s: can't set isolateb_gpio(%d) to %d, ret=%d\n",
			       __func__, rp2->isolateb_gpio, 0, ret);
		}
		break;
	case R8168_TCMD_PCI_ISOLATE_DEASSERT_H:
		ret = gpio_direction_output(rp2->isolateb_gpio, 1);
		if (ret) {
			pr_err("%s: can't set isolateb_gpio(%d) to %d, ret=%d\n",
			       __func__, rp2->isolateb_gpio, 1, ret);
		}
		break;
	case R8168_TCMD_VPH_POWER_ON_H:
		ret = gpio_direction_output(rp2->vph_power_gpio, 1);
		if (ret) {
			pr_err("%s: can't set vph_power_gpio(%d) to %d, ret=%d\n",
			       __func__, rp2->vph_power_gpio, 1, ret);
		}
		break;
	case R8168_TCMD_VPH_POWER_OFF_L:
		ret = gpio_direction_output(rp2->vph_power_gpio, 0);
		if (ret) {
			pr_err("%s: can't set vph_power_gpio(%d) to %d, ret=%d\n",
			       __func__, rp2->vph_power_gpio, 0, ret);
		}
		break;
	default:
		break;
	}

	return ret;
}

/*
 *  sysfs interface
 */

static ssize_t pow_req_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_request);
	mutex_unlock(&rp2->power_mlock);

	return n;
}
static DEVICE_ATTR_RO(pow_req);

static ssize_t pow_level_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_level);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_level_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int pow;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &pow) < 0) {
		pr_err("%s: sscanf failed to set pow level value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	mutex_lock(&rp2->power_mlock);
	rp2->power_level = pow;
	mutex_unlock(&rp2->power_mlock);

 end:
	return count;
}
static DEVICE_ATTR_RW(pow_level);

static ssize_t pow_state_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_state);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_state_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int pow;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &pow) < 0) {
		pr_err("%s: sscanf failed to set pow value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	__pm_stay_awake(rp2->power_wakeup);
	mutex_lock(&rp2->power_mlock);

	SLOGD("power_state = %d\n", !!pow);
	r8168_s_power_on(rp2, !!pow);

	mutex_unlock(&rp2->power_mlock);
	__pm_relax(rp2->power_wakeup);
 end:
	return count;
}
static DEVICE_ATTR_RW(pow_state);

static ssize_t pow_timer_en_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_timer_en);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_timer_en_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int polling;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &polling) < 0) {
		pr_err("%s: sscanf failed to set polling_en value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	mutex_lock(&rp2->power_mlock);
	SLOGD("power_timer_en = %d\n", !!polling);
	rp2->power_timer_en = !!polling;
	mutex_unlock(&rp2->power_mlock);
 end:
	return count;
}
static DEVICE_ATTR_RW(pow_timer_en);

static ssize_t pow_timer_remain_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	ktime_t kt;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	kt = alarm_expires_remaining(&rp2->power_timer);
	if (kt < 0)
		/* timer passed */
		kt = -1;
	else
		/* convert to sec */
		kt = ktime_to_ms(kt)/1000;

	return snprintf(buf, 8, "%d\n", kt);
}
static DEVICE_ATTR_RO(pow_timer_remain);

static ssize_t dmy_eth_en_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->dmy_eth_en);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t dmy_eth_en_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int en;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &en) < 0) {
		pr_err("%s: sscanf failed to set value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	mutex_lock(&rp2->power_mlock);
	rp2->dmy_eth_en = en;
	mutex_unlock(&rp2->power_mlock);

 end:
	return count;
}
static DEVICE_ATTR_RW(dmy_eth_en);

static ssize_t pow_upt_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_up_time);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_upt_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int time;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &time) < 0) {
		pr_err("%s: sscanf failed to set time value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	SLOGD("power_up_time = %d\n", time);
	mutex_lock(&rp2->power_mlock);
	rp2->power_up_time = time;
	mutex_unlock(&rp2->power_mlock);

 end:
	return count;
}
static DEVICE_ATTR_RW(pow_upt);

static ssize_t pow_dnt_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_dn_time);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_dnt_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int time;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &time) < 0) {
		pr_err("%s: sscanf failed to set time value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	SLOGD("power_dn_time = %d\n", time);
	mutex_lock(&rp2->power_mlock);
	rp2->power_dn_time = time;
	mutex_unlock(&rp2->power_mlock);

 end:
	return count;
}
static DEVICE_ATTR_RW(pow_dnt);

static ssize_t pow_keep_alivet_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n, time;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	time = rp2->power_keep_alive_time;
	// convert sec to min.
	time = _sec_to_min_keep_alivet(time);
	n = snprintf(buf, 8, "%d\n", time);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_keep_alivet_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int time;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &time) < 0) {
		pr_err("%s: sscanf failed to set time value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	SLOGD("power_keep_alive_time = %d min (%d sec)\n",
	      time, _min_to_sec_keep_alivet(time));

	mutex_lock(&rp2->power_mlock);

	// convert min to sec.
	time = _min_to_sec_keep_alivet(time);
	// skip if no updated.
	if (time == rp2->power_keep_alive_time)
		goto unlock;

	if (_is_valid_keep_alivet(time)) {
		rp2->power_keep_alive_time = time;
		// turn power on with keep alive timer.
		if (rp2->disp_state == 0) {
			// Display Off condition
			if (rp2->power_state == R8168_POWER_ON) {
				rp2->power_request = R8168_POWER_OFF;
				// pre timer should be already kicked.
				// Therefore, restart power timer.
				_stop_alarm_pow_timer(rp2);
				if (rp2->power_timer_en)
					_start_alarm_pow_timer(rp2, rp2->power_keep_alive_time);
			}
		}
		else {
			// Display On condition
			// release wakelock
			_wakeup_keep_alive_time(rp2, false);
		}
	}
	else if (_is_always_on_keep_alivet(time)) {
		rp2->power_keep_alive_time = time;
		// turn power always on.
		// cancel timers.
		_stop_alarm_pow_timer(rp2);
		_stop_alarm_pre_timer(rp2);

		// get wakelock
		_wakeup_keep_alive_time(rp2, true);

		if (rp2->power_state == R8168_POWER_OFF) {
			// mutex_unlock to avoid potential dead-lock.
			mutex_unlock(&rp2->power_mlock);
			// Immediately turn power on
			r8168_s_restart_power_work(rp2, R8168_POWER_ON);
			goto end;
		}
	}
	else {
		// unsupported keep_alive_time value.
		pr_err("%s: unsupported keep_alive_time value\n", __func__);
	}

 unlock:
	mutex_unlock(&rp2->power_mlock);
 end:
	return count;
}
static DEVICE_ATTR_RW(pow_keep_alivet);

static ssize_t pow_keep_alivesust_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->power_keep_alive_sus_time);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t pow_keep_alivesust_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int time;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &time) < 0) {
		pr_err("%s: sscanf failed to set time value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	SLOGD("power_keep_alive_sus_time = %d\n", time);
	mutex_lock(&rp2->power_mlock);
	rp2->power_keep_alive_sus_time = time;
	mutex_unlock(&rp2->power_mlock);

 end:
	return count;
}
static DEVICE_ATTR_RW(pow_keep_alivesust);

static ssize_t disp_state_show(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp2;
	int n;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		return -EINVAL;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&rp2->power_mlock);
	n = snprintf(buf, 8, "%d\n", rp2->disp_state);
	mutex_unlock(&rp2->power_mlock);

	return n;
}

static ssize_t disp_state_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int state;
	struct r8168_sony_private *rp2;

	if (!dev) {
		pr_err("%s: invalid dev\n", __func__);
		goto end;
	}

	if (sscanf(buf, "%d", &state) < 0) {
		pr_err("%s: sscanf failed to set state value\n", __func__);
		goto end;
	}

	rp2 = dev_get_drvdata(dev);
	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		goto end;
	}

	SLOGD("disp_state = %d\n", state);

	mutex_lock(&rp2->power_mlock);
	rp2->disp_state = state;

	if (rp2->disp_state) {
		// Display on
		_stop_alarm_pow_timer(rp2);
		_stop_alarm_pre_timer(rp2);
		// release wakelock if timer used.
		if (_is_valid_keep_alivet(rp2->power_keep_alive_time))
			_wakeup_keep_alive_time(rp2, false);

		if (rp2->power_state == R8168_POWER_OFF) {
			// mutex_unlock to avoid potential dead-lock.
			mutex_unlock(&rp2->power_mlock);
			// Immediately power on
			r8168_s_restart_power_work(rp2, R8168_POWER_ON);
			goto end;
		}
		else {
			goto unlock;
		}
	}
	else {
		// Display off
		if(rp2->power_timer_en &&
		   _is_valid_keep_alivet(rp2->power_keep_alive_time)) {
			rp2->power_request = R8168_POWER_OFF;
			_stop_alarm_pow_timer(rp2);
			_start_alarm_pow_timer(rp2, rp2->power_keep_alive_time);

			_stop_alarm_pre_timer(rp2);
			_start_alarm_pre_timer(rp2, rp2->power_keep_alive_sus_time);
		}
	}
 unlock:
	mutex_unlock(&rp2->power_mlock);
 end:
	return count;
}
static DEVICE_ATTR_RW(disp_state);

static ssize_t debug_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct r8168_sony_private *rp = dev_get_drvdata(dev);
	SLOGD("\n");
	if (rp) {
		return snprintf(buf, 8, "%d", rp->debug);
	}
	return snprintf(buf, 8, "%d", 0);
}

static ssize_t debug_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	u32 cmd = 0;

	if (dev == NULL) {
		printk("invalid dev\n");
		return -EINVAL;
	}

	if (sscanf(buf, "%d", &cmd) < 0) {
		printk("sscanf failed to set cmd\n");
		return -EINVAL;
	}

	SLOGD("debug cmd = %d\n", cmd);

	// execute function.
	r8168_s_tcmd_exec(dev, cmd);
	return count;
}
static DEVICE_ATTR_RW(debug);


static struct attribute *r8168_s_attrs[] = {
	&dev_attr_pow_req.attr,
	&dev_attr_pow_level.attr,
	&dev_attr_pow_state.attr,
	&dev_attr_pow_upt.attr,
	&dev_attr_pow_dnt.attr,
	&dev_attr_pow_keep_alivet.attr,
	&dev_attr_pow_keep_alivesust.attr,
	&dev_attr_pow_timer_en.attr,
	&dev_attr_pow_timer_remain.attr,
	&dev_attr_disp_state.attr,
	&dev_attr_dmy_eth_en.attr,
	&dev_attr_debug.attr,
	NULL,
};
ATTRIBUTE_GROUPS(r8168_s);


static int r8168_s_power_on(struct r8168_sony_private *rp2, int pow)
{
	int ret = 0;
	const u32 pci_busn = R8168_PCI_BUSN;

	if (!rp2) {
		pr_err("%s: invalid rp2\n", __func__);
		return -EINVAL;
	}

	SLOGD("current pow_level=%d, pow_state=%d, set pow=%d\n",
	      rp2->power_level, rp2->power_state, pow);

	if (rp2->power_state == R8168_POWER_ON && pow == R8168_POWER_OFF) {
		// VPH POWER down
		if (rp2->power_level >= R8168_POWER_LEVEL_PS3) {
			SLOGD("msm_pcie_deenumerate (bus=%d)\n", pci_busn);
			ret = msm_pcie_deenumerate(pci_busn);
			if (ret) {
				pr_err("%s: failed to msm_pcie_deenumerate(%d), ret=%d\n",
				       __func__, pci_busn, ret);
			}
		}

		if (rp2->power_level >= R8168_POWER_LEVEL_PS4) {
			SLOGD("isolateb to %d\n", pow);
			ret = gpio_direction_output(rp2->isolateb_gpio, pow);
			if (ret) {
				pr_err("%s: can't set isolateb_gpio(%d) to %d, ret=%d\n",
				       __func__, rp2->isolateb_gpio, pow, ret);
			}
		}

		if (rp2->power_level >= R8168_POWER_LEVEL_PS5) {
			SLOGD("vph_power to %d\n", pow);
			ret = gpio_direction_output(rp2->vph_power_gpio, pow);
			if (ret) {
				pr_err("%s: can't set vph_power_gpio(%d) to %d, ret=%d\n",
				       __func__, rp2->vph_power_gpio, pow, ret);
			}
		}

		// reserve netdevice eth0
		r8168_s_reserve_ndev_eth(rp2, true);

		rp2->power_state = R8168_POWER_OFF;
	}
	else if (rp2->power_state == R8168_POWER_OFF && pow == R8168_POWER_ON) {
		// VPH POWER up

		// release reserved dmy eth0
		r8168_s_reserve_ndev_eth(rp2, false);

		if (rp2->power_level >= R8168_POWER_LEVEL_PS5) {
			SLOGD("vph_power to %d\n", pow);
			ret = gpio_direction_output(rp2->vph_power_gpio, pow);
			if (ret) {
				pr_err("%s: can't set vph_power_gpio(%d) to %d, ret=%d\n",
				       __func__, rp2->vph_power_gpio, pow, ret);
			}
		}

		if (rp2->power_level >= R8168_POWER_LEVEL_PS4) {
			msleep(2);
			SLOGD("isolateb to %d\n", pow);
			ret = gpio_direction_output(rp2->isolateb_gpio, pow);
			if (ret) {
				pr_err("%s: can't set isolateb_gpio(%d) to %d, ret=%d\n",
			       __func__, rp2->isolateb_gpio, pow, ret);
			}
			/* 3.3V Rise Time Max */
			msleep(100);
		}

		if (rp2->power_level >= R8168_POWER_LEVEL_PS3) {
			SLOGD("msm_pcie_enumerate (bus=%d)\n", pci_busn);
			ret = msm_pcie_enumerate(pci_busn);
			if (ret) {
				pr_err("%s: failed to msm_pcie_enumerate(%d), ret=%d\n",
				       __func__, pci_busn, ret);
			}
		}

		rp2->power_state = R8168_POWER_ON;
	}

	return ret;
}

static void r8168_s_power_work(struct work_struct *work)
{
	unsigned int next_power_req = R8168_POWER_ON;
	int next_alarm_time = 0;
	static unsigned long counter = 0;
	struct r8168_sony_private *rp2 = container_of(work, struct r8168_sony_private,
						      power_work);
	__pm_stay_awake(rp2->power_wakeup);
	mutex_lock(&rp2->power_mlock);

	SLOGD("[poll_en=%d] disp_state=%d, pow_state=%d, pow_req=%d, eth_link=%d counter=%lu\n",
	      rp2->power_timer_en, rp2->disp_state,
	      rp2->power_state, rp2->power_request,
	      _is_ether_link_on(rp2), counter++);

	if (rp2->disp_state == 0) {
		// Display Off condition
		if (rp2->power_state == R8168_POWER_ON) {
			// Power on current state
			if (rp2->power_request == R8168_POWER_OFF) {
				// Request power off
				if (_is_ether_link_on(rp2)) {
					// link-up, check again at next alarm.
					next_alarm_time = rp2->power_keep_alive_time;
					next_power_req = R8168_POWER_OFF;
				}
				else {
					// link-down
					// power down transition 
					r8168_s_power_on(rp2, rp2->power_request);
					next_alarm_time = rp2->power_dn_time;
					next_power_req = R8168_POWER_ON;
					// release wakelock
					_wakeup_keep_alive_time(rp2, false);
				}
			}
		}
		else if (rp2->power_state == R8168_POWER_OFF) {
			// Power off current state
			if (rp2->power_request == R8168_POWER_ON) {
				// Request power on
				// power on transition
				r8168_s_power_on(rp2, rp2->power_request);
				next_alarm_time = rp2->power_up_time;
				next_power_req = R8168_POWER_OFF;
			}
		}
	}
	else {
		// Display On condition
		if (rp2->power_state == R8168_POWER_ON) {
			// Power on current state
			// NOP
		}
		else if (rp2->power_state == R8168_POWER_OFF) {
			// Power off current state
			if (rp2->power_request == R8168_POWER_ON) {
				// set power up
				// power transition
				r8168_s_power_on(rp2, rp2->power_request);
			}
		}
	}

	// next alarm if polling enabled
	if (rp2->power_timer_en && next_alarm_time) {
		rp2->power_request = next_power_req;
		_start_alarm_pow_timer(rp2, next_alarm_time);
	}

	mutex_unlock(&rp2->power_mlock);
	__pm_relax(rp2->power_wakeup);
}

static int r8168_s_restart_power_work(struct r8168_sony_private *rp2, int powreq)
{
	bool ret=0;
	__pm_wakeup_event(rp2->power_wakeup, R8168_POWER_WAKEUP_HOLD);

	r8168_s_stop_power_work(rp2);

	rp2->power_request = powreq;
	if (rp2->power_state != rp2->power_request)
		ret = queue_work(rp2->power_wq, &rp2->power_work);

	SLOGD("power_state=%d, power_request=%d, queued=%d\n",
	      rp2->power_state, rp2->power_request, ret);

	return ret;
}

static void r8168_s_stop_power_work(struct r8168_sony_private *rp2)
{
	alarm_cancel(&rp2->power_timer);
	cancel_work_sync(&rp2->power_work);
}

static enum alarmtimer_restart r8168_s_power_timer_cb(struct alarm *alarm,
							    ktime_t time)
{
	/* Interrupt context */
	struct r8168_sony_private *rp2 = container_of(alarm, struct r8168_sony_private,
						      power_timer);
	//SLOGD("rp2=%p)\n", rp2);

	__pm_wakeup_event(rp2->power_wakeup, R8168_POWER_WAKEUP_HOLD);

	cancel_work_sync(&rp2->power_work);

	queue_work(rp2->power_wq, &rp2->power_work);

	return ALARMTIMER_NORESTART;
}

static enum alarmtimer_restart r8168_s_wakeup_ka_pre_timer_cb(struct alarm *alarm,
							    ktime_t time)
{
	/* Interrupt context */
	struct r8168_sony_private *rp2 = container_of(alarm, struct r8168_sony_private,
						      wakeup_ka_pre_timer);
	//SLOGD("rp2=%p)\n", rp2);

	// get wakeup source for keep alive time
	_wakeup_keep_alive_time(rp2, true);

	return ALARMTIMER_NORESTART;
}

static void r8168_s_reserve_ndev_eth(struct r8168_sony_private *rp2, bool get)
{
	if (rp2->dmy_eth_en && get && !rp2->dmy_eth) {
		rp2->dmy_eth = r8168_s_dmy_eth_register();
	}
	else if (!get && rp2->dmy_eth) {
		r8168_s_dmy_eth_unregister(rp2->dmy_eth);
		rp2->dmy_eth = NULL;
	}

	SLOGD("dmy_eth_en=%d, get=%d, dmy_eth=%p\n",
	      rp2->dmy_eth_en, get, rp2->dmy_eth);
	return;
}

static int r8168_s_get_gpio_resource(struct r8168_sony_private *rp2,
				     struct platform_device *pdev)
{
	int ret = 0;
	/* gpios */
	rp2->isolateb_gpio = of_get_named_gpio(pdev->dev.of_node,
					      "isolateb-gpio", 0);
	if (!gpio_is_valid(rp2->isolateb_gpio)) {
		pr_err("%s: isolate_gpio pin:%d is invalid!\n",
		       __func__, rp2->isolateb_gpio);
		ret = -EINVAL;
		goto out;
	}

	rp2->vph_power_gpio = of_get_named_gpio(pdev->dev.of_node,
					      "vph-power-gpio", 0);
	if (!gpio_is_valid(rp2->vph_power_gpio)) {
		pr_err("%s: vph_power_gpio pin:%d is invalid!\n",
		       __func__, rp2->vph_power_gpio);
		ret = -EINVAL;
	}
 out:
	return ret;
}

static	int r8168_s_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct rtl8168_private *rp1;
	struct r8168_sony_private *rp2;

	SLOGD("\n");
	rp2 = devm_kzalloc(&pdev->dev, sizeof(*rp2), GFP_KERNEL);
	if (!rp2)
		return -ENOMEM;

	platform_set_drvdata(pdev, rp2);
	rp2->dev = &pdev->dev;

	rp2->class = class_create(THIS_MODULE, "r8168_sony");
	if (IS_ERR(rp2->class)) {
		ret = PTR_ERR(rp2->class);
		devm_kfree(&pdev->dev, rp2);
		return -ENODEV;
	}
	rp2->class->dev_groups = r8168_s_groups;

	rp2->device = device_create(rp2->class, NULL, MKDEV(0, 0),
						NULL, "ext");
	if (IS_ERR(rp2->device)) {
		pr_err("%s: Could not create device\n", __func__);
		ret = -ENODEV;
		goto del_class;
	}

	if (alarmtimer_get_rtcdev()) {
		alarm_init(&rp2->power_timer, ALARM_REALTIME,
			   r8168_s_power_timer_cb);
		alarm_init(&rp2->wakeup_ka_pre_timer, ALARM_REALTIME,
			   r8168_s_wakeup_ka_pre_timer_cb);
	}
	else {
		ret = -EPROBE_DEFER;
		goto del_device;
	}

	ret = r8168_s_get_gpio_resource(rp2, pdev);
	if (ret) {
		ret = -EINVAL;
		goto del_device;
	}

	/* Initialize resources */
	mutex_init(&rp2->power_mlock);
	rp2->power_wq = create_singlethread_workqueue("r8168_s_pow");
	if (!rp2->power_wq) {
		ret = -ENOMEM;
		goto del_device;
	}
	INIT_WORK(&rp2->power_work, r8168_s_power_work);
	rp2->power_wakeup = wakeup_source_register(&pdev->dev, "r8168_s_pow");
	if (!rp2->power_wakeup) {
		ret = -ENOMEM;
		goto del_wq;
	}
	rp2->power_wakeup_ka = wakeup_source_register(&pdev->dev, "r8168_s_pow_ka");
	if (!rp2->power_wakeup_ka) {
		wakeup_source_unregister(rp2->power_wakeup);
		ret = -ENOMEM;
		goto del_wq;
	}

	/* Initialize default parameters */
	rp2->power_level = R8168_POWER_LEVEL_PS5;
	rp2->power_up_time = R8168_POWER_UP_TIME;
	rp2->power_dn_time = R8168_POWER_DOWN_TIME;
	rp2->power_keep_alive_sus_time = R8168_POWER_KEEP_ALIVE_SUS_TIME;
	rp2->power_keep_alive_time = R8168_POWER_KEEP_ALIVE_TIME;
	rp2->dmy_eth_en = true;
	rp2->power_timer_en = true;

	rp1 = r8168_get_drvdata_rp();
	if (rp1) {
		rp2->power_state = R8168_POWER_ON;
	}
	else {
		pr_err("%s: r8168 ndev is not initialized\n", __func__);
		rp2->power_state = R8168_POWER_OFF;
	}

	dev_set_drvdata(rp2->device, rp2);

	return 0;

 del_wq:
	destroy_workqueue(rp2->power_wq);
 del_device:
	device_destroy(rp2->class, MKDEV(0, 0));
 del_class:
	class_destroy(rp2->class);
	devm_kfree(&pdev->dev, rp2);

	return ret;
}
static	int r8168_s_remove(struct platform_device *pdev)
{
	struct r8168_sony_private *rp2 = platform_get_drvdata(pdev);
	SLOGD("\n");

	alarm_cancel(&rp2->wakeup_ka_pre_timer);
	alarm_cancel(&rp2->power_timer);
	cancel_work_sync(&rp2->power_work);

	r8168_s_reserve_ndev_eth(rp2, false);

	wakeup_source_unregister(rp2->power_wakeup);
	wakeup_source_unregister(rp2->power_wakeup_ka);

	destroy_workqueue(rp2->power_wq);

	device_destroy(rp2->class, MKDEV(0, 0));
	class_destroy(rp2->class);
	devm_kfree(&pdev->dev, rp2);

	platform_set_drvdata(pdev, NULL);

	return 0;
}

static	void r8168_s_shutdown(struct platform_device *pdev)
{
	SLOGD("\n");
	return;
}

static const struct of_device_id r8168_s_match_table[] = {
	{
		.compatible	 = "realtek,r8168_sony",
	},
	{ },
};

static struct platform_driver r8168_s_driver = {
	.probe		= r8168_s_probe,
	.remove		= r8168_s_remove,
	.shutdown	= r8168_s_shutdown,
	.driver		= {
		.name	= "r8168_sony",
		.of_match_table	= r8168_s_match_table,
	},
};

static int __init
r8168_sony_init(void)
{
	int ret;
	SLOGD("\n");

	ret = rtl8168_init_module();
        if (ret) {
                pr_err("%s rtl8168 init failed %d\n", __func__, ret);
                return ret;
        }

	ret = platform_driver_register(&r8168_s_driver);
	if (ret) {
		pr_err("%s: platform driver register failed %d\n",
			__func__, ret);
		return ret;
	}

	return 0;
}

static void __exit
r8168_sony_exit(void)
{
	SLOGD("\n");
	platform_driver_unregister(&r8168_s_driver);

	rtl8168_cleanup_module();
}

module_init(r8168_sony_init);
module_exit(r8168_sony_exit);

MODULE_DESCRIPTION("R8168 sony extension");
MODULE_LICENSE("GPL v2");
