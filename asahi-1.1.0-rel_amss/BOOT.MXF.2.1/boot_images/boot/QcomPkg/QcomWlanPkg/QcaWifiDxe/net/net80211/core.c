/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 18/11/21  zxue     refine code
 23/7/21   zxue     Disable 6G when supplicant doesnt support WPA3 (SAE or SUITE B)
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/net80211.h>
#include <net/ndebug.h>
#include "net80211_i.h"
#include "drvops.h"
#include "sme.h"

struct net80211_notifier __g_net80211_notifier;

/* ops */
int net80211_vif_add(
    struct net80211_pdev *pdev, const char *name, enum nl80211_iftype type,
    struct net80211_vif **new_vif);

void net80211_vif_remove(struct net80211_vif *vif);

/* Implementation exposed to higher layer */

int net80211_init(struct net80211_notifier *notifier)
{
    __g_net80211_notifier = *notifier;
    return 0;
}

void net80211_deinit(struct net80211_notifier *notifier)
{
    ASSERT(__g_net80211_notifier.ctx == notifier->ctx);
    memset(&__g_net80211_notifier, 0, sizeof(__g_net80211_notifier));
}

void net80211_dev_notify(struct net80211_pdev *pdev, struct net80211_dev_event *devt)
{
    net_dbg("notify event %d\n", devt ? devt->type : 0);

    if (__g_net80211_notifier.dev_notify) {
        __g_net80211_notifier.dev_notify(pdev, devt, 
            __g_net80211_notifier.ctx);
    }
}

/* device information */
int net80211_get_mac_address(struct net80211_pdev *pdev, u8 *mac_address)
{
    memcpy(mac_address, pdev->conf.perm_addr, ETH_ALEN);
    return 0;
}

int net80211_set_supplicant_supported_akm_suites(struct net80211_pdev *pdev,
    const struct net80211_suite_selector *akm_suites, u32 n_akm_suites)
{
    static const u32 PRIORITY_AKM_SUITES[] = {
        WLAN_RSN_AKM_SUITE_SAE,
        WLAN_RSN_AKM_SUITE_PSK_SHA256,
        WLAN_RSN_AKM_SUITE_PSK,
        WLAN_RSN_AKM_SUITE_SUITE_B_192,
        WLAN_RSN_AKM_SUITE_SUITE_B,
        WLAN_RSN_AKM_SUITE_8021X_SHA256,
        WLAN_RSN_AKM_SUITE_8021X,
    };

    u32 i, j, k;

    BUILD_BUG_ON(ARRAY_SIZE(PRIORITY_AKM_SUITES) > ARRAY_SIZE(pdev->scrypto.akm_suites));

    net_dbg("build supported akm suites from %d supplicant supported akm suites "
        "and %d hardware supported akm suites\n",
        n_akm_suites, pdev->conf.n_akm_suites);

    /* rebuild akm suites */
    pdev->scrypto.n_akm_suites = 0;

    for (i = 0; i < ARRAY_SIZE(PRIORITY_AKM_SUITES); i++) {
        /* supplicant supported akm suite */
        if (n_akm_suites) {
            for (j = 0; j < n_akm_suites; j++) {
                if (PRIORITY_AKM_SUITES[i] == WLAN_SUITE_SELECTOR(&akm_suites[j]))
                    break;
            }
            if (j == n_akm_suites)
                continue;
        }

        /* hardware supported akm suites */
        if (pdev->conf.n_akm_suites) {
            for (k = 0; k < pdev->conf.n_akm_suites; k++) {
                if (PRIORITY_AKM_SUITES[i] == pdev->conf.akm_suites[k])
                    break;
            }
            if (k == n_akm_suites)
                continue;
        }

        pdev->scrypto.akm_suites[pdev->scrypto.n_akm_suites++] = PRIORITY_AKM_SUITES[i];
    }

    net_dbg("built %d supported akm suites\n", pdev->scrypto.n_akm_suites);

    return 0;
}

int net80211_set_supplicant_supported_cipher_suites(struct net80211_pdev *pdev,
    const struct net80211_suite_selector *cipher_suites, u32 n_cipher_suites)
{
    static const u32 PRIORITY_CIPHERS_PAIRWISE[] = {
        WLAN_RSN_CIPHER_SUITE_CCMP,
        WLAN_RSN_CIPHER_SUITE_TKIP,
        WLAN_RSN_CIPHER_SUITE_GCMP,
        WLAN_RSN_CIPHER_SUITE_GCMP_256,
        WLAN_RSN_CIPHER_SUITE_CCMP_256,
    };

    u32 i, j, k;

    BUILD_BUG_ON(ARRAY_SIZE(PRIORITY_CIPHERS_PAIRWISE) > ARRAY_SIZE(pdev->scrypto.cipher_suites));

    net_dbg("build supported cipher suites from %d supplicant supported cipher suites "
        "and %d hardware supported cipher suites\n",
        n_cipher_suites, pdev->conf.n_cipher_suites);

    /* rebuild cipher suites */
    pdev->scrypto.n_cipher_suites = 0;

    for (i = 0; i < ARRAY_SIZE(PRIORITY_CIPHERS_PAIRWISE); i++) {
        /* supplicant supported cipher suite */
        if (n_cipher_suites) {
            for (j = 0; j < n_cipher_suites; j++) {
                if (PRIORITY_CIPHERS_PAIRWISE[i] == WLAN_SUITE_SELECTOR(&cipher_suites[j]))
                    break;
            }
            if (j == n_cipher_suites)
                continue;
        }

        /* hardware supported cipher suite */
        if (pdev->conf.n_cipher_suites) {
            for (k = 0; k < pdev->conf.n_cipher_suites; k++) {
                if (PRIORITY_CIPHERS_PAIRWISE[i] == pdev->conf.cipher_suites[k])
                    break;
            }
            if (k == pdev->conf.n_cipher_suites)
                continue;
        }
        
        pdev->scrypto.cipher_suites[pdev->scrypto.n_cipher_suites++] = PRIORITY_CIPHERS_PAIRWISE[i];
    }

    net_dbg("built %d supported cipher suites\n", pdev->scrypto.n_cipher_suites);

    return 0;
}

bool net80211_is_sae_suiteb_supported(struct net80211_pdev *pdev)
{
	static const u32 SAE_SUITEB_AKM_SUITES[] = {
		WLAN_RSN_AKM_SUITE_SAE,
		WLAN_RSN_AKM_SUITE_SUITE_B_192,
		WLAN_RSN_AKM_SUITE_SUITE_B,
	};

	struct net80211_supported_crypto_settings *scrypto = &pdev->scrypto;
	u32 i, j;

	if (!scrypto->n_akm_suites)
		return false;

	for (i = 0; i < ARRAY_SIZE(SAE_SUITEB_AKM_SUITES); i++) {
		for (j = 0; j < scrypto->n_akm_suites; j++) {
			if (SAE_SUITEB_AKM_SUITES[i] == scrypto->akm_suites[j])
				return true;
		}
	}

	return false;
}

/* interface api */
struct net80211_vif* net80211_add_interface(struct net80211_pdev *pdev)
{
    struct net80211_vif *vif;
    int err;

    err = net80211_vif_add(pdev, "wlan0", NL80211_IFTYPE_STATION, &vif);

    return err ? NULL : vif;
}

int net80211_remove_interface(struct net80211_pdev *pdev, struct net80211_vif *vif)
{
    net80211_vif_remove(vif);
    return 0;
}

int net80211_install_key(struct net80211_pdev *pdev, 
    struct net80211_vif *vif, struct net80211_key_set *key_set)
{
    return net80211_vif_add_key(vif, key_set);
}

/* connect */
int net80211_connect(
    struct net80211_pdev *pdev, struct net80211_vif *vif,
    struct net80211_connect_params *request)
{
    return net80211_sta_sme_connect(vif, request);
}

int net80211_disconnect(
    struct net80211_pdev *pdev, struct net80211_vif *vif)
{
    return net80211_sta_sme_disconnect(vif);
}

/* tx & rx */
int net80211_transmit_pkt(struct net80211_pdev *pdev, struct net80211_vif *vif, struct sk_buff *skb)
{
	return net80211_vif_start_xmit_8023(skb, &vif->dev);
}

struct net_device *net80211_get_data_device(struct net80211_vif *vif)
{
    return vif ? &vif->dev: NULL;
}

/* priv */
int net80211_priv_command(struct net80211_pdev *pdev, struct net80211_priv_cmd *cmd)
{
    BUILD_BUG_ON(sizeof(*cmd) != sizeof(struct ieee80211_priv_cmd));
    return drv_priv_command(pdev, (void *)cmd);
}


/**************************/
/* helpers */
void net80211_notify_dev_registered(struct net80211_pdev *pdev)
{
    if (__g_net80211_notifier.dev_registered) {
        __g_net80211_notifier.dev_registered(
		pdev, __g_net80211_notifier.ctx);
    }
}

void net80211_notify_dev_unregistered(struct net80211_pdev *pdev)
{
    if (__g_net80211_notifier.dev_registered) {
        __g_net80211_notifier.dev_unregistered(
		pdev, __g_net80211_notifier.ctx);
    }
}
