#undef LOG_TAG
#define LOG_TAG "w800sdk"

#include <stdint.h>
#include <string.h>

#include "elog.h"

#include "w800sdk_conf.h"
#include "wm_include.h"

#include "mbedtls/base64.h"
#include "mbedtls/rsa.h"
#include "mbedtls/pk.h"

#define W800_SDK_VER_MAIN     0
#define W800_SDK_VER_SUB      1
#define W800_SDK_VER_REVISION 4

#define _2STR(x) #x
#define CONV_STR(x) _2STR(x)

// --- internal datas

#if CONFIG_W800_IMAGE_SIGN
#include "w800sdk_pubkey_sign.h"
    __attribute__((used))
    __attribute__((section(".usr_pubkey")))
        static const char firmware_sign_pubkey_pem[] = W800SDK_PUBKEY_SIGN_PEM;
#endif

// --- export funcs

int w800sdk_get_version_main(void)
{
    return W800_SDK_VER_MAIN;
}

int w800sdk_get_version_sub(void)
{
    return W800_SDK_VER_SUB;
}

int w800sdk_get_version_revision(void)
{
    return W800_SDK_VER_REVISION;
}

const char *w800sdk_get_version_string(void)
{
    return (CONV_STR(W800_SDK_VER_MAIN) "." CONV_STR(W800_SDK_VER_SUB) "." CONV_STR(W800_SDK_VER_REVISION));
}

int w800sdk_get_img_info(struct IMAGE_HEADER_PARAM *out)
{
#define IMG_HEAD_MAGIC_NO (0xA0FFFF9F)

    tls_fls_read(CONFIG_W800_IMAGE_HEADER_ADDR, (uint8_t *)out, sizeof(struct IMAGE_HEADER_PARAM));

    if (out->magic_no != IMG_HEAD_MAGIC_NO) {
        log_e("img magic '0x%08x' error ! expected '0x%08x'", out->magic_no, IMG_HEAD_MAGIC_NO);
        return -1;
    }

    return WM_SUCCESS;
}

int w800sdk_get_img_signature(struct w800_img_signature_info_t *info)
{
    struct IMAGE_HEADER_PARAM img_info;
    int rc;

    rc = w800sdk_get_img_info(&img_info);
    if (rc != WM_SUCCESS)
        return -1;

    // image not have a signature !
    if (!img_info.img_attr.b.signature)
        return -1;

    info->sign_addr = img_info.img_addr + img_info.img_len;

    rc = tls_fls_read(info->sign_addr, info->sign_data, sizeof(info->sign_data));
    if (rc != WM_SUCCESS) {
        log_e("tls_fls_read failed !");
        return -1;
    }

    psDigestContext_t sha1_ctx;
    tls_crypto_sha1_init(&sha1_ctx);

    // sha1 image header
    tls_crypto_sha1_update(&sha1_ctx, &img_info, sizeof(struct IMAGE_HEADER_PARAM));

    // sha1 image body
    uint32_t rd_addr = img_info.img_addr;
    uint32_t rd_end  = img_info.img_addr + img_info.img_len;
    uint8_t *tmpbuf  = tls_mem_alloc(512);

    while (rd_addr < rd_end) {

        uint32_t rd_size = (rd_addr + 512) < rd_end ? 512 : rd_end - rd_addr;
        if (rd_size == 0)
            break;

        rc = tls_fls_read(rd_addr, tmpbuf, rd_size);
        if (rc != WM_SUCCESS) {
            log_e("tls_fls_read(addr=0x%08x, size=%d) failed ! code=%d", rd_addr, rd_size, rc);
            tls_mem_free(tmpbuf);
            return -1;
        }

        tls_crypto_sha1_update(&sha1_ctx, tmpbuf, rd_size);

        rd_addr += rd_size;
    }

    tls_mem_free(tmpbuf);

    int32_t sz = tls_crypto_sha1_final(&sha1_ctx, info->image_sha1);
    if (sz != sizeof(info->image_sha1)) {
        log_e("tls_crypto_sha1_final failed ! code=%d", sz);
        return -1;
    }

    mbedtls_pk_context ctx_pk;
    mbedtls_pk_init(&ctx_pk);
    rc = mbedtls_pk_parse_public_key(&ctx_pk, (const uint8_t *)firmware_sign_pubkey_pem, strlen(firmware_sign_pubkey_pem) + 1);
    if (rc != WM_SUCCESS) {
        log_e("mbedtls_pk_parse_public_key failed ! code=%d", rc);
        return -1;
    }

    mbedtls_rsa_context rsa_ctx = *(mbedtls_rsa_context*)ctx_pk.pk_ctx;
    rc = mbedtls_rsa_complete(&rsa_ctx);
    if (rc != WM_SUCCESS) {
        log_e("mbedtls_rsa_complete failed ! code=%d", rc);
        return -1;
    }

    rc = mbedtls_rsa_pkcs1_verify(&rsa_ctx, NULL, NULL,
                                  MBEDTLS_RSA_PUBLIC, MBEDTLS_MD_SHA1,
                                  sizeof(info->image_sha1), info->image_sha1, info->sign_data);

    info->verify_passed = rc == 0;

    return 0;
}

// --- flash dummy

#if CONFIG_W800_CODE_ENCRYPT
    #define _IMG_CODE_ENC_ALIGN    16
    #define _IMG_CODE_ENC_KEY_SIZE 256 /* usrkey_enc.bin + pubkey_N.bin */
#else
    #define _IMG_CODE_ENC_ALIGN    0
    #define _IMG_CODE_ENC_KEY_SIZE 0
#endif

#if CONFIG_W800_IMAGE_SIGN
    #define _IMG_CODE_SIGN_KEY_SIZE 128 /* sign.bin */
#else
    #define _IMG_CODE_SIGN_KEY_SIZE 0
#endif

#define _FLASH_DUMMY_SIZE (_IMG_CODE_ENC_ALIGN + _IMG_CODE_ENC_KEY_SIZE + _IMG_CODE_SIGN_KEY_SIZE)

#if _FLASH_DUMMY_SIZE > 0
    static const uint8_t _flash_dummy[_FLASH_DUMMY_SIZE]
        __attribute__((used))
        __attribute__((section(".img_dummy")));
#endif
