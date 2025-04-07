/*
 * Copyright (c) 2020-2021 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

/*=============================================================================
                              EDIT HISTORY

 

 when       who     what, where, why
 --------   ---     -----------------------------------------------------------
 14/7/21   zxue     branch for core boot

=============================================================================*/

#include <net/ndebug.h>
#include "net80211_i.h"
#include "drvops.h"

#define NUM_DEFAULT_KEYS 4
#define NUM_DEFAULT_MGMT_KEYS 2

struct key_params {
    const u8 *key;
    const u8 *seq;
    int key_len;
    int seq_len;
    u16 vlan_id;
    u32 cipher;
    enum nl80211_key_mode mode;
};

/* helpers */
static bool net80211_key_is_same(struct net80211_key *key1, struct net80211_key *key2)
{
    if (key2 == key1)
        return true;

    if (key1 && key2 &&
        (key1->sta == key2->sta) &&
        (key1->conf.flags == key2->conf.flags) &&
        (key1->conf.cipher == key2->conf.cipher) &&
        (key1->conf.icv_len == key2->conf.icv_len) &&
        (key1->conf.iv_len == key2->conf.iv_len) &&
        (key1->conf.key_idx == key2->conf.key_idx) &&
        (key1->conf.key_len == key2->conf.key_len) &&
        memcmp(key1->conf.key, key2->conf.key,
            sizeof(key1->conf) + key1->conf.key_len) == 0) {
        return true;
    }

    return false;
}

struct net80211_key *net80211_key_alloc(u32 cipher, int idx, 
    size_t key_len, const u8 *key_data,
    size_t seq_len, const u8 *seq)
{
	struct net80211_key *key;

	if (WARN_ON(idx < 0 || idx >= NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS))
		return ERR_PTR(-EINVAL);

	key = kzalloc(sizeof(struct net80211_key) + key_len, GFP_KERNEL);
	if (!key)
		return ERR_PTR(-ENOMEM);

	key->conf.flags = 0;
	key->conf.cipher = cipher;
	key->conf.key_idx = (s8)idx;
	key->conf.key_len = (u8)key_len;
	switch (cipher) {
	case WLAN_RSN_CIPHER_SUITE_WEP40:
	case WLAN_RSN_CIPHER_SUITE_WEP104:
		key->conf.iv_len = IEEE80211_WEP_IV_LENGTH;
		key->conf.icv_len = IEEE80211_WEP_ICV_LENGTH;
		break;
	case WLAN_RSN_CIPHER_SUITE_TKIP:
		key->conf.iv_len = IEEE80211_TKIP_IV_LENGTH;
		key->conf.icv_len = IEEE80211_TKIP_ICV_LENGTH;
		break;
	case WLAN_RSN_CIPHER_SUITE_CCMP:
		key->conf.iv_len = IEEE80211_CCMP_HDR_LENGTH;
		key->conf.icv_len = IEEE80211_CCMP_MIC_LENGTH;
		break;
	case WLAN_RSN_CIPHER_SUITE_CCMP_256:
		key->conf.iv_len = IEEE80211_CCMP_256_HDR_LENGTH;
		key->conf.icv_len = IEEE80211_CCMP_256_MIC_LENGTH;
		break;
	case WLAN_RSN_CIPHER_SUITE_AES_CMAC:
	case WLAN_RSN_CIPHER_SUITE_BIP_CMAC_256:
		key->conf.iv_len = 0;
		if (cipher == WLAN_RSN_CIPHER_SUITE_AES_CMAC)
			key->conf.icv_len = sizeof(struct ieee80211_mmie);
		else
			key->conf.icv_len = sizeof(struct ieee80211_mmie_16);
		break;
	case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_128:
	case WLAN_RSN_CIPHER_SUITE_BIP_GMAC_256:
		key->conf.iv_len = 0;
		key->conf.icv_len = sizeof(struct ieee80211_mmie_16);
		break;
	case WLAN_RSN_CIPHER_SUITE_GCMP:
	case WLAN_RSN_CIPHER_SUITE_GCMP_256:
		key->conf.iv_len = IEEE80211_GCMP_HDR_LENGTH;
		key->conf.icv_len = IEEE80211_GCMP_MIC_LENGTH;
		break;
	default:
		net_dbg("nl80211: cipher %d\n", cipher); 
	}
	
	memcpy(key->conf.key, key_data, key_len);
	return key;
}

void net80211_key_destroy(struct net80211_key *key)
{
    if (key)
    	kfree(key);
}

int net80211_key_enable_hw_accel(struct net80211_key *key)
{
	int ret = -EOPNOTSUPP;

    if (!key || !key->pdev->ops->ieee80211_set_key)
        return ret;
	
    ret = drv_set_key(key->pdev, IEEE80211_SET_KEY, key->vif,
        key->sta, &key->conf);
	if (ret) {
        net_err("failed to add key (%d, %pM) from hardware (%d)\n",
            key->conf.key_idx, key->sta ? net80211_sta_addr(key->sta): NULL, ret);
    }

    key->uploaded = 1;

	return ret;
}

int net80211_key_disable_hw_accel(struct net80211_key *key)
{
	int ret = -EOPNOTSUPP;

	if (!key || !key->pdev->ops->ieee80211_set_key)
		return ret;

    key->uploaded = 0;

	ret = drv_set_key(key->pdev, IEEE80211_DISABLE_KEY, key->vif, 
        key->sta, &key->conf);
    if (ret) {
        net_err("failed to remove key (%d, %pM) from hardware (%d)\n",
            key->conf.key_idx, key->sta ? net80211_sta_addr(key->sta) : NULL, ret);
    }

	return ret;
}

int net80211_key_replace(struct net80211_vif *vif,
				  struct net80211_sta *sta,
				  struct net80211_key *old_key,
				  struct net80211_key *new_key,
				  u16 flags)
{
	/* Remove key with old_key and install key with new_key */
	if (WARN_ON(!new_key && !old_key))
		return 0;

    if (net80211_key_is_same(old_key, new_key)) {
        net_warn("Not reinstalling key to driver as the key is already in use\n");
        net80211_key_destroy(new_key);
        return 0;
    }

	if (old_key) {
		net80211_key_disable_hw_accel(old_key);


		if (flags & IEEE80211_KEY_FLAG_PAIRWISE) {
			if (vif->ptk_key == old_key) {
				vif->ptk_key = NULL;
				net80211_key_destroy(old_key);
			}
		}
		else if (flags & IEEE80211_KEY_FLAG_GTK) {
			if (vif->gtk_key == old_key) {
				vif->gtk_key = NULL;
				net80211_key_destroy(old_key);
			}
		}
		else {
			if (vif->igtk_key == old_key) {
				vif->igtk_key = NULL;
				net80211_key_destroy(old_key);
			}
		}
	}

    if (new_key) {
        net80211_key_enable_hw_accel(new_key);
        if (flags & IEEE80211_KEY_FLAG_PAIRWISE) {
            WARN_ON(vif->ptk_key);
            vif->ptk_key = new_key;
        }
        else if (flags & IEEE80211_KEY_FLAG_GTK) {
            WARN_ON(vif->gtk_key);
            vif->gtk_key = new_key;
        }
		else {
			WARN_ON(vif->igtk_key);
			vif->igtk_key = new_key;
		}
    }
	
	return 0;
}

int net80211_key_link(struct net80211_key *key,
		       struct net80211_vif *vif,
		       struct net80211_sta *sta)
{
	static atomic_t key_color = ATOMIC_INIT(0);
	struct net80211_key *old_key = NULL;
	int ret;

	key->pdev = vif->pdev;
	key->vif = vif;
	key->sta = sta;

	/* get the old key */
	if (key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE) {
		old_key = vif->ptk_key;
	}
	else if (key->conf.flags& IEEE80211_KEY_FLAG_GTK) {
		old_key = vif->gtk_key;
	}
	else {
		old_key = vif->igtk_key;
	}

	/*
	 * Assign a unique ID to every key so we can easily prevent mixed
	 * key and fragment cache attacks.
	 */
	key->conf.color = (u8)atomic_inc_return(&key_color);

	ret = net80211_key_replace(vif, sta, old_key, key, key->conf.flags);
	if (ret) {
		net80211_key_destroy(key);
		net_err("key replace failed: %d\n", ret);
	}
	
	return ret;
}

int net80211_vif_set_key(struct net80211_vif *vif,
    u8 key_idx, int key_type, const u8 *mac_addr,
    struct key_params *params)
{
	struct net80211_sta *sta = NULL;
	struct net80211_key *key;
	int err;

	key = net80211_key_alloc(params->cipher, key_idx, params->key_len,
				  params->key, params->seq_len, params->seq);
	if (IS_ERR(key))
		return PTR_ERR(key);

	if (key_type == 0)
		key->conf.flags |= IEEE80211_KEY_FLAG_GTK;
	else if (key_type == 1)
		key->conf.flags |= IEEE80211_KEY_FLAG_PAIRWISE;



	if (params->mode == NL80211_KEY_NO_TX)
		key->conf.flags |= IEEE80211_KEY_FLAG_NO_AUTO_TX;

	if (mac_addr) {
		sta = net80211_vif_get_sta(vif, mac_addr);
	}
	
	err = net80211_key_link(key, vif, sta);

	return err;

}

void net80211_key_free(struct net80211_key *key)
{
	if (!key)
		return;

	/*
	 * Replace key with NULL.
	 */
	if (key->vif)
		net80211_key_replace(key->vif, key->sta,
				key, NULL, key->conf.flags);
}

int net80211_vif_add_key(struct net80211_vif *vif, struct net80211_key_set *key)
{
	struct key_params *params;
	u8 *params_key, *params_seq;

	net_dbg("key_len/key_id/key_type/rsc_len/suite_type: %d-%d-%d-%d-%d\n", key->key_len, key->key_id, key->key_type, 
			 key->rsc_len, key->cipher_suite.suite_type);
	net_dbg("mac_addr %02x-%02x-%02x-%02x-%02x-%02x\n", key->mac_addr[0], key->mac_addr[1], key->mac_addr[2], 
			 key->mac_addr[3], key->mac_addr[4], key->mac_addr[5]);

	params = kzalloc(sizeof(*params) + key->key_len + key->rsc_len, GFP_KERNEL);
	if (!params)
		return -ENOMEM;

    BUILD_BUG_ON(sizeof(key->cipher_suite) != sizeof(u32));

	/* Build the key params */
	params_key = (u8*)params + sizeof(*params);
	params_seq = params_key + key->key_len;
    params->cipher = WLAN_SUITE_SELECTOR(&key->cipher_suite);
	params->key_len = (int)key->key_len;
	params->seq_len = (int)key->rsc_len;
	params->mode = NL80211_KEY_RX_TX;
	params->key = params_key;
	params->seq = params_seq;
	memcpy(params_key, key->key, key->key_len);
	memcpy(params_seq, key->rsc, key->rsc_len);

	net_hexdump("Key: ", params->key, (u32)params->key_len, 32);
	net_hexdump("Seq: ", params->seq, (u32)params->seq_len, 32);

	if (key->key_id == 0) {
		/* PTK set */
		net80211_vif_set_key(vif, key->key_id, key->key_type, key->mac_addr, params);
	}
	else {
		/* GTK/IGTK set use the addr as NULL */
		net80211_vif_set_key(vif, key->key_id, key->key_type, NULL, params);
	}

	kfree(params);
	return 0;
}

int net80211_vif_del_key(struct net80211_vif *vif, const u8 *mac_addr)
{
	struct net80211_sta *sta;
	int ret = -ENOENT;

	if (mac_addr) {
		sta = net80211_vif_get_sta(vif, mac_addr);
		if (!sta) {
			net_err("sta is NULL\n");
			goto out_unlock;
		}
	}

    net80211_key_free(vif->ptk_key);
    net80211_key_free(vif->gtk_key);
    net80211_key_free(vif->igtk_key);

    ret = 0;

 out_unlock:
	return ret;
}


