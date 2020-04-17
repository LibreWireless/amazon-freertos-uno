#include "app_sec_config.h"
#include "lib.h"
int app_sec_init(app_sec_conf *conf)
{
    int rv = -1;
    if(conf != NULL){
        conf->max_retry = 10;
        conf->fatal_on_fail = 1;
        conf->skip_verify = 0;
        conf->source = APP_SEC_AVS;
        conf->authmode = VERIFY_REQUIRED;
        conf->delayBetweenRetries = 200;
        rv = 0;
    }
    return rv;

}

int app_sec_set_retry_delay(app_sec_conf *conf, int delay)
{
    int rv= -1;
    if(conf != NULL){
        conf->delayBetweenRetries = delay;
        rv = 0;
    }
    return rv;
}

int app_sec_set_source(app_sec_conf *conf, app_sec_src source)
{
    int rv= -1;
    if(conf != NULL){
        conf->source = source;
        rv = 0;
    }
    return rv;
}

int app_sec_set_max_retry(app_sec_conf *conf, unsigned char max_retry)
{

    int rv = -1;
    if(conf != NULL && max_retry>= 0){
        conf->max_retry = max_retry;
        rv = 0;
    }
    return rv;
}

int app_sec_set_fatal_on_fail(app_sec_conf *conf, unsigned char fatal_on_fail)
{
    int rv = -1;
    if(conf != NULL){
        conf->fatal_on_fail = (fatal_on_fail>0)?1:0;
        rv = 0;
    }
    return rv;
}

int app_sec_set_authmode(app_sec_conf *conf, app_sec_authmode authmode)
{
    int rv = -1;
    if(conf != NULL){
        switch(authmode){
            case VERIFY_NONE:
            case VERIFY_OPTIONAL:
            case VERIFY_REQUIRED:
            case VERIFY_UNSET:
                rv = 0;
                conf->authmode = authmode;
                break;
            default:
                printf("\r\n[%s]: unknown authmode - %d",__FUNCTION__,authmode);
                break;
        }
    }
    return rv;
}

int app_sec_set_skipverify(app_sec_conf *conf, unsigned char skip_verify)
{
    int rv = -1;
    if(conf != NULL){
        conf->skip_verify = (skip_verify>0)? 1:0 ;
        rv = 0;
    }
    return rv;
}
