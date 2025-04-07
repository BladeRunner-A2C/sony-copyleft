/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#include "wpas_glue.h"
#include "utils/eloop.h"
#include "crypto/sha1.h"
#include "crypto/crypto.h"
#include "utils/list.h"
#include "eapol_supp/eapol_supp_sm.h"
#include "WlanSupplicant.h"
#include "Utils.h"
#include "Debug.h"

int wpa_debug_level = MSG_DEBUG;

/* eloop support */
static struct eloop_registration {
    eloop_timeout_handler handler;
    void *eloop_data;
    void *user_data;
    u64 timeout_usecs;
} g_eloop_registration = { 0 };

int eloop_cancel_timeout(eloop_timeout_handler handler,
    void *eloop_data, void *user_data)
{
    /* registration context */
    struct eloop_registration *registration = &g_eloop_registration;

    if (handler == registration->handler &&
        eloop_data == registration->eloop_data &&
        user_data == registration->user_data) {
        registration->handler = NULL;
        registration->eloop_data = NULL;
        registration->user_data = NULL;
    }

    return 0;
}

int eloop_register_timeout(unsigned int secs, unsigned int usecs,
    eloop_timeout_handler handler,
    void *eloop_data, void *user_data)
{
    /* registration context */
    struct eloop_registration *registration = &g_eloop_registration;

    if ((secs == 0) && (usecs == 0))
        return -1;
    if (registration->handler != NULL)
        return -1;

	registration->handler = handler;
	registration->eloop_data = eloop_data;
	registration->user_data = user_data;
	registration->timeout_usecs = getwalltime_us() + usecs + secs * 1000;

    return 0;
}

void eloop_timer_tick(void)
{
    /* registration context */
    struct eloop_registration *registration = &g_eloop_registration;
    eloop_timeout_handler handler;
    void *eloop_data, *user_data;

    if (!registration->handler)
        return;

    if (getwalltime_us() < registration->timeout_usecs) {
        return;
    }
	
	handler = registration->handler;
	eloop_data = registration->eloop_data;
	user_data = registration->user_data;

    eloop_cancel_timeout(handler, eloop_data, user_data);
    handler(eloop_data, user_data);
}

/* wpas implementation */

int wpas_register(void)
{
    int ret;

    ret = eap_peer_tls_register();
    if (ret) {
        return ret;
    }

    ret = eap_peer_mschapv2_register();
    if (ret) {
        return ret;
    }

    ret = eap_peer_peap_register();
    if (ret) {
        return ret;
    }

    ret = eap_peer_ttls_register();
    if (ret) {
        return ret;
    }

    return 0;
}

static int wpas_ether_send(void *ctx, const u8 *dest, u16 proto, const u8 *buf,
    size_t len)
{
    struct wpas *wpas = ctx;
    u8 *resp_buf;

    if (wpas->resp_eapol == NULL || wpas->resp_eapol_len == NULL) {
        return -1;
    }

    resp_buf = wpas->resp_eapol;
    os_memcpy(resp_buf, wpas->auth_addr, ETH_ALEN);
    resp_buf += ETH_ALEN;
    os_memcpy(resp_buf, wpas->own_addr, ETH_ALEN);
    resp_buf += ETH_ALEN;
    *((u16*)resp_buf) = htons(proto);
    resp_buf += sizeof(proto);
    os_memcpy(resp_buf, buf, len);
    *(wpas->resp_eapol_len) = len + ETH_HLEN;

    wpa_hexdump(MSG_DEBUG, "tx eapol", wpas->resp_eapol, *wpas->resp_eapol_len);

    wpas->resp_eapol = NULL;
    wpas->resp_eapol_len = NULL;

    return 0;
}

static u8 *wpas_alloc_eapol(void *ctx, u8 type, const void *data,
    u16 data_len, size_t *msg_len, void **data_pos)
{
    struct ieee802_1x_hdr *hdr;

    wpa_printf(MSG_DEBUG, "type=%d data_len=%d", type, data_len);

    *msg_len = sizeof(*hdr) + data_len;
    hdr = os_malloc(*msg_len);
    if (hdr == NULL)
        return NULL;

    hdr->version = 2;
    hdr->type = type;
    hdr->length = host_to_be16(data_len);

    if (data)
        os_memcpy(hdr + 1, data, data_len);
    else
        os_memset(hdr + 1, 0, data_len);

    if (data_pos)
        *data_pos = hdr + 1;

    return (u8 *)hdr;
}

static void wpas_initiate_eapol(struct wpas *wpas, struct eap_peer_config *eap)
{
    struct eapol_config eapol_conf;

    eapol_sm_notify_eap_success(wpas->eapol, FALSE);
    eapol_sm_notify_eap_fail(wpas->eapol, FALSE);
    eapol_sm_notify_portControl(wpas->eapol, Auto);
    eapol_sm_notify_portEnabled(wpas->eapol, FALSE);
    eapol_sm_notify_portValid(wpas->eapol, FALSE);

    os_memset(&eapol_conf, 0, sizeof(eapol_conf));
    eapol_conf.fast_reauth = 0;
    eapol_conf.workaround = 0;
    eapol_conf.eap_disabled = 0;
    eapol_conf.external_sim = 0;

    eapol_sm_notify_config(wpas->eapol, eap, &eapol_conf);

    eapol_sm_notify_portEnabled(wpas->eapol, TRUE);
    eapol_sm_notify_portValid(wpas->eapol, TRUE);
}

static int wpas_eapol_send(void *ctx, int type, const u8 *buf, size_t len)
{
    struct wpas *wpas = ctx;
    u8 *msg, *dst = wpas->auth_addr;
    size_t msglen;
    int res;

    msg = wpas_alloc_eapol(wpas, type, buf, len, &msglen, NULL);
    if (msg == NULL)
        return -1;

    res = wpas_ether_send(wpas, dst, ETH_P_EAPOL, msg, msglen);
    os_free(msg);
    return res;
}

static void wpas_eapol_cb(struct eapol_sm *eapol,
    enum eapol_supp_result result,
    void *ctx)
{
    struct wpas *wpas = ctx;

    if (result == EAPOL_SUPP_RESULT_EXPECTED_FAILURE)
        return;

    if (result != EAPOL_SUPP_RESULT_SUCCESS) {
        if (wpas->ops->eapol_complete)
            wpas->ops->eapol_complete(wpas->parent, 0);

        wpa_debug_flush();
        return;
    }

    if (eapol_sm_get_key(eapol, wpas->pmk, PMK_LEN)) {
        wpa_debug_flush();
        return;
    }

    wpas->pmk_set = 1;

    if (wpas->ops->eapol_complete)
        wpas->ops->eapol_complete(wpas->parent, 1);

    wpa_debug_flush();
}

static void wpas_set_config_blob(void *ctx, struct wpa_config_blob *blob)
{
}

static const struct wpa_config_blob *
wpas_get_config_blob(void *ctx, const char *name)
{
    struct wpas *wpas = ctx;

    if (!os_strcmp(name, "ca_cert"))
        return &wpas->ca_cert_blob;
    else if (!os_strcmp(name, "client_cert"))
        return &wpas->client_cert_blob;
    else if (!os_strcmp(name, "priv_key"))
        return &wpas->priv_key_blob;

    return NULL;
}

int wpas_init_eapol_sm(struct wpas *wpas)
{
    struct eapol_ctx *ctx;

    ctx = os_zalloc(sizeof(*ctx));
    if (ctx == NULL) {
        return -1;
    }

    ctx->ctx = wpas;
    ctx->msg_ctx = wpas;
    ctx->eapol_send_ctx = wpas;
    ctx->preauth = 0;
    ctx->eapol_send = wpas_eapol_send;
    ctx->cb = wpas_eapol_cb;
    ctx->set_config_blob = wpas_set_config_blob;
    ctx->get_config_blob = wpas_get_config_blob;
    ctx->cb_ctx = wpas;

    wpas->eapol = eapol_sm_init(ctx);
    if (wpas->eapol == NULL) {
        os_free(ctx);
        return -1;
    }

    os_memset(&wpas->eap, 0, sizeof(wpas->eap));
    wpas->ca_cert_blob.name = "ca_cert";
    wpas->client_cert_blob.name = "client_cert";
    wpas->priv_key_blob.name = "priv_key";
    return 0;
}

static void *wpas_get_network_ctx(void *arg)
{
    return (void *)1;
}

static void wpas_set_state(void *ctx, enum wpa_states state)
{
}

static int wpas_get_bssid(void *ctx, u8 *bssid)
{
    struct wpas *wpas = ctx;
    os_memcpy(bssid, wpas->auth_addr, ETH_ALEN);
    return 0;
}

static bool wpa_alg_to_cipher_suite(enum wpa_alg alg, size_t key_len, EFI_80211_SUITE_SELECTOR *suiteSelector)
{
    static const EFI_80211_SUITE_SELECTOR TkipCipherSuite = {
        .Oui = { 0x00, 0x0F, 0xAC },
        .SuiteType = 2,
    };

    static const EFI_80211_SUITE_SELECTOR CcmpCipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 4,
    };

    static const EFI_80211_SUITE_SELECTOR AesCmacCipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 6,
    };

    static const EFI_80211_SUITE_SELECTOR GcmpCipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 8,
    };
    static const EFI_80211_SUITE_SELECTOR Gcmp256CipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 9,
    };
    static const EFI_80211_SUITE_SELECTOR Ccmp256CipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 10,
    };
    static const EFI_80211_SUITE_SELECTOR BIPGmac128CipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 11,
    };
    static const EFI_80211_SUITE_SELECTOR BIPGmac256CipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 12,
    };
    static const EFI_80211_SUITE_SELECTOR BIPCmac256CipherSuite = {
      .Oui = { 0x00, 0x0F, 0xAC },
      .SuiteType = 13,
    };

    const EFI_80211_SUITE_SELECTOR *standardSuiteSelector = NULL;

    switch (alg) {
    case WPA_ALG_TKIP:
        standardSuiteSelector = &TkipCipherSuite;
        break;
    case WPA_ALG_CCMP:
        standardSuiteSelector = &CcmpCipherSuite;
        break;
    case WPA_ALG_GCMP:
        standardSuiteSelector = &GcmpCipherSuite;
        break;
    case WPA_ALG_BIP_CMAC_128:
        standardSuiteSelector = &AesCmacCipherSuite;
        break;
    case WPA_ALG_GCMP_256:
        standardSuiteSelector = &Gcmp256CipherSuite;
        break;
    case WPA_ALG_CCMP_256:
        standardSuiteSelector = &Ccmp256CipherSuite;
        break;
    case WPA_ALG_BIP_GMAC_128:
        standardSuiteSelector = &BIPGmac128CipherSuite;
        break;
    case WPA_ALG_BIP_GMAC_256:
        standardSuiteSelector = &BIPGmac256CipherSuite;
        break;
    case WPA_ALG_BIP_CMAC_256:
        standardSuiteSelector = &BIPCmac256CipherSuite;
        break;
    default:
        wpa_printf(MSG_ERROR, "Invalid algo type %x", alg);
        break;
        
    }

    if (!standardSuiteSelector)
        return false;
	
    os_memcpy(suiteSelector, standardSuiteSelector, sizeof(suiteSelector));
	
    return true;
}

static int wpas_set_key(void *ctx, enum wpa_alg alg,
    const u8 *addr, int key_idx, int set_tx,
    const u8 *seq, size_t seq_len,
    const u8 *key, size_t key_len, enum key_flag key_flag)
{
    struct wpas *wpas = ctx;

    wpa_printf(MSG_DEBUG, "SUPP: %s(alg=%d addr=" MACSTR " key_idx=%d "
        "set_tx=%d)", __func__, alg, MAC2STR(addr), key_idx, set_tx);
    wpa_hexdump(MSG_DEBUG, "SUPP: set_key - seq", seq, seq_len);
    wpa_hexdump(MSG_DEBUG, "SUPP: set_key - key", key, key_len);

    if (os_memcmp(addr, broadcast_ether_addr, 6) != 0) {
		os_memcpy(&wpas->PtkSet.Key, key, EFI_MAX_KEY_LEN);
		wpas->PtkSet.KeyLen = key_len;
		wpas->PtkSet.KeyId  = key_idx;
		wpas->PtkSet.KeyType = Pairwise;
		os_memcpy(&wpas->PtkSet.Addr, addr, 6);
		os_memcpy(&wpas->PtkSet.Rsc, seq, seq_len);
		wpas->PtkSet.RscLen = seq_len;
		wpas->PtkSet.IsAuthenticator = FALSE;
		wpa_alg_to_cipher_suite(alg, key_len, &wpas->PtkSet.CipherSuite);
		wpas->PtkSet.Direction = set_tx;
    }
    else {

        if (wpa_alg_bip(alg)) {
            EFI_SUPPLICANT_KEY* igtk = &wpas->IGtkSet.GTKList[0];
            wpas->IGtkSet.GTKCount = 1; // support igtk
            os_memcpy(igtk->Key, key, EFI_MAX_KEY_LEN);
            igtk->KeyLen = key_len;
            igtk->KeyId = key_idx;
            igtk->KeyType = IGTK;
            os_memcpy(&igtk->Addr, addr, 6);
            os_memcpy(igtk->Rsc, seq, seq_len);
            igtk->RscLen = seq_len;
            igtk->IsAuthenticator = FALSE;
            wpa_alg_to_cipher_suite(alg, key_len, &igtk->CipherSuite);
            igtk->Direction = set_tx;
        }
        else
        {
            EFI_SUPPLICANT_KEY* gtk = &wpas->GtkSet.GTKList[0];

            wpas->GtkSet.GTKCount = 1; // Only support 1 GTK
            os_memcpy(gtk->Key, key, EFI_MAX_KEY_LEN);
            gtk->KeyLen = key_len;
            gtk->KeyId = key_idx;
            gtk->KeyType = Group;
            os_memcpy(&gtk->Addr, addr, 6);
            os_memcpy(gtk->Rsc, seq, seq_len);
            gtk->RscLen = seq_len;
            gtk->IsAuthenticator = FALSE;
            wpa_alg_to_cipher_suite(alg, key_len, &gtk->CipherSuite);
            gtk->Direction = set_tx;
        }
    }

	if (wpas->PtkSet.KeyLen && (wpas->GtkSet.GTKCount || wpas->IGtkSet.GTKCount)) {
		// eapol complete when both PTK and GTK set
		wpas->ops->wpa_complete(wpas->parent, 1);
	}

    return 0;
}

static int wpas_get_beacon_ie(void *ctx)
{
    return 1;
}

static void wpas_deauthenticate(void *ctx, u16 reason_code)
{
}

static int wpas_mlme_setprotection(void *ctx, const u8 *addr,
    int protection_type, int key_type)
{
    return 0;
}

static void wpas_cancel_auth_timeout(void *ctx)
{
}

static enum wpa_states wpas_get_state(void *ctx)
{
    return WPA_COMPLETED;
}

static int wpas_key_mgmt_set_pmk(
    void *ctx, const u8 *pmk, size_t pmk_len)
{
    return -1;
}

static int wpas_add_pmkid(
    void *ctx, void *network_ctx, const u8 *bssid,
    const u8 *pmkid, const u8 *fils_cache_id,
    const u8 *pmk, size_t pmk_len, u32 pmk_lifetime,
    u8 pmk_reauth_threshold, int akmp)
{
    return -1;
}

static int wpas_remove_pmkid(void *wpa_s, void *network_ctx,
    const u8 *bssid, const u8 *pmkid,
    const u8 *fils_cache_id)
{
    return -1;
}

int wpas_init_wpa_sm(struct wpas *wpas)
{
    struct wpa_sm_ctx *ctx = os_zalloc(sizeof(*ctx));
    if (!ctx)
        return -1;

    ctx->ctx = wpas;
    ctx->msg_ctx = wpas;
    ctx->set_state = wpas_set_state;
    ctx->get_bssid = wpas_get_bssid;
    ctx->ether_send = wpas_ether_send;
    ctx->get_beacon_ie = wpas_get_beacon_ie;
    ctx->alloc_eapol = wpas_alloc_eapol;
    ctx->get_network_ctx = wpas_get_network_ctx;
    ctx->set_key = wpas_set_key;
    ctx->deauthenticate = wpas_deauthenticate;
    ctx->mlme_setprotection = wpas_mlme_setprotection;
    ctx->cancel_auth_timeout = wpas_cancel_auth_timeout;
    ctx->get_state = wpas_get_state;
    ctx->key_mgmt_set_pmk = wpas_key_mgmt_set_pmk;
    ctx->add_pmkid = wpas_add_pmkid;
    ctx->remove_pmkid = wpas_remove_pmkid;

    wpas->supp = wpa_sm_init(ctx);
    if (!wpas->supp) {
        return -1;
    }

    return 0;
}

int wpas_init(struct wpas *wpas, struct wpas_glue_cbs *ops, void *parent)
{
    wpas->ops = ops;
    wpas->parent = parent;

    if (wpas_init_wpa_sm(wpas)) {
        return -1;
    }

    if (wpas_init_eapol_sm(wpas))
        return -1;

    wpa_sm_set_eapol(wpas->supp, wpas->eapol);

    if (wpas_init_sae(wpas))
        return -1;

    return 0;
}

void wpas_deinit(struct wpas *wpas)
{
    wpas_deinit_sae(wpas);
    eapol_sm_deinit(wpas->eapol);
    os_memset(wpas, 0, sizeof(*wpas));
}

static void wpas_set_pmk(struct wpas *wpas)
{
    if (!wpas->passphrase ||
        !wpas->ssid_set ||
        wpa_sm_get_key_mgmt(wpas->supp) == 0 ||
        wpa_sm_get_key_mgmt(wpas->supp) == WPA_KEY_MGMT_SAE)
        return;

    if (!wpas->pmk_set) {
        pbkdf2_sha1(wpas->passphrase, wpas->ssid, wpas->ssid_len, 4096,
            wpas->pmk, sizeof(wpas->pmk));
        wpas->pmk_set = 1;
        wpa_sm_set_pmk(wpas->supp, wpas->pmk, PMK_LEN, NULL, NULL);
    }
}

void wpas_set_passphrase(struct wpas *wpas, const char *passphrase)
{
    if (wpas->passphrase) {
        os_free(wpas->passphrase);
        wpas->passphrase = NULL;
    }

    wpas->passphrase = os_strdup(passphrase);
    wpas->pmk_set = 0;
    os_memset(wpas->pmk, 0, sizeof(wpas->pmk));
}

void wpas_set_ssid(struct wpas *wpas, const u8 *ssid, int ssid_len)
{
    if (wpas->ssid_len != ssid_len ||
        os_memcmp(wpas->ssid, ssid, ssid_len) != 0) {
        wpas->pmk_set = 0;
        os_memset(wpas->pmk, 0, sizeof(wpas->pmk));
    }

    os_memcpy(wpas->ssid, ssid, ssid_len);
    wpas->ssid_len = ssid_len;
    wpas->ssid_set = 1;
}

void wpas_set_own_addr(struct wpas *wpas, const u8 *own_addr)
{
    os_memcpy(wpas->own_addr, own_addr, ETH_ALEN);

    wpa_sm_set_own_addr(wpas->supp, own_addr);
}

void wpas_get_auth_addr(struct wpas *wpas, u8 *auth_addr)
{
	os_memcpy(auth_addr, wpas->auth_addr, ETH_ALEN);
}

void wpas_set_auth_addr(struct wpas *wpas, const u8 *auth_addr)
{
    os_memcpy(wpas->auth_addr, auth_addr, ETH_ALEN);
}

void wpas_set_key_mgmt(struct wpas *wpas, int key_mgmt)
{
    // Only support RSN proto
    wpa_sm_set_param(wpas->supp, WPA_PARAM_RSN_ENABLED, 1);
    wpa_sm_set_param(wpas->supp, WPA_PARAM_PROTO, WPA_PROTO_RSN);
    wpa_sm_set_param(wpas->supp, WPA_PARAM_KEY_MGMT, key_mgmt);
}

void wpas_set_group_cipher(struct wpas *wpas, int group_cipher)
{
    wpa_sm_set_param(wpas->supp, WPA_PARAM_GROUP, group_cipher);
}

int wpas_set_pairwise_cipher(struct wpas *wpas, int pairwise_cipher)
{
    return wpa_sm_set_param(wpas->supp, WPA_PARAM_PAIRWISE, pairwise_cipher);
}

void wpas_update_mgmt_group_chiper(struct wpas *wpas, u32 type)
{
    wpa_printf(MSG_DEBUG, "type 0x%x", type);

	if (type == WPA_KEY_MGMT_IEEE8021X)
		wpa_sm_set_param(wpas->supp, WPA_PARAM_MGMT_GROUP, WPA_CIPHER_BIP_GMAC_128);
	else if (type == WPA_KEY_MGMT_IEEE8021X_SUITE_B ||
		type == WPA_KEY_MGMT_IEEE8021X_SUITE_B_192)
		wpa_sm_set_param(wpas->supp, WPA_PARAM_MGMT_GROUP, WPA_CIPHER_BIP_GMAC_256);
	else if (type == WPA_KEY_MGMT_SAE)
		wpa_sm_set_param(wpas->supp, WPA_PARAM_MGMT_GROUP, WPA_CIPHER_AES_128_CMAC);
	else {
		wpa_printf(MSG_DEBUG, "unsupported type 0x%x", type);
		wpa_sm_set_param(wpas->supp, WPA_PARAM_MGMT_GROUP, 0);
	}
}

void wpas_set_mfp(struct wpas *wpas, u8 mfp)
{
    wpa_printf(MSG_DEBUG, "mfp %d", mfp);
    wpa_sm_set_param(wpas->supp, WPA_PARAM_MFP, mfp);
}

static void wpas_sae_set_pwe(struct wpas *wpas, int sae_pwe)
{
	wpas->conf.sae_pwe = sae_pwe;
}

void wpas_set_rsn_extcap(struct wpas *wpas, u8 rsnxe_cap)
{
	wpa_printf(MSG_DEBUG, "rsnxe_cap %d", rsnxe_cap);
	
	wpas->rsnxe_cap = rsnxe_cap;
	if (wpas->rsnxe_cap) {
		if(rsnxe_cap & BIT(WLAN_RSNX_CAPAB_SAE_H2E)) {
			wpa_sm_set_param(wpas->supp, WPA_PARAM_SAE_PWE, 1);
			wpas_sae_set_pwe(wpas, 1);
			return;
		}
	} 

	wpa_sm_set_param(wpas->supp, WPA_PARAM_SAE_PWE, 0);
	wpas_sae_set_pwe(wpas, 0);
}

void wpas_set_phase1_eap_method(struct wpas *wpas, enum eap_type method)
{
    wpas->phase1_method = method;
}

void wpas_set_phase2_eap_method(struct wpas *wpas, enum eap_type method)
{
    wpas->phase2_method = method;
}

void wpas_set_eap_identity(struct wpas *wpas, u8 *identity, size_t identity_len)
{
    wpas->eap_identity = os_zalloc(identity_len);
    if (wpas->eap_identity) {
        os_memcpy(wpas->eap_identity, identity, identity_len);
        wpas->eap_identity_len = identity_len;
    }
}

void wpas_set_eap_priv_key_password(struct wpas *wpas, u8 *pwd, size_t buf_size)
{
    wpas->eap_priv_key_password = os_zalloc(buf_size);
    if (wpas->eap_priv_key_password)
        os_memcpy(wpas->eap_priv_key_password, pwd, buf_size);
}

void wpas_set_eap_pwd(struct wpas *wpas, u8 *ucs_pwd, size_t buf_size)
{
    size_t len = buf_size;

    md4_vector(1, (const u8 **)&ucs_pwd, &len, wpas->eap_pwd);
    wpas->eap_pwd_set = 1;
}

void wpas_set_eap_blob(struct wpas *wpas, u8 *data, size_t buf_size,
    struct wpa_config_blob *blob)
{
    u8 *copy = os_zalloc(buf_size);
    if (!copy)
        return;

    os_memcpy(copy, data, buf_size);
    blob->data = copy;
    blob->len = buf_size;
    blob->next = NULL;
}

void wpas_rx_eapol(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
    u8 *response, size_t *response_len)
{
    wpas->resp_eapol = response;
    wpas->resp_eapol_len = response_len;

    if (rx_data) {
        eapol_sm_rx_eapol(wpas->eapol, wpas->auth_addr, rx_data, rx_data_len);
    }

    eloop_timer_tick();

    if (wpas->resp_eapol_len) {
        *(wpas->resp_eapol_len) = 0;
        wpas->resp_eapol = NULL;
        wpas->resp_eapol_len = NULL;
    }
}

void wpas_rx_wpa(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
    u8 *response, size_t *response_len)
{
    wpas->resp_eapol = response;
    wpas->resp_eapol_len = response_len;

    if (rx_data) {
        wpa_sm_rx_eapol(wpas->supp, wpas->auth_addr, rx_data, rx_data_len);
    }

    eloop_timer_tick();

    if (wpas->resp_eapol_len) {
        *(wpas->resp_eapol_len) = 0;
        wpas->resp_eapol = NULL;
        wpas->resp_eapol_len = NULL;
    }
}

static void wpas_wpa_notify_disassoc(struct wpas* wpas)
{
    wpa_sm_notify_disassoc(wpas->supp);
}

static void wpas_eapol_notify_disassoc(struct wpas *wpas)
{
    wpas->pmk_set = 0;
    os_memset(wpas->pmk, 0, sizeof(wpas->pmk));
    wpas->ssid_set = 0;
    wpas->ssid_len = 0;
    os_memset(wpas->ssid, 0, sizeof(wpas->ssid));

    os_memset(wpas->auth_addr, 0, ETH_ALEN);
    if (wpas->passphrase) {
        os_free(wpas->passphrase);
        wpas->passphrase = NULL;
    }

    wpas->resp_eapol = NULL;
    if (wpas->resp_eapol_len)
        *wpas->resp_eapol_len = 0;
    wpas->resp_eapol_len = NULL;

    if (wpas->eap_identity) {
        os_free(wpas->eap_identity);
        wpas->eap_identity = NULL;
        wpas->eap_identity_len = 0;
    }

    if (wpas->eap_priv_key_password) {
        os_free(wpas->eap_priv_key_password);
        wpas->eap_priv_key_password = NULL;
    }

    if (wpas->ca_cert_blob.data) {
        os_free(wpas->ca_cert_blob.data);
        wpas->ca_cert_blob.data = NULL;
        wpas->ca_cert_blob.len = 0;
    }

    if (wpas->client_cert_blob.data) {
        os_free(wpas->client_cert_blob.data);
        wpas->client_cert_blob.data = NULL;
        wpas->client_cert_blob.len = 0;
    }

    if (wpas->priv_key_blob.data) {
        os_free(wpas->priv_key_blob.data);
        wpas->priv_key_blob.data = NULL;
        wpas->priv_key_blob.len = 0;
    }

    wpas->eap_pwd_set = 0;
    os_memset(wpas->eap_pwd, 0, sizeof(wpas->eap_pwd));
    os_memset(&wpas->eap, 0, sizeof(wpas->eap));

    wpas->phase1_method = EAP_TYPE_NONE;
    wpas->phase2_method = EAP_TYPE_NONE;

    eapol_sm_invalidate_cached_session(wpas->eapol);
}

static void wpas_sae_notify_disassoc(struct wpas* wpas)
{
    wpas_deinit_sae(wpas);
}

void wpas_notify_disassoc(struct wpas *wpas)
{
    wpas_eapol_notify_disassoc(wpas);
    wpas_wpa_notify_disassoc(wpas);
    wpas_sae_notify_disassoc(wpas);
}

static void wpas_wpa_notify_assoc(struct wpas *wpas)
{
    /* clean old wpa_ie and build a new one for new cipher */
    wpas->supp_ie_len = sizeof(wpas->supp_ie);
    wpa_sm_set_assoc_wpa_ie(wpas->supp, NULL, 0);
    if (wpa_sm_set_assoc_wpa_ie_default(wpas->supp, wpas->supp_ie,
        &wpas->supp_ie_len) < 0) {
        wpa_printf(MSG_DEBUG, "SUPP: wpa_sm_set_assoc_wpa_ie_default() failed");
    }

	/* clean old wpa_ie and build a new one for new cipher */
    wpas->rsnxe_len = sizeof(wpas->rsnxe);
    wpa_sm_set_assoc_rsnxe(wpas->supp, NULL, 0);
	if (wpa_sm_set_assoc_rsnxe_default(wpas->supp, wpas->rsnxe,
		&wpas->rsnxe_len) < 0) {
		wpa_printf(MSG_DEBUG, "SUPP: wpa_sm_set_assoc_rsnxe_default() failed");
	}

    wpas_set_pmk(wpas);
    wpa_sm_notify_assoc(wpas->supp, wpas->auth_addr);
}

static void wpas_eapol_notify_assoc(struct wpas *wpas)
{
    int midx = 0;

    if (wpas->phase1_method != EAP_TYPE_NONE) {
        wpas->eap_methods[midx].vendor = EAP_VENDOR_IETF;
        wpas->eap_methods[midx].method = wpas->phase1_method;
        midx++;
    }

    wpas->eap_methods[midx].vendor = EAP_VENDOR_IETF;
    wpas->eap_methods[midx].method = EAP_TYPE_NONE;
    wpas->eap.eap_methods = wpas->eap_methods;

    wpas->eap.fragment_size = 1398;

    wpas->eap.phase1 = "tls_disable_time_checks=1";

    wpas->eap.identity = wpas->eap_identity;
    wpas->eap.identity_len = wpas->eap_identity_len;

    if (wpas->eap_pwd_set) {
        wpas->eap.password = wpas->eap_pwd;
        wpas->eap.password_len = sizeof(wpas->eap_pwd);
        wpas->eap.flags |= EAP_CONFIG_FLAGS_PASSWORD_NTHASH;
    }

    if (wpas->phase2_method == EAP_TYPE_MSCHAPV2) {
        if (wpas->phase1_method == EAP_TYPE_PEAP)
            wpas->eap.phase2 = "auth=MSCHAPV2";
        else if (wpas->phase1_method == EAP_TYPE_TTLS)
            wpas->eap.phase2 = "autheap=MSCHAPV2";
    }
    if (wpas->ca_cert_blob.data)
        wpas->eap.cert.ca_cert = (char *)"blob://ca_cert";
    if (wpas->client_cert_blob.data)
        wpas->eap.cert.client_cert = (char *)"blob://client_cert";
    if (wpas->priv_key_blob.data) {
        wpas->eap.cert.private_key = (char *)"blob://priv_key";
        wpas->eap.cert.private_key_passwd = (char *)wpas->eap_priv_key_password;
    }

    wpas_initiate_eapol(wpas, &wpas->eap);
}

void wpas_notify_assoc(struct wpas *wpas)
{
    wpas_eapol_notify_assoc(wpas);
    wpas_wpa_notify_assoc(wpas);
}

#ifdef CONFIG_SAE

static void wpas_sae_fail(struct wpas *wpas, u8 status)
{
	wpa_printf(MSG_ERROR, "SAE failure %d", status);
	wpabuf_free(wpas->sae_token);
	wpas->sae_token = NULL;
	sae_clear_data(&wpas->sae);
}

static int wpas_sae_set_group(struct wpas *wpas)
{
    const u8 max_group_index = ARRAY_SIZE(wpas->conf.sae_groups);
    int *groups = wpas->conf.sae_groups;
    int group;
    
    if (wpas->sae_group_index >= max_group_index)
        return -1;

    do {
        group = groups[wpas->sae_group_index];
        if (group <= 0)
            break;
        if (sae_set_group(&wpas->sae, group) == 0) {
            wpa_printf(MSG_DEBUG, "SME: Selected SAE group %d", wpas->sae.group);
            return 0;
        }
        wpas->sae_group_index++;
    } while (true);

	return -1;
}

static void wpas_sae_set_pmk(struct wpas *wpas)
{
    if (wpas->sae.state >= SAE_CONFIRMED) {
        wpas->pmk_set = 1;
        wpa_sm_set_pmk(wpas->supp, wpas->sae.pmk, SAE_PMK_LEN, wpas->sae.pmkid, NULL);
    }
}

static struct sae_pt * wpas_setup_sae_pt(struct wpas *wpas)
{
	struct sae_pt *pt = NULL;
	int *groups = wpas->conf.sae_groups;
	int default_groups[] = { 19, 20, 21, 0 };
	const char *password;

	if (!groups || groups[0] <= 0)
		groups = default_groups;

	password = wpas->passphrase;
	if (!password ||
	    (wpas->conf.sae_pwe == 0 && !wpas->sae_pwd_id &&
	     !sae_pk_valid_password(password)) ||
	    wpas->conf.sae_pwe == 3) {
	    pt = NULL;
		wpa_printf(MSG_ERROR, "PT is NULL");
		return NULL;
	}

	pt = sae_derive_pt(groups, wpas->ssid, wpas->ssid_len,
			(const u8 *) password, os_strlen(password),
			wpas->sae_pwd_id);

	return pt;
}

static int wpas_sae_send_commit(struct wpas *wpas, u8 *resp, size_t *resp_len)
{
	struct ieee80211_mgmt *mgmt = (void*)resp;
	struct sae_pt *pt = NULL;
	int use_pt = wpas->conf.sae_pwe? 1: 0;
	struct wpabuf *buf;
	size_t len;

	wpa_printf(MSG_ERROR, "use_pt = %d", use_pt);

	if (use_pt) {
		pt = wpas_setup_sae_pt(wpas);
		if (pt && sae_prepare_commit_pt(&wpas->sae, pt,
				wpas->own_addr, wpas->auth_addr,
				wpas->sae_rejected_groups, NULL) < 0) {
			wpa_printf(MSG_ERROR, "prepare sae commit pt fail");
			return -1;
		}
	} else {
		if (sae_prepare_commit(wpas->own_addr, wpas->auth_addr,
				(u8*)wpas->passphrase,
				os_strlen(wpas->passphrase),
				wpas->sae_pwd_id, &wpas->sae) < 0) {
			wpa_printf(MSG_ERROR, "prepare sae commit fail");
			return -1;
		}
	}

	len = wpas->sae_token ? wpabuf_len(wpas->sae_token) : 0;
	if (wpas->sae_pwd_id)
		len += 4 + os_strlen(wpas->sae_pwd_id);

	buf = wpabuf_alloc(4 + SAE_COMMIT_MAX_LEN + len);
	if (buf == NULL)
		return -1;

    if (sae_write_commit(&wpas->sae, buf, wpas->sae_token, wpas->sae_pwd_id)) 
        wpa_printf(MSG_ERROR, "write sae conmmit fail");

	mgmt->frame_control = host_to_le16((WLAN_FC_TYPE_MGMT << 2) |
		(WLAN_FC_STYPE_AUTH << 4));
	os_memcpy(mgmt->da, wpas->auth_addr, ETH_ALEN);
	os_memcpy(mgmt->sa, wpas->own_addr, ETH_ALEN);
	os_memcpy(mgmt->bssid, wpas->auth_addr, ETH_ALEN);
	mgmt->u.auth.auth_alg = host_to_le16(WLAN_AUTH_SAE);

	mgmt->seq_ctrl = host_to_le16(wpas->sae_seq_num++ << 4);
	mgmt->u.auth.auth_transaction = host_to_le16(1);
	if (use_pt) {
		mgmt->u.auth.status_code = host_to_le16(WLAN_STATUS_SAE_HASH_TO_ELEMENT);
	} else {
		mgmt->u.auth.status_code = host_to_le16(WLAN_STATUS_SUCCESS); 
	}
	os_memcpy(resp + offsetof(struct ieee80211_mgmt, u.auth.variable),
		wpabuf_head(buf), wpabuf_len(buf));

	*resp_len = wpabuf_len(buf) + offsetof(struct ieee80211_mgmt, u.auth.variable);

	wpas->sae.state = SAE_COMMITTED;
	wpabuf_free(buf);

	return 0;
}

static int wpas_sae_send_confirm(struct wpas *wpas, u8 *resp, size_t *resp_len)
{
	struct ieee80211_mgmt *mgmt = (void*)resp;
	struct wpabuf *buf;

	buf = wpabuf_alloc(4 + SAE_CONFIRM_MAX_LEN);
	if (buf == NULL)
		return -1;

	sae_write_confirm(&wpas->sae, buf);
	mgmt->frame_control = host_to_le16((WLAN_FC_TYPE_MGMT << 2) |
		(WLAN_FC_STYPE_AUTH << 4));
	os_memcpy(mgmt->da, wpas->auth_addr, ETH_ALEN);
	os_memcpy(mgmt->sa, wpas->own_addr, ETH_ALEN);
	os_memcpy(mgmt->bssid, wpas->auth_addr, ETH_ALEN);
	mgmt->u.auth.auth_alg = host_to_le16(WLAN_AUTH_SAE);
	mgmt->seq_ctrl = host_to_le16(wpas->sae_seq_num++ << 4);
	mgmt->u.auth.auth_transaction = host_to_le16(2);
	mgmt->u.auth.status_code = host_to_le16(WLAN_STATUS_SUCCESS);
	os_memcpy(resp + offsetof(struct ieee80211_mgmt, u.auth.variable),
		wpabuf_head(buf), wpabuf_len(buf));
	*resp_len = wpabuf_len(buf) + offsetof(struct ieee80211_mgmt, u.auth.variable);
	wpas->sae.state = SAE_CONFIRMED;
	wpabuf_free(buf);

	return 0;
}

static int wpas_sae_start_auth(struct wpas *wpas, u8 *resp, size_t *resp_len)
{
	int res;

	wpas->sae_seq_num = 0;
	wpas->sae.state = SAE_NOTHING;
	wpas->sae.send_confirm = 0;
    wpas->sae_group_index = 0;

	if (wpas_sae_set_group(wpas)) {
        wpas_sae_fail(wpas, WLAN_STATUS_UNSPECIFIED_FAILURE);
		return -1;
	}

	res = wpas_sae_send_commit(wpas, resp, resp_len);
	if (res < 0)
        wpas_sae_fail(wpas, WLAN_STATUS_UNSPECIFIED_FAILURE);

	return res;
}

static int wpas_sae_handle_auth(struct wpas *wpas, u16 auth_transaction,
	u16 status_code, const u8 *data, size_t len,
	const u8 *sa, u8 *resp, size_t *resp_len)
{
	if (auth_transaction == 1 &&
		status_code == WLAN_STATUS_ANTI_CLOGGING_TOKEN_REQ &&
		wpas->sae.state == SAE_COMMITTED) {
		u16 group;

		if (len < sizeof(le16)) {
            wpa_printf(MSG_ERROR, "SAE: anti-clogging token is too short");
			return -1;
		}

		group = WPA_GET_LE16(data);
        wpa_printf(MSG_INFO,  "SAE: anti-clogging token  (group %u)",
			group);
		if (sae_group_allowed(&wpas->sae, NULL, group) !=
			WLAN_STATUS_SUCCESS) {
            wpa_printf(MSG_ERROR,  "SAE: invalid group %u of anti-clogging request",
				group);
			return -1;
		}

		wpabuf_free(wpas->sae_token);
		wpas->sae_token = wpabuf_alloc_copy(data + sizeof(le16),
			len - sizeof(le16));
        wpas_sae_send_commit(wpas, resp, resp_len);
		return 0;
	}

	if (auth_transaction == 1 &&
		status_code == WLAN_STATUS_FINITE_CYCLIC_GROUP_NOT_SUPPORTED &&
		wpas->sae.state == SAE_COMMITTED) {
		wpa_printf(MSG_DEBUG, "SAE: SAE group unsupported");
        int_array_add_unique(&wpas->sae_rejected_groups,
            wpas->sae.group);
        wpas->sae_group_index++;
		if (wpas_sae_set_group(wpas) < 0)
			return -1; /* no other groups enabled */
        wpa_dbg(wpa_s, MSG_DEBUG, "SME: Try next enabled SAE group");
        wpas_sae_send_commit(wpas, resp, resp_len);
		return 0;
	}

	if (status_code != WLAN_STATUS_SUCCESS && 
		status_code != WLAN_STATUS_SAE_HASH_TO_ELEMENT) {
		return -1;
	}

	if (auth_transaction == 1) {
		u16 res;

		wpa_printf(MSG_DEBUG, "SAE commit is Done");
		if (wpas->sae.state != SAE_COMMITTED)
			return -1;

		res = sae_parse_commit(&wpas->sae, data, len, NULL, NULL, NULL, 0);
		if (res == SAE_SILENTLY_DISCARD) {
			wpa_printf(MSG_DEBUG,
				"SAE: Drop commit message due to reflection attack");
			return 0;
		}

		if (res != WLAN_STATUS_SUCCESS)
			return -1;

		if (sae_process_commit(&wpas->sae) < 0) {
			wpa_printf(MSG_DEBUG, "Failed to process peer SAE commit");
			return -1;
		}

		wpabuf_free(wpas->sae_token);
		wpas->sae_token = NULL;
        wpas_sae_send_confirm(wpas, resp, resp_len);
		return 0;
	}
	else if (auth_transaction == 2) {
		wpa_printf(MSG_DEBUG, "SAE confirm is Done");
		if (wpas->sae.state != SAE_CONFIRMED)
			return -1;

		if (sae_check_confirm(&wpas->sae, data, len) < 0)
			return -1;

		wpas->sae.state = SAE_ACCEPTED;

		sae_clear_temp_data(&wpas->sae);

		return 1;
	}

	return -1;
}

static int wpas_sae_ext_auth_rx(struct wpas *wpas, const u8 *auth_frame,
	size_t len, u8 *resp, size_t *resp_len)
{
    int res;
	size_t auth_length;
    const struct ieee80211_mgmt *header = (const struct ieee80211_mgmt*)auth_frame;

	auth_length = IEEE80211_HDRLEN + sizeof(header->u.auth);
    wpa_printf(MSG_DEBUG, "len: %d, auth_length %d", len, auth_length);
    wpa_printf(MSG_DEBUG, "frame_control %X, algo =%d, auth_transaction =%d, status_code=%d",
        header->frame_control, header->u.auth.auth_alg,
        header->u.auth.auth_transaction, header->u.auth.status_code);

	if (len < auth_length) {
        wpas_sae_fail(wpas, WLAN_STATUS_UNSPECIFIED_FAILURE);
		return -1;
	}

    if (le_to_host16(header->u.auth.auth_alg) != WLAN_AUTH_SAE) {
        wpa_printf(MSG_ERROR, "invalid algo %d", header->u.auth.auth_alg);
            return -1;
    }
    wpa_printf(MSG_DEBUG, "auth_transaction: %d, status_code %d",
        header->u.auth.auth_transaction, header->u.auth.status_code);
	res = wpas_sae_handle_auth(wpas, le_to_host16(header->u.auth.auth_transaction),
		le_to_host16(header->u.auth.status_code),
		header->u.auth.variable,
		len - auth_length, header->sa, resp, resp_len);

	if (res < 0) {
        wpas_sae_fail(wpas, WLAN_STATUS_UNSPECIFIED_FAILURE);
        wpa_printf(MSG_ERROR, "wpas_sae_handle_auth failed: %d", res);
		return res;
	}

	if (res != 1)
		return 0;
    
    /* set the pmk */

    wpas_sae_set_pmk(wpas);
	*resp_len = 0;
	wpa_printf(MSG_DEBUG, "SAE completed");
	if (wpas->ops->sae_complete)
		wpas->ops->sae_complete(wpas->parent, 1);

	return 0;
}

int wpas_init_sae(struct wpas *wpas)
{
    static const int supported_groups[] = { 19, 20, 21, 0 };

    BUILD_BUG_ON(sizeof(wpas->conf.sae_groups) < sizeof(supported_groups));
    os_memcpy(wpas->conf.sae_groups, supported_groups, sizeof(supported_groups));

    return 0;
}

void wpas_deinit_sae(struct wpas *wpas)
{
    os_free(wpas->sae_rejected_groups);
    wpas->sae_rejected_groups = NULL;
    wpabuf_free(wpas->sae_token);
    wpas->sae_token = NULL;
    os_free(wpas->sae_pwd_id);
    wpas->sae_pwd_id = NULL;
    sae_clear_data(&wpas->sae);
}

int wpas_rx_sae(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
	u8 *response, size_t *response_len)
{
	if (!rx_data)
		return wpas_sae_start_auth(wpas, response, response_len);

	return wpas_sae_ext_auth_rx(wpas, rx_data, rx_data_len, response,
		response_len);
}

#else /* !CONFIG_SAE */

int wpas_init_sae(struct wpas *wpas)
{
    return 0;
}

void wpas_deinit_sae(struct wpas *wpas)
{
    return;
}

int wpas_rx_sae(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
	u8 *response, size_t *response_len)
{
	return -1;
}

#endif /* CONFIG_SAE */