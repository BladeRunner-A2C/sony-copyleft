/*
 * Copyright (c) 2020-2023 Qualcomm Technologies, Inc.
 * All Rights Reserved.
 * Confidential and Proprietary - Qualcomm Technologies, Inc.
 */

#ifndef _WPA_GLUE_H_
#define _WPA_GLUE_H_
#include <Protocol/Supplicant.h>

#include "utils/includes.h"
#include "utils/common.h"
#include "common/wpa_common.h"
#include "common/eapol_common.h"
#include "common/ieee802_11_defs.h"
#include "common/sae.h"

#include "eap_peer/eap.h"
#include "eap_peer/eap_methods.h"
#include "eap_peer/eap_config.h"
#include "eapol_supp/eapol_supp_sm.h"
#include "rsn_supp/wpa.h"

struct wpas {
    void *parent;
    struct wpas_glue_cbs *ops;

    struct eapol_sm *eapol;
    struct wpa_sm *supp;

    u8 own_addr[ETH_ALEN];

    /*** for connection ***/

    /* eap configuration */
    struct eap_peer_config eap;
    struct eap_method_type eap_methods[3];

    /* eapol data */
    u8 *resp_eapol;
    size_t *resp_eapol_len;

    /* eap data */
    enum eap_type phase1_method, phase2_method;
    u8 *eap_identity;
    size_t eap_identity_len;
    u8 eap_pwd[16];
    int eap_pwd_set;

    struct wpa_config_blob ca_cert_blob;
    struct wpa_config_blob client_cert_blob;
    struct wpa_config_blob priv_key_blob;

    u8 *eap_priv_key_password;

    int ssid_set;
    int ssid_len;
    u8 ssid[32];

    u8 auth_addr[ETH_ALEN];
    u8 supp_addr[ETH_ALEN];
    u8 psk[PMK_LEN];

    char *passphrase;

    u8 pmk[PMK_LEN];
    int pmk_set;

    /* wpa data */
    u8 supp_ie[80];
    size_t supp_ie_len;

	/* rsnxe data */
    u8 rsnxe[20];
    size_t rsnxe_len;

    /* sae data */
    struct sae_data sae;
    u16 sae_seq_num;
    u8 sae_group_index;
    struct wpabuf *sae_token;
    char *sae_pwd_id;
	u8 rsnxe_cap;
    int *sae_rejected_groups;

    /* configuration */
    struct {
        int sae_groups[4];
        int sae_pwe;
    } conf;
	
    /* uefi data */
	EFI_SUPPLICANT_KEY PtkSet;
	EFI_SUPPLICANT_GTK_LIST GtkSet;
    EFI_SUPPLICANT_GTK_LIST IGtkSet;
};

struct wpas_glue_cbs {
    void(*wpa_complete)(void *ctx, int success);
    void(*eapol_complete)(void *ctx, int success);
    void(*sae_complete)(void* ctx, int success);
};

int wpas_register(void);
int wpas_init(struct wpas *wpas, struct wpas_glue_cbs *ops, void *ctx);
void wpas_deinit(struct wpas *wpas);
void wpas_set_passphrase(struct wpas *wpas, const char *passphrase);
void wpas_set_ssid(struct wpas *wpas, const u8 *ssid, int ssid_len);
void wpas_set_own_addr(struct wpas *wpas, const u8 *own_addr);
void wpas_get_auth_addr(struct wpas *wpas, u8 *auth_addr);
void wpas_set_auth_addr(struct wpas *wpas, const u8 *auth_addr);
void wpas_set_key_mgmt(struct wpas *wpas, int key_mgmt);
void wpas_set_group_cipher(struct wpas *wpas, int group_cipher);
int wpas_set_pairwise_cipher(struct wpas *wpas, int pairwise_cipher);
void wpas_set_mfp(struct wpas *wpas, u8 mfp);
void wpas_set_rsn_extcap(struct wpas *wpas, u8 rsnxe_cap);
void wpas_update_mgmt_group_chiper(struct wpas* wpas, u32 type);
void wpas_notify_assoc(struct wpas *wpas);
void wpas_notify_disassoc(struct wpas *wpas);
void wpas_rx_wpa(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
    u8 *response, size_t *response_len);
void wpas_rx_eapol(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
    u8 *response, size_t *response_len);
void wpas_set_phase1_eap_method(struct wpas *wpas, enum eap_type method);
void wpas_set_phase2_eap_method(struct wpas *wpas, enum eap_type method);
void wpas_set_eap_identity(struct wpas *wpas, u8 *identity, size_t identity_len);
void wpas_set_eap_pwd(struct wpas *wpas, u8 *ucs_pwd, size_t buf_size);
void wpas_set_eap_blob(struct wpas *wpas, u8 *data, size_t buf_size,
    struct wpa_config_blob *blob);
void wpas_set_eap_priv_key_password(struct wpas *wpas, u8 *pwd, size_t buf_size);
/* SAE */
int wpas_init_sae(struct wpas *wpas);
void wpas_deinit_sae(struct wpas *wpas);
int wpas_rx_sae(struct wpas *wpas, const u8 *rx_data, size_t rx_data_len,
    u8 *response, size_t *response_len);
#endif
