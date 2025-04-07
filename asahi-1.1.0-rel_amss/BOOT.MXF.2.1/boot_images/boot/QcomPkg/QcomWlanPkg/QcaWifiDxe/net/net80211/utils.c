/*
 * Copyright (c) 2020-2022 Qualcomm Technologies, Inc.
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
#include <net/regulatory.h>
#include <qdf/worker.h>
#include "net80211_i.h"
#include "drvops.h"
#include "chan.h"
#include "mlme.h"

static inline int ecw2cw(int ecw)
{
    return (1 << ecw) - 1;
}

const struct ieee80211_reg_rule *
freq_reg_info(struct net80211_pdev *pdev, u32 center_freq);

u32 
ieee80211_channel_to_frequency(int channel, enum nl80211_band band)
{
    /* invalid channel */
    if (channel <= 0)
        return 0;

    if (NL80211_BAND_2GHZ == band) {
        if (1 <= channel && channel <= 13) {
            return (2407 + 5 * channel);
        }
        if (14 == channel) {
            return 2484;
        }
        return 0;
    }

    if (NL80211_BAND_5GHZ == band) {
        if (36 <= channel && channel <= 173) {
            return (5000 + 5 * channel);
        }
        if (183 <= channel && channel <= 196) {
            if (channel == 186 || channel == 190 || channel == 191)
                return 0;
            return (4000 + channel * 5);
        }
        return 0;
    }

    if (NL80211_BAND_6GHZ == band) {
        if (channel == 2) {  /* orphan */
            return 5935;
        }
        if (1 <= channel && channel <= 233) {
            return (5950 + 5 * channel);
        }
        return 0;
    }

    return 0;
}

typedef u32 ieee80211_band_channel_t;

#define IEEE80211_BAND_2GHZ_CHANNEL(_c) ((_c) | (NL80211_BAND_2GHZ << 16))
#define IEEE80211_BAND_5GHZ_CHANNEL(_c) ((_c) | (NL80211_BAND_5GHZ << 16))
#define IEEE80211_BAND_6GHZ_CHANNEL(_c) ((_c) | (NL80211_BAND_6GHZ << 16))

#define IEEE80211_BAND_CHANNEL_GET_CHANNEL(_bc)  ((_bc) & 0xffff)
#define IEEE80211_BAND_CHANNEL_GET_BAND(_bc)     ((enum nl80211_band)((_bc >> 16) & 0xffff))

static ieee80211_band_channel_t
ieee80211_frequency_to_band_channel(u32 freq)
{
    /* 2GHZ */
    if (2412 <= freq && freq <= 2472) {
        if (((freq - 2407) % 5) != 0)
            return 0;
        return IEEE80211_BAND_2GHZ_CHANNEL((freq - 2407) / 5);
    }
    if (freq == 2484) {
        return IEEE80211_BAND_2GHZ_CHANNEL(14);
    }

    /* 5GHZ */
    if (4910 <= freq && freq <= 4980) {
        if (((freq - 4000) % 5) != 0)
            return 0;
        return IEEE80211_BAND_5GHZ_CHANNEL((freq - 4000) / 5);
    }
    if (freq < 5945) {
        if (((freq - 5000) % 5) != 0)
            return 0;
        return IEEE80211_BAND_5GHZ_CHANNEL((freq - 5000) / 5);
    }

    /* 6GHZ */
    if (freq == 5935) {
        return IEEE80211_BAND_6GHZ_CHANNEL(2);
    }
    if (5955 <= freq && freq <= 7115) {
        if (((freq - 5950) % 5) != 0)
            return 0;
        return IEEE80211_BAND_6GHZ_CHANNEL((freq - 5950) / 5);
    }

    return 0;
}

int
ieee80211_frequency_to_channel(u32 freq)
{
    ieee80211_band_channel_t bc = ieee80211_frequency_to_band_channel(freq);
    return IEEE80211_BAND_CHANNEL_GET_CHANNEL(bc);
}

static inline enum nl80211_band
ieee80211_frequency_to_band(u32 freq)
{
    ieee80211_band_channel_t bc = ieee80211_frequency_to_band_channel(freq);
    if (!bc)
        return NUM_NL80211_BANDS;
    return IEEE80211_BAND_CHANNEL_GET_BAND(bc);
}

u32 
ieee80211_hdrlen(le16 fc)
{
    u32 hdrlen = 24;

    if (ieee80211_is_mgmt(fc)) {
        if (ieee80211_has_order(fc))
            hdrlen += IEEE80211_HT_CTL_LEN;
    }
    else if (ieee80211_is_data(fc)) {
        if (ieee80211_has_a4(fc))
            hdrlen += ETH_ALEN;
        if (ieee80211_is_data_qos(fc)) {
            hdrlen += IEEE80211_QOS_LEN;
            if (ieee80211_has_order(fc))
                hdrlen += IEEE80211_HT_CTL_LEN;
        }
    }
    else if (ieee80211_is_ctl(fc)) {
        if (ieee80211_is_ack(fc) || ieee80211_is_cts(fc))
            hdrlen = 10;
        else
            hdrlen = 16;
    }

    return hdrlen;
}

const struct element *
ieee80211_find_element(const u8 *ies, u32 len, u8 eid)
{
    const struct element *elem;

    for_each_element_id(elem, eid, ies, len) {
        return elem;
    }

    return NULL;
}

const struct element *
ieee80211_find_vendor_element(const u8 *ies, u32 len, u32 oui)
{
    const struct element *elem;
    u32 match = __cpu_to_be32(oui);

    for_each_element_id(elem, WLAN_EID_VENDOR_SPECIFIC, ies, len) {
        if (elem->datalen < 4)
            continue;
        if (memcmp(elem->data, &match, sizeof(match)) == 0)
            return elem;
    }

    return NULL;
}

const struct element *
ieee80211_find_extension_element(const u8 *ies, u32 len, u8 eeid)
{
    const struct element *elem;

    for_each_element_id(elem, WLAN_EID_EXTENSION, ies, len) {
        if (elem->datalen < 1)
            continue;
        if (memcmp(elem->data, &eeid, sizeof(eeid)) == 0)
            return elem;
    }

    return NULL;
}

bool
ieee80211_sband_supports_80mhz(const struct ieee80211_supported_band *sband)
{
    u32 i;
    for (i = 0; i < sband->n_channels; i++) {
        if (sband->channels[i].flags & (IEEE80211_CHAN_DISABLED |
            IEEE80211_CHAN_NO_80MHZ))
            continue;

        return true;
    }

    return false;
}

static inline u8
ieee80211_get_ht_vht_rx_chains(
    const struct ieee80211_ht_capabilities *ht_cap,
    const struct ieee80211_vht_capabilities *vht_cap)
{
    u8 chains = 1;

    if (ht_cap) {
        chains = ieee80211_mcs_info_get_chains(&ht_cap->mcs);
    }

    if (vht_cap) {
        u8 nss = ieee80211_vht_mcs_info_get_nss(&vht_cap->supported_mcs_set);
        chains = max(chains, nss);
    }

    return chains;
}

static inline u8
ieee80211_sband_get_rx_chains(const struct ieee80211_supported_band *sband)
{
    u8 chains = 1;

    if (sband->ht_cap.ht_supported) {
        chains = ieee80211_mcs_info_get_chains(&sband->ht_cap.mcs);
    }

    if (sband->vht_cap.vht_supported) {
        u8 nss = ieee80211_vht_mcs_info_get_nss(&sband->vht_cap.vht_mcs);
        chains = max(chains, nss);
    }

    return chains;
}

u8
ieee80211_get_rx_chains(
    const struct ieee80211_supported_band *sband,
    const struct ieee80211_ht_capabilities *ht_cap,
    const struct ieee80211_vht_capabilities *vht_cap)
{
    u8 supp_rx_chains = ieee80211_sband_get_rx_chains(sband);
    u8 avai_rx_chains = ieee80211_get_ht_vht_rx_chains(ht_cap, vht_cap);

    return min(supp_rx_chains, avai_rx_chains);
}

void 
ieee80211_get_rates(const struct ieee80211_supported_band *sband,
    u8 *supp_rates, u32 supp_rates_len, int shift,
    u32 *rates, u32 *basic_rates,
    bool *have_rate_higher_than_11mbit)
{
    int min_rate = INT_MAX;
    int min_rate_index = -1;
    u32 i, n;

    for (i = 0; i < supp_rates_len; i++) {
        int rate = supp_rates[i] & 0x7f;
        bool is_basic = !!(supp_rates[i] & 0x80);

        /* NOTE: Skip HT/VHT BSS membership selectors as they're not rates. */
        if (supp_rates[i] == (0x80 | IEEE80211_BSS_MEMBERSHIP_SELECTOR_HT_PHY) ||
            supp_rates[i] == (0x80 | IEEE80211_BSS_MEMBERSHIP_SELECTOR_VHT_PHY))
            continue;

        if ((rate * 5 * (1 << shift)) > 110)
            *have_rate_higher_than_11mbit = true;

        for (n = 0; n < sband->n_bitrates; n++) {
            struct ieee80211_rate *arate;
            int bitrate;

            arate = &sband->bitrates[n];

            bitrate = DIV_ROUND_UP(arate->bitrate, (1 << shift) * 5);
            if (bitrate == rate) {
                *rates |= BIT(n);
                if (is_basic)
                    *basic_rates |= BIT(n);
                if ((rate * 5) < min_rate) {
                    min_rate = rate * 5;
                    min_rate_index = n;
                }
                break;
            }
        }
    }

    if ((*basic_rates == 0) && min_rate_index >= 0) {
        net_warn("No basic rates, using min rate instead\n");
        *basic_rates = BIT(min_rate_index);
    }
}

int
ieee80211_parse_wpa_ie(const u8 *ie, struct net80211_crypto_settings *crypto)
{
    u16 len;
    u16 i, n;
    u16 version;

    if (ie == NULL)
        return -EINVAL;

    net_dbg("parse wpa ie\n");

    len = ie[1];
    if (len < 14) {
        net_dbg("WPA too short, len %u\n", len);
        return -EINVAL;
    }
    ie += 6; len -= 4;  /* NOTE: len is payload only */

    memset(crypto, 0, sizeof(*crypto));
    crypto->wpa_type = IEEE80211_WPA_TYPE_WPA;

    /* NOTE: WPA OUI is validated before  */
    version = le16_to_cpu(*(__le16*)ie);
    if (version != 1) {
        net_dbg("WPA bad version %u\n", version);
        return -EINVAL;
    }
    crypto->wpa_versions = version;
    ie += 2; len -= 2;

    /* multicast/group cipher */
    if (len >= 4) {
        crypto->cipher_group = le32_to_cpu(*(__le32*)ie);
        ie += 4; len -= 4;
    }

    /* unicast ciphers */
    if (len >= 2) {
        n = le16_to_cpu(*(__le16*)ie);
        ie += 2; len -= 2;
        if (len < n * 4) {
            net_dbg("RSN ucast cipher data too short; len %u, n %u\n",
                len, n);
            return -EINVAL;
        }
        for (i = 0; i < n; i++) {
            crypto->ciphers_pairwise[crypto->n_ciphers_pairwise++] = le32_to_cpu(*(__le32*)ie);
            ie += 4; len -= 4;
        }

        if (crypto->n_ciphers_pairwise == 0) {
            net_dbg("WPA ucast cipher set empty\n");
            return -EINVAL;
        }
    }

    /* key management algorithms */
    if (len >= 2) {
        n = le16_to_cpu(*(__le16*)ie);
        ie += 2; len -= 2;
        if (len < n * 4) {
            net_dbg("WPA key mgmt alg data too short; len %u, n %u\n",
                len, n);
            return -EINVAL;
        }
        for (i = 0; i < n; i++) {
            crypto->akm_suites[crypto->n_akm_suites++] = le32_to_cpu(*(__le32*)ie);
            ie += 4; len -= 4;
        }
    }

    /* optional capabilities */
    if (len >= 2) {
        net_dbg("WPA capability %u\n", le16_to_cpu(*(__le16*)ie));
        ie += 2; len -= 2;
    }

    return 0;
}

static u32
ieee80211_skip_ie(const u8* ies, u32 ielen, u32 pos)
{
    /* Assume the IE is valid */
    u8 length = ies[pos + 1];

    pos += 2 + length;

    /* the IE must more than 255 bytes for fragments to follow */
    if (length < 255)
        return pos;

    while (pos < ielen && ies[pos] == WLAN_EID_FRAGMENT) {
        length = ies[pos + 1];
        pos += 2 + length;
    }

    return pos;
}

static bool
ieee80211_id_in_list(const u8* ids, int n_ids, u8 id, bool id_ext)
{
    int index;

    /* Make sure the ids array value are legal */
    if (ids[n_ids - 1] == WLAN_EID_EXTENSION)
        return false;

    index = 0;
    while (index < n_ids) {
        if (ids[index] == WLAN_EID_EXTENSION) {
            if (id_ext && (ids[index + 1] == id))
                return true;

            index += 2;
            continue;
        }

        if (ids[index] == id && !id_ext)
            return true;

        index++;
    }
    return false;
}

u32
ieee80211_ie_split_ric(const u8 *ies, u32 ielen,
    const u8 *ids, int n_ids,
    const u8 *after_ric, int n_after_ric,
    u32 offset)
{
    u32 postion = offset;

    while (postion < ielen) {
        u8 ext = 0;

        if (ies[postion] == WLAN_EID_EXTENSION)
            ext = 2;
        if ((postion + ext) >= ielen)
            break;

        if (!ieee80211_id_in_list(ids, n_ids, ies[postion + ext],
            ies[postion] == WLAN_EID_EXTENSION))
            break;

        if (ies[postion] == WLAN_EID_RIC_DATA && n_after_ric) {
            postion = ieee80211_skip_ie(ies, ielen, postion);

            while (postion < ielen) {
                if (ies[postion] == WLAN_EID_EXTENSION)
                    ext = 2;
                else
                    ext = 0;

                if ((postion + ext) >= ielen)
                    break;

                if (!ieee80211_id_in_list(after_ric,
                    n_after_ric,
                    ies[postion + ext],
                    ext == 2))
                    postion = ieee80211_skip_ie(ies, ielen, postion);
                else
                    break;
            }
        }
        else {
            postion = ieee80211_skip_ie(ies, ielen, postion);
        }
    }

    return postion;
}

static int 
net80211_vif_build_preq_ies_band(struct net80211_vif *vif, 
    u8 *buffer,
    u32 buffer_len,
    const u8 *ie, u32 ie_len,
    enum nl80211_band band,
    u32 rate_mask,
    struct ieee80211_chan_def *chandef,
    u32 *offset, u32 flags)
{
    struct ieee80211_supported_band **sband;
    const struct ieee80211_sta_he_cap *he_cap;
    u8 *postion = buffer, *end = buffer + buffer_len;
    u32 noffset;
    u8 supp_rates_len;
    u8 rates[32];
    u8 num_rates;
    u8 ext_rates_len;
    int shift;
    bool have_80mhz = false;
    u32 index;

    *offset = 0;
    sband = net80211_get_sbands(vif->pdev);
    if (!sband)
        return 0;

    shift = ieee80211_chandef_get_shift(chandef);

    num_rates = 0;
    for (index = 0; index < sband[band]->n_bitrates; index++) {
        rates[num_rates++] =
            (u8)DIV_ROUND_UP(sband[band]->bitrates[index].bitrate,
                (1 << shift) * 5);
    }
    supp_rates_len = min_t(int, num_rates, 8);

    if (end - postion < 2 + supp_rates_len)
        goto out_err;
    *postion++ = WLAN_EID_SUPP_RATES;
    *postion++ = supp_rates_len;
    memcpy(postion, rates, supp_rates_len);
    postion += supp_rates_len;

    /* Insert "request information" if custom IEs inclued*/
    if (ie && ie_len) {
        static const u8 before_extrates[] = {
            WLAN_EID_SSID,
            WLAN_EID_SUPP_RATES,
            WLAN_EID_REQUEST,
        };
        noffset = ieee80211_ie_split(ie, ie_len,
            before_extrates,
            ARRAY_SIZE(before_extrates),
            *offset);
        if (end - postion < (u8)(noffset - *offset))
            goto out_err;
        memcpy(postion, ie + *offset, noffset - *offset);
        postion += noffset - *offset;
        *offset = noffset;
    }
    ext_rates_len = num_rates - supp_rates_len;
    if (ext_rates_len > 0) {
        if (end - postion < 2 + ext_rates_len)
            goto out_err;
        *postion++ = WLAN_EID_EXT_SUPP_RATES;
        *postion++ = ext_rates_len;
        memcpy(postion, rates + supp_rates_len, ext_rates_len);
        postion += ext_rates_len;
    }

    if (chandef->chan && sband[band]->band == NL80211_BAND_2GHZ) {
        if (end - postion < 3)
            goto out_err;
        *postion++ = WLAN_EID_DS_PARAMS;
        *postion++ = 1;
        *postion++ = (u8)ieee80211_frequency_to_channel(
            chandef->chan->center_freq);
    }

    /* Insert custom IEs before HT */
    if (ie && ie_len) {
        static const u8 before_ht[] = {
            /* No need to list the ones split off already (or generated here) */
            WLAN_EID_DS_PARAMS,
            WLAN_EID_SUPPORTED_OPERATING_CLASSES,
        };
		
        noffset = ieee80211_ie_split(ie, ie_len,
            before_ht, ARRAY_SIZE(before_ht),
            *offset);
        if (end - postion < (u8)(noffset - *offset))
            goto out_err;
        memcpy(postion, ie + *offset, noffset - *offset);
        postion += noffset - *offset;
        *offset = noffset;
    }

    if (sband[band]->ht_cap.ht_supported) {
        if (end - postion < 2 + sizeof(struct ieee80211_ht_capabilities))
            goto out_err;
        postion = ieee80211_ie_build_ht_cap(postion, &sband[band]->ht_cap,
            sband[band]->ht_cap.cap);
    }
    /* Insert custom IEs before VHT */
    if (ie && ie_len) {
        static const u8 before_vht[] = {
            /* No need to list the ones split off already (or generated here) */
            WLAN_EID_20_40_BSS_COEXISTENCE,
            WLAN_EID_EXT_CAPAB,
            WLAN_EID_SSID_LIST,
            WLAN_EID_CHANNEL_USAGE,
            WLAN_EID_INTERWORKING,
            WLAN_EID_MESH_ID,
            /* 60 GHz (Multi-band, DMG, MMS) can't happen */
        };
		
        noffset = ieee80211_ie_split(ie, ie_len,
            before_vht, ARRAY_SIZE(before_vht),
            *offset);
        if (end - postion < (u8)(noffset - *offset))
            goto out_err;
        memcpy(postion, ie + *offset, noffset - *offset);
        postion += noffset - *offset;
        *offset = noffset;
    }

    /* Check if any channel in this sband supports at least 80 MHz */
    for (index = 0; index < sband[band]->n_channels; index++) {
        if (sband[band]->channels[index].flags & (IEEE80211_CHAN_DISABLED |
            IEEE80211_CHAN_NO_80MHZ))
            continue;

        have_80mhz = true;
        break;
    }

    if (sband[band]->vht_cap.vht_supported && have_80mhz) {
        if (end - postion < 2 + sizeof(struct ieee80211_vht_capabilities))
            goto out_err;
        postion = ieee80211_ie_build_vht_cap(postion, &sband[band]->vht_cap,
            sband[band]->vht_cap.cap);
    }

    /* Insert custom IEs before HE */
    if (ie && ie_len) {
        static const u8 before_he[] = {
            /* No need to list the ones split off before VHT (or generated here) */
            WLAN_EID_EXTENSION, 
            WLAN_EID_EXT_FILS_REQ_PARAMS,
            WLAN_EID_AP_CSN,
            /* TODO: add 11ah/11aj/11ak elements */
        };
		
        noffset = ieee80211_ie_split(ie, ie_len,
            before_he, ARRAY_SIZE(before_he),
            *offset);
        if (end - postion < (u8)(noffset - *offset))
            goto out_err;
        memcpy(postion, ie + *offset, noffset - *offset);
        postion += noffset - *offset;
        *offset = noffset;
    }

    he_cap = ieee80211_get_sta_he_cap(sband[band]);
    if (he_cap) {
        postion = ieee80211_ie_build_he_cap(postion, he_cap, end);
        if (!postion)
            goto out_err;

        if (sband[band]->band == NL80211_BAND_6GHZ) {
            enum nl80211_iftype iftype = net80211_vif_type(vif);
            __le16 cap = ieee80211_get_he_6ghz_cap(sband[band], iftype);
            postion = ieee80211_ie_build_he_6ghz_cap(postion, cap, end);
        }
    }

    net_dbg("band %d, ht_supported %d, vht_supported %d, he_cap 0x%p, have_80mhz %d\n",
        band,
        sband[band]->ht_cap.ht_supported,
        sband[band]->vht_cap.vht_supported, 
        he_cap, have_80mhz);

    return (int)(postion - buffer);

out_err:
    net_err("not enough space for preq IEs\n");
    return (int)(postion - buffer);
}

int 
net80211_vif_build_preq_ies(struct net80211_vif *vif, 
    u8 *buffer,
    u32 buffer_len,
    struct net80211_scan_ies *ie_desc,
    const u8 *ie, u32 ie_len,
    u8 bands_used, u32 *rate_masks,
    struct ieee80211_chan_def *chandef,
    u32 flags)
{
    u32 postion = 0, old_postion = 0, custom_ie_offset = 0;
    int index;

    memset(ie_desc, 0, sizeof(*ie_desc));

    for (index = 0; index < NUM_NL80211_BANDS; index++) {
        if (bands_used & BIT(index)) {
            postion += net80211_vif_build_preq_ies_band(vif,
                buffer + postion,
                buffer_len - postion,
                ie, ie_len, index,
                rate_masks[index],
                chandef,
                &custom_ie_offset,
                flags);
            ie_desc->ies[index] = buffer + old_postion;
            ie_desc->len[index] = postion - old_postion;
            old_postion = postion;
        }
    }

    /* add any remaining custom IEs */
    if (ie && ie_len) {
        if (buffer_len - postion < ie_len - custom_ie_offset) {
            net_err("not enough space for preq custom IEs\n");
            return (int)postion;
        }
        memcpy(buffer + postion, ie + custom_ie_offset,
            ie_len - custom_ie_offset);
        ie_desc->common_ies = buffer + postion;
        ie_desc->common_ie_len = ie_len - custom_ie_offset;
        postion += ie_len - custom_ie_offset;
    }

    return (int)postion;
}

u8*
ieee80211_ie_build_wpa(u8 *pos, struct net80211_crypto_settings *crypto)
{
    u32 oui = __cpu_to_be32(WLAN_OUI_MICROSOFT_WPA);
    u8 *orig_pos = pos;
    u8 i;

    if (!pos || !crypto || !crypto->wpa_type)
        return orig_pos;

    *pos++ = WLAN_EID_VENDOR_SPECIFIC;
    *pos++ = 0;                /* length filled in below */
    memcpy(pos, &oui, 4);
    pos += 4;

    /* version */
    memcpy(pos, &crypto->wpa_versions, 2);
    pos += 2;

    /* multicast/group cipher */
    memcpy(pos, &crypto->cipher_group, 4);
    pos += 4;

    /* unicast ciphers */
    memcpy(pos, &crypto->n_ciphers_pairwise, 2);
    pos += 2;
    for (i = 0; i < crypto->n_ciphers_pairwise; i++) {
        memcpy(pos, &crypto->ciphers_pairwise[i], 4);
        pos += 4;
    }

    /* key management algorithms */
    memcpy(pos, &crypto->n_akm_suites, 2);
    pos += 2;
    for (i = 0; i < crypto->n_akm_suites; i++) {
        memcpy(pos, &crypto->akm_suites[i], 4);
        pos += 4;
    }

    /* capability */ // TODOTODO: Add PMF support
    pos += 2;

    orig_pos[1] = (u8)((pos - orig_pos) - 2);
    return pos;
}

int
ieee80211_parse_rsn_ie(const u8 *ie, struct net80211_crypto_settings *crypto)
{
    u16 len;
    u16 i, n;
    u16 version;

    if (ie == NULL)
        return -EINVAL;

    len = ie[1];
    if (len < 2) {
        net_dbg("RSN IE is too short, len %u\n", len);
        return -EINVAL;
    }
    else {
        net_dbg("RSN IE len %u\n", len);
    }
    ie += 2;

    memset(crypto, 0, sizeof(*crypto));
    crypto->wpa_type = IEEE80211_WPA_TYPE_RSN;

    /* version */
    version = le16_to_cpu(*(__le16*)ie);
    if (version != 1) {
        net_dbg("RSN bad version %u\n", version);
        return -EINVAL;
    }
    crypto->wpa_versions = version;
    ie += 2; len -= 2;

    /* multicast/group cipher */
    if (len >= 4) {
        crypto->cipher_group = le32_to_cpu(*(__le32*)ie);
        ie += 4; len -= 4;
    }

    /* unicast ciphers */
    if (len >= 2) {
        n = le16_to_cpu(*(__le16*)ie);
        ie += 2; len -= 2;
        if (len < n * 4) {
            net_dbg("RSN ucast cipher data too short; len %u, n %u\n",
                len, n);
            return -EINVAL;
        }
        for (i = 0; i < n; i++) {
            net_dbg("crypto->ciphers_pairwise[%d] = %08X\n", 
                crypto->n_ciphers_pairwise, le32_to_cpu(*(__le32*)ie));
            crypto->ciphers_pairwise[crypto->n_ciphers_pairwise++] = le32_to_cpu(*(__le32*)ie);
            ie += 4; len -= 4;
        }
        if (crypto->n_ciphers_pairwise == 0) {
            net_dbg("RSN ucast cipher set empty\n");
            return -EINVAL;
        }
    }

    /* key management algorithms */
    if (len >= 2) {
        n = le16_to_cpu(*(__le16*)ie);
        ie += 2; len -= 2;
        if (len < n * 4) {
            net_dbg("RSN key mgmt alg data too short; len %u, n %u\n",
                len, n);
            return -EINVAL;
        }
        for (i = 0; i < n; i++) {
            net_dbg("crypto->akm_suites[%d] = %08X\n",
                crypto->n_akm_suites, le32_to_cpu(*(__le32*)ie));
            crypto->akm_suites[crypto->n_akm_suites++] = le32_to_cpu(*(__le32*)ie);
            ie += 4; len -= 4;
        }
    }
    /* optional capabilities */
    if (len >= 2) {
        n = le16_to_cpu(*(__le16*)ie);
        net_dbg("RSN capabilities 0x%02X\n", n);
        crypto->mfp = n & (IEEE80211_RSN_CAP_MFP_ENABLED | IEEE80211_RSN_CAP_MFP_REQUIRED);
        ie += 2; len -= 2;
    }
    /*pmkid*/
    if (len >= 2) {
        n = le16_to_cpu(*(__le16*)ie);
        ie += 2; len -= 2;
    }
    /* group mgmt cipher suite*/
    if (len >= 4) {
        crypto->group_mgmt_cipher_suite = le32_to_cpu(*(__le32*)ie);
        net_dbg("group_mgmt_cipher_suite 0x%x\n", crypto->group_mgmt_cipher_suite);
        ie += 4; len -= 4;
    }

    return 0;
}

u8*
ieee80211_ie_build_rsn(u8 *pos, struct net80211_crypto_settings *crypto)
{
    u8 *orig_pos = pos;
    u8 i;
    u16 rsn_cap = 0;

    if (!pos || !crypto || !crypto->wpa_type)
        return orig_pos;

    *pos++ = WLAN_EID_RSN;
    *pos++ = 0;                /* length filled in below */

    /* version */
    memcpy(pos, &crypto->wpa_versions, 2);
    pos += 2;

    /* multicast/group cipher */
    memcpy(pos, &crypto->cipher_group, 4);
    pos += 4;

    /* unicast ciphers */
    memcpy(pos, &crypto->n_ciphers_pairwise, 2);
    pos += 2;
    for (i = 0; i < crypto->n_ciphers_pairwise; i++) {
        memcpy(pos, &crypto->ciphers_pairwise[i], 4);
        pos += 4;
    }

    /* key management algorithms */
    memcpy(pos, &crypto->n_akm_suites, 2);
    pos += 2;
    for (i = 0; i < crypto->n_akm_suites; i++) {
        memcpy(pos, &crypto->akm_suites[i], 4);
        pos += 4;
    }

    /* capability */ 
    if (crypto->mfp & IEEE80211_RSN_CAP_MFP_ENABLED) {
        rsn_cap |= crypto->mfp;
        memcpy(pos, &rsn_cap, 2);
    }
    pos += 2;
    if (crypto->group_mgmt_cipher_suite) {
        net_dbg("build ext pmkid and gmc in rsn ies\n");
        /*pmkid*/
        pos += 2;

        /* group mgmt cipher suite*/
        memcpy(pos, &crypto->group_mgmt_cipher_suite, 4);
        pos += 4;
    }

    orig_pos[1] = (u8)((pos - orig_pos) - 2);
    return pos;
}

int
ieee80211_parse_rsnxe_ie(const u8 *ie, struct net80211_crypto_settings *crypto)
{
    u8 len;

    if (ie == NULL)
        return -EINVAL;

    len = ie[1];
    if (len < 1) {
        net_dbg("RSNXE IE is too short, len %u\n", len);
        return -EINVAL;
    }
    ie += 2;

    crypto->rsnxe_cap = ie[0];

    return 0;
}

u8*
ieee80211_ie_build_rsnxe(u8 *pos, struct net80211_crypto_settings *crypto)
{
    if (!pos || !crypto || !crypto->wpa_type)
        return pos;

    *pos++ = WLAN_EID_RSNX;
    *pos++ = 1;

    memcpy(pos, &crypto->rsnxe_cap, 1);

    return pos;
}

struct ieee80211_channel *
net80211_get_channel(struct net80211_pdev *pdev, u32 freq)
{
    enum nl80211_band band;
    const struct ieee80211_supported_band *sband;
    u32 i;

    band = ieee80211_frequency_to_band(freq);
    sband = net80211_get_sband(pdev, band);
    if (!sband)
        return NULL;

    for (i = 0; i < sband->n_channels; i++) {
        if (sband->channels[i].center_freq == freq)
            return &sband->channels[i];
    }

    return NULL;
}

u32
net80211_get_scan_channel_num(struct net80211_pdev *pdev)
{
	u32 i = 0;
	u32 num_channels = 0;
	struct ieee80211_channel *channel;
	enum nl80211_band band;
	struct ieee80211_supported_band **supported_bands;

	supported_bands = net80211_get_sbands(pdev);
	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		if (!supported_bands[band])
			continue;
		
		/* 6GHZ requires SAE or SUITEB */
        if (NL80211_BAND_6GHZ == band && !net80211_is_sae_suiteb_supported(pdev))
            continue;
		
		for (i = 0; i < supported_bands[band]->n_channels; i++) {
			channel = &supported_bands[band]->channels[i];

			if (channel->flags & IEEE80211_CHAN_DISABLED)
				continue;

			num_channels++;
		}
	}

	return num_channels;
}

u32
net80211_get_scan_channels(struct net80211_pdev *pdev, struct ieee80211_channel **channels, u32 nchannels)
{
	u32 i = 0;
	u32 num_channels = 0;
	struct ieee80211_channel *channel;
	enum nl80211_band band;
	struct ieee80211_supported_band **supported_bands;

	supported_bands = net80211_get_sbands(pdev);
	for (band = 0; band < NUM_NL80211_BANDS; band++) {
		if (!supported_bands[band])
			continue;
		
        /* 6GHZ requires SAE or SUITEB */
        if (NL80211_BAND_6GHZ == band && !net80211_is_sae_suiteb_supported(pdev))
            continue;

		for (i = 0; i < supported_bands[band]->n_channels; i++) {
			channel = &supported_bands[band]->channels[i];
			if (channel->flags & IEEE80211_CHAN_DISABLED)
				continue;

            if (num_channels >= nchannels)
                break;

			channels[num_channels++] = channel;
		}
	}

	return num_channels;
}

bool net80211_channel_is_psc(const struct ieee80211_channel *chan)
{
	if (chan->band != NL80211_BAND_6GHZ)
		return false;

	return ieee80211_frequency_to_channel(chan->center_freq) % 16 == 5;
}

void net80211_vif_regulatory_limit_wmm_params(struct net80211_vif *vif,
    u16 ac, struct ieee80211_tx_queue_params *txq_params)
{
    struct ieee80211_chanctx_conf *chanctx_conf;
    const struct ieee80211_reg_rule *reg_rule;
    const struct ieee80211_wmm_ac *wmm_ac;
    u32 center_freq = 0;

    chanctx_conf = vif->chanctx_conf;
    center_freq = chanctx_conf ? chanctx_conf->def.chan->center_freq : 0;

    if (!center_freq) {
        return;
    }

    reg_rule = freq_reg_info(vif->pdev, MHZ_TO_KHZ(center_freq));

    if (IS_ERR_OR_NULL(reg_rule) || !reg_rule->has_wmm) {
        return;
    }

    if (vif->type == NL80211_IFTYPE_AP)
        wmm_ac = &reg_rule->wmm_rule.ap[ac];
    else
        wmm_ac = &reg_rule->wmm_rule.client[ac];
    txq_params->cw_min = max_t(u16, txq_params->cw_min, wmm_ac->cw_min);
    txq_params->cw_max = max_t(u16, txq_params->cw_max, wmm_ac->cw_max);
    txq_params->aifs = max_t(u8, txq_params->aifs, wmm_ac->aifsn);
    txq_params->txop = min_t(u16, txq_params->txop, wmm_ac->cot / 32);
}

static void net80211_vif_drv_conf_tx(struct net80211_vif *vif, 
    u16 ac, struct ieee80211_tx_queue_params *txq_params)
{
    struct net80211_pdev *pdev = vif->pdev;

    /* TODO: is it needed? */
    net80211_vif_regulatory_limit_wmm_params(vif, ac, txq_params);

    drv_conf_tx(pdev, vif, ac, txq_params);
}

void net80211_vif_set_wmm_default(struct net80211_vif *vif, 
    bool bss_notify, bool enable_qos)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct ieee80211_tx_queue_params *txq_params;
    struct ieee80211_chanctx_conf *chanctx_conf;
    bool use_11b;
    u16 aCWmin, aCWmax;

    if (!pdev->ops->ieee80211_conf_tx)
        return;

    chanctx_conf = vif->chanctx_conf;
    use_11b = (chanctx_conf && 
        chanctx_conf->def.chan->band == NL80211_BAND_2GHZ &&
        !vif->only_g_mode);

    aCWmax = 1023;
    aCWmin = use_11b ? 31 : 15;

    /* BK */
    txq_params = &vif->tx_conf[IEEE80211_AC_BK];
    memset(txq_params, 0, sizeof(*txq_params));
    txq_params->cw_max = aCWmax;
    txq_params->cw_min = aCWmin;
    if (enable_qos) {
        txq_params->txop = 0;
        txq_params->aifs = 7;
    }
    else {
        txq_params->txop = 0;
        txq_params->aifs = 2;
    }
    net80211_vif_drv_conf_tx(vif, IEEE80211_AC_BK, txq_params);

    /* BE */
    txq_params = &vif->tx_conf[IEEE80211_AC_BE];
    memset(txq_params, 0, sizeof(*txq_params));
    txq_params->cw_max = aCWmax;
    txq_params->cw_min = aCWmin;
    if (enable_qos) {
        txq_params->txop = 0;
        txq_params->aifs = 3;
    }
    else {
        txq_params->txop = 0;
        txq_params->aifs = 2;
    }
    net80211_vif_drv_conf_tx(vif, IEEE80211_AC_BE, txq_params);

    /* VI */
    txq_params = &vif->tx_conf[IEEE80211_AC_VI];
    memset(txq_params, 0, sizeof(*txq_params));
    if (enable_qos) {
        txq_params->cw_max = aCWmin;
        txq_params->cw_min = (aCWmin + 1) / 2 - 1;
        txq_params->txop = use_11b ? (6016 / 32) : (3008 / 32);;
        txq_params->aifs = 2;
    }
    else {
        txq_params->cw_max = aCWmax;
        txq_params->cw_min = aCWmin;
        txq_params->txop = 0;
        txq_params->aifs = 2;
    }
    net80211_vif_drv_conf_tx(vif, IEEE80211_AC_VI, txq_params);

    /* VO */
    txq_params = &vif->tx_conf[IEEE80211_AC_VO];
    memset(txq_params, 0, sizeof(*txq_params));
    if (enable_qos) {
        txq_params->cw_max = (aCWmin + 1) / 2 - 1;
        txq_params->cw_min = (aCWmin + 1) / 4 - 1;
        txq_params->txop = use_11b ? (3264 / 32) : (1504 / 32);
        txq_params->aifs = 2;
    }
    else {
        txq_params->cw_max = aCWmax;
        txq_params->cw_min = aCWmin;
        txq_params->txop = 0;
        txq_params->aifs = 2;
    }
    net80211_vif_drv_conf_tx(vif, IEEE80211_AC_VO, txq_params);

    net80211_vif_bss_conf_set_qos(vif, enable_qos);
    if (bss_notify) {
        net80211_vif_bss_conf_change_notify(vif);
    }
}

bool
net80211_vif_set_wmm_params(
    struct net80211_vif *vif,
    const u8 *wmm_param, u8 wmm_param_len,
    const struct ieee80211_he_mu_edca_param_set *mu_edca)
{
    struct net80211_pdev *pdev = vif->pdev;
    struct net80211_mlme_conf *mlme_conf = net80211_sta_get_mlme_conf(vif);
    struct ieee80211_tx_queue_params txq_params[IEEE80211_NUM_OF_ACS] = { 0 };
    u8 remaining;
    int count, mu_edca_count;
    u16 ac;
    const u8 *pos;
    u8 uapsd_queues = 0;

    if (!pdev->ops->ieee80211_conf_tx)
        return false;

    if (net80211_get_hw_queues(pdev) < IEEE80211_NUM_OF_ACS)
        return false;

    if (!wmm_param)
        return false;

    if (wmm_param_len < 8 || wmm_param[5] /* version */ != 1)
        return false;

    if (mlme_conf->flags & NET80211_MLME_UAPSD_ENABLED)
        uapsd_queues = mlme_conf->uapsd_queues;

    count = wmm_param[6] & 0x0f;
    mu_edca_count = mu_edca ? mu_edca->he_qos_info & 0x0f : -1;
    /* don't tell driver if it is set before */
    if (count == mlme_conf->wmm_param_last_set &&
        mu_edca_count == mlme_conf->mu_edca_param_last_set)
        return false;

    mlme_conf->wmm_param_last_set = count;
    mlme_conf->mu_edca_param_last_set = mu_edca_count;

    pos = wmm_param + 8;
    remaining = wmm_param_len - 8;

    for (; remaining >= 4; remaining -= 4, pos += 4) {
        u8 aci = (pos[0] >> 5) & 0x03;
        u8 acm = (pos[0] >> 4) & 0x01;

        switch (aci) {
        case 1: /* AC_BK */
            ac = IEEE80211_AC_BK;
            txq_params[ac].uapsd = 
                !!(uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_BK);
            txq_params[ac].mu_edca = !!mu_edca;
            if (mu_edca)
                txq_params[ac].mu_edca_param_record = mu_edca->ac_bk;
            break;
        case 2: /* AC_VI */
            ac = IEEE80211_AC_VI;
            txq_params[ac].uapsd = 
                !!(uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_VI);
            txq_params[ac].mu_edca = !!mu_edca;
            if (mu_edca)
                txq_params[ac].mu_edca_param_record = mu_edca->ac_vi;
            break;
        case 3: /* AC_VO */
            ac = IEEE80211_AC_VO;
            txq_params[ac].uapsd = 
                !!(uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_VO);
            txq_params[ac].mu_edca = !!mu_edca;
            if (mu_edca)
                txq_params[ac].mu_edca_param_record = mu_edca->ac_vo;
            break;
        case 0: /* AC_BE */
        default:
            ac = IEEE80211_AC_BE;
            txq_params[ac].uapsd = 
                !!(uapsd_queues & IEEE80211_WMM_IE_STA_UAPSD_BE);
            txq_params[ac].mu_edca = !!mu_edca;
            if (mu_edca)
                txq_params[ac].mu_edca_param_record = mu_edca->ac_be;
            break;
        }

        txq_params[ac].aifs = pos[0] & 0x0f;
        if (txq_params[ac].aifs < 2) {
            net_warn("Invalid WMM params (AIFSN=%d for ACI %d), will use 2\n",
                txq_params[ac].aifs, aci);
            txq_params[ac].aifs = 2;
        }
        txq_params[ac].cw_max = (u16)ecw2cw((pos[1] & 0xf0) >> 4);
        txq_params[ac].cw_min = (u16)ecw2cw(pos[1] & 0x0f);
        txq_params[ac].txop = *(u16 *)(pos + 2);
        txq_params[ac].acm = !!acm;

        if (txq_params[ac].cw_min == 0 ||
            txq_params[ac].cw_min > txq_params[ac].cw_max) {
            net_warn("Invalid WMM params (CWmin/CWmax=%d/%d for ACI %d), using defaults\n",
                txq_params[ac].cw_min, txq_params[ac].cw_max, aci);
            return false;
        }
        net80211_vif_regulatory_limit_wmm_params(vif, ac, &txq_params[ac]);
    }

    /* All 4 ACIs is required */
    for (ac = 0; ac < IEEE80211_NUM_OF_ACS; ac++) {
        if (txq_params[ac].cw_min == 0) {
            net_warn("Invalid WMM params (missing AC %d), using defaults\n",
                ac);
            return false;
        }
    }

    for (ac = 0; ac < IEEE80211_NUM_OF_ACS; ac++) {
        net_dbg("WMM AC=%d acm=%d aifs=%d cWmin=%d cWmax=%d txop=%d uapsd=%d\n",
            ac, txq_params[ac].acm,
            txq_params[ac].aifs, txq_params[ac].cw_min, txq_params[ac].cw_max,
            txq_params[ac].txop, txq_params[ac].uapsd);
        vif->tx_conf[ac] = txq_params[ac];
        if (drv_conf_tx(pdev, vif, ac, &txq_params[ac]))
            net_warn("failed to set TX queue parameters for AC %d\n", ac);
    }

    /* enable qos */
    net80211_vif_bss_conf_set_qos(vif, true);
    return true;
}

u8 *ieee80211_add_wmm_info_ie(u8 *buf, u8 qosinfo)
{
    struct ieee80211_wmm_ie *wmmie = (void *)buf;

    buf += sizeof(*wmmie);

    wmmie->element_id = WLAN_EID_VENDOR_SPECIFIC;
    wmmie->length = (u8)(buf - &wmmie->oui[0]);
    wmmie->oui[0] = 0x00;
    wmmie->oui[1] = 0x50;
    wmmie->oui[2] = 0xf2;
    wmmie->oui_type = 2; /* WME */
    wmmie->subtype = 0;
    wmmie->version = 1;
    wmmie->qosinfo = qosinfo;

    return buf;
}

u8 ieee80211_ac_to_qos_mask(u8 ac)
{
    static const u8 ieee80211_ac_to_qos_masks[] = {
        IEEE80211_WMM_IE_STA_UAPSD_VO,
        IEEE80211_WMM_IE_STA_UAPSD_VI,
        IEEE80211_WMM_IE_STA_UAPSD_BE,
        IEEE80211_WMM_IE_STA_UAPSD_BK
    };

    u8 qos = IEEE80211_WMM_IE_STA_UAPSD_BE;
    if (ac < ARRAY_LENGTH(ieee80211_ac_to_qos_masks))
        qos = ieee80211_ac_to_qos_masks[ac];

    return qos;
}

u32 ieee80211_parse_bitrates(struct ieee80211_chan_def *chandef,
    const struct ieee80211_supported_band *sband,
    const u8 *supp_rates, u32 supp_rates_len, u32 *rates)
{
    u32 rate_flags;
    int shift;
    struct ieee80211_rate *arate;
    u32 bitrate, rate;
    u32 i, n;
    u32 count = 0;

    *rates = 0;

    /* ap doesn't provide supported rates, use all supported */
    if (!supp_rates || !supp_rates_len) {
        for (n = 0; n < sband->n_bitrates; n++) {
            *rates |= BIT(n);
            count++;
        }
    }
    else {
        rate_flags = ieee80211_chandef_rate_flags(chandef);
        shift = ieee80211_chandef_get_shift(chandef);

        for (i = 0; i < supp_rates_len; i++) {
            rate = supp_rates[i] & 0x7f;
            for (n = 0; n < sband->n_bitrates; n++) {
                arate = &sband->bitrates[n];
                if ((rate_flags & arate->flags) != rate_flags)
                    continue;
                bitrate = DIV_ROUND_UP(arate->bitrate, (1 << shift) * 5);
                if (bitrate == rate) {
                    *rates |= BIT(n);
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}

bool
net80211_bss_get_dtim(struct net80211_bss *bss,
    u8 *dtim_count, u8 *dtim_period)
{
    const u8 *tim_ie;
    const u8 *idx_ie;

    const struct ieee80211_tim *tim;
    const struct ieee80211_bssid_index *idx;

    /* DTIM is overriden by non-transmitted profile */
    idx_ie = net80211_bss_find_ie(bss, WLAN_EID_MULTIPLE_BSSID_INDEX);
    if (idx_ie && idx_ie[1] >= 3) {
        idx = (void *)(idx_ie + 2);
        if (dtim_count)
            *dtim_count = idx->dtim_count;

        if (dtim_period)
            *dtim_period = idx->dtim_period;
        return true;
    }

    tim_ie = net80211_bss_find_ie(bss, WLAN_EID_TIM);
    if (tim_ie && tim_ie[1] >= 2) {
        tim = (void *)(tim_ie + 2);
        if (dtim_count)
            *dtim_count = tim->dtim_count;
        if (dtim_period)
            *dtim_period = tim->dtim_period;

        return true;
    }

    return false;
}

#define case_WLAN_REASON(type) \
	case WLAN_REASON_##type: return #type
const char *
ieee80211_get_reason_code_string(u16 reason_code)
{
    switch (reason_code) {
        case_WLAN_REASON(UNSPECIFIED);
        case_WLAN_REASON(PREV_AUTH_NOT_VALID);
        case_WLAN_REASON(DEAUTH_LEAVING);
        case_WLAN_REASON(DISASSOC_DUE_TO_INACTIVITY);
        case_WLAN_REASON(DISASSOC_AP_BUSY);
        case_WLAN_REASON(CLASS2_FRAME_FROM_NONAUTH_STA);
        case_WLAN_REASON(CLASS3_FRAME_FROM_NONASSOC_STA);
        case_WLAN_REASON(DISASSOC_STA_HAS_LEFT);
        case_WLAN_REASON(STA_REQ_ASSOC_WITHOUT_AUTH);
        case_WLAN_REASON(PWR_CAPABILITY_NOT_VALID);
        case_WLAN_REASON(SUPPORTED_CHANNEL_NOT_VALID);
        case_WLAN_REASON(INVALID_IE);
        case_WLAN_REASON(MICHAEL_MIC_FAILURE);
        case_WLAN_REASON(4WAY_HANDSHAKE_TIMEOUT);
        case_WLAN_REASON(GROUP_KEY_UPDATE_TIMEOUT);
        case_WLAN_REASON(IE_IN_4WAY_DIFFERS);
        case_WLAN_REASON(GROUP_CIPHER_NOT_VALID);
        case_WLAN_REASON(PAIRWISE_CIPHER_NOT_VALID);
        case_WLAN_REASON(AKMP_NOT_VALID);
        case_WLAN_REASON(UNSUPPORTED_RSN_IE_VERSION);
        case_WLAN_REASON(INVALID_RSN_IE_CAPAB);
        case_WLAN_REASON(IEEE_802_1X_AUTH_FAILED);
        case_WLAN_REASON(CIPHER_SUITE_REJECTED);
        case_WLAN_REASON(UNSPECIFIED_QOS_REASON);
        case_WLAN_REASON(NOT_ENOUGH_BANDWIDTH);
        case_WLAN_REASON(DISASSOC_LOW_ACK);
        case_WLAN_REASON(EXCEEDED_TXOP);
        case_WLAN_REASON(STA_LEAVING);
        case_WLAN_REASON(END_TS_BA_DLS);
        case_WLAN_REASON(UNKNOWN_TS_BA);
        case_WLAN_REASON(TIMEOUT);
        case_WLAN_REASON(PEERKEY_MISMATCH);
        case_WLAN_REASON(MESH_PEERING_CANCELLED);
        case_WLAN_REASON(MESH_MAX_PEERS);
        case_WLAN_REASON(MESH_CONFIG_POLICY_VIOLATION);
        case_WLAN_REASON(MESH_CLOSE_RCVD);
        case_WLAN_REASON(MESH_MAX_RETRIES);
        case_WLAN_REASON(MESH_CONFIRM_TIMEOUT);
        case_WLAN_REASON(MESH_INVALID_GTK);
        case_WLAN_REASON(MESH_INCONSISTENT_PARAMS);
        case_WLAN_REASON(MESH_INVALID_SECURITY_CAP);
        case_WLAN_REASON(MESH_PATH_ERROR_NO_PROXY_INFO);
        case_WLAN_REASON(MESH_PATH_ERROR_NO_FORWARDING_INFO);
        case_WLAN_REASON(MESH_PATH_ERROR_DEST_UNREACHABLE);
        case_WLAN_REASON(MAC_ADDRESS_ALREADY_EXISTS_IN_MBSS);
        case_WLAN_REASON(MESH_CHANNEL_SWITCH_REGULATORY_REQ);
        case_WLAN_REASON(MESH_CHANNEL_SWITCH_UNSPECIFIED);
    default:
        return "<unknown>";
    }
}