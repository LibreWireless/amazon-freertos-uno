#ifndef __APP_SEC_CONFIG_H
#define __APP_SEC_CONFIG_H


typedef enum APP_SEC_AUTHMODE{
    VERIFY_NONE,
    VERIFY_OPTIONAL,
    VERIFY_REQUIRED,
    VERIFY_UNSET
}app_sec_authmode;

typedef enum APP_SEC_SRC{
    APP_SEC_AVS,
    APP_SEC_AVS_AUTH,
    APP_SEC_AUDIOPLAYER

}app_sec_src;

typedef struct app_sec_conf{
    unsigned char max_retry;
    unsigned char fatal_on_fail;
    unsigned char skip_verify;
    int delayBetweenRetries;
    app_sec_src source;
    app_sec_authmode authmode;
}app_sec_conf;


int app_sec_init(app_sec_conf *conf);
int app_sec_set_retry_delay(app_sec_conf *conf, int delay);
int app_sec_set_source(app_sec_conf *conf, app_sec_src source);
int app_sec_set_max_retry(app_sec_conf *conf, unsigned char max_retry);
int app_sec_set_fatal_on_fail(app_sec_conf *conf, unsigned char fatal_on_fail);
int app_sec_set_authmode(app_sec_conf *conf, app_sec_authmode authmode);
int app_sec_set_skipverify(app_sec_conf *conf, unsigned char skip_verify);
#endif /* __APP_SEC_CONFIG_H */

