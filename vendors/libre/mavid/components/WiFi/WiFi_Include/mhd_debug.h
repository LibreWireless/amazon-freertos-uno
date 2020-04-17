/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

#ifndef INCLUDED_MHD_DEBUG_H
#define INCLUDED_MHD_DEBUG_H

#include "host_defaults.h"
#include "my_print.h"
//#include <stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif



#ifdef MHD_DEBUG
#include "platform_assert.h"
    #define HOST_BREAK_IF_DEBUG( ) HOST_ASSERTION_FAIL_ACTION()
#else
    #define HOST_BREAK_IF_DEBUG( )
#endif

/******************************************************
 *             Print declarations
 ******************************************************/
// TODO: Micky modify
//#define WPRINT_MACRO(args) do {printf args;} while(0==1)
//#include "my_print.h"
//#define WPRINT_MACRO(args) do {PRINTF args; PRINTF("\r");} while(0==1)
#define WPRINT_MACRO(args) do {PRINTF args;} while(0==1)

/* HOST printing macros for general SDK/Library functions*/
#ifdef WPRINT_ENABLE_LIB_INFO
    #define WPRINT_LIB_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_LIB_INFO(args)
#endif
#ifdef WPRINT_ENABLE_LIB_DEBUG
    #define WPRINT_LIB_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_LIB_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_LIB_ERROR
    #define WPRINT_LIB_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_LIB_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for the Webserver*/
#ifdef WPRINT_ENABLE_WEBSERVER_INFO
    #define WPRINT_WEBSERVER_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_WEBSERVER_INFO(args)
#endif
#ifdef WPRINT_ENABLE_WEBSERVER_DEBUG
    #define WPRINT_WEBSERVER_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_WEBSERVER_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_WEBSERVER_ERROR
    #define WPRINT_WEBSERVER_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_WEBSERVER_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for Applications*/
#ifdef WPRINT_ENABLE_APP_INFO
    #define WPRINT_APP_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_APP_INFO(args)
#endif
#ifdef WPRINT_ENABLE_APP_DEBUG
    #define WPRINT_APP_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_APP_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_APP_ERROR
    #define WPRINT_APP_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_APP_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for Network Stacks */
#ifdef WPRINT_ENABLE_NETWORK_INFO
    #define WPRINT_NETWORK_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_NETWORK_INFO(args)
#endif
#ifdef WPRINT_ENABLE_NETWORK_DEBUG
    #define WPRINT_NETWORK_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_NETWORK_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_NETWORK_ERROR
    #define WPRINT_NETWORK_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_NETWORK_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for the RTOS*/
#ifdef WPRINT_ENABLE_RTOS_INFO
    #define WPRINT_RTOS_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_RTOS_INFO(args)
#endif
#ifdef WPRINT_ENABLE_RTOS_DEBUG
    #define WPRINT_RTOS_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_RTOS_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_RTOS_ERROR
    #define WPRINT_RTOS_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_RTOS_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for the Security stack*/
#ifdef WPRINT_ENABLE_SECURITY_INFO
    #define WPRINT_SECURITY_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_SECURITY_INFO(args)
#endif
#ifdef WPRINT_ENABLE_SECURITY_DEBUG
    #define WPRINT_SECURITY_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_SECURITY_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_SECURITY_ERROR
    #define WPRINT_SECURITY_ERROR(args) { WPRINT_MACRO(args); }
#else
    #define WPRINT_SECURITY_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for the WPS stack*/
#ifdef WPRINT_ENABLE_WPS_INFO
    #define WPS_INFO(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define WPS_INFO(args)
#endif
#ifdef WPRINT_ENABLE_WPS_DEBUG
    #define WPS_DEBUG(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define WPS_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_WPS_TRACE
    #define WPS_TRACE(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define WPS_TRACE(args)
#endif
#ifdef WPRINT_ENABLE_WPS_ERROR
    #define WPS_ERROR(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define WPS_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for the P2P stack*/
#ifdef WPRINT_ENABLE_P2P_INFO
    #define P2P_INFO(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define P2P_INFO(args)
#endif
#ifdef WPRINT_ENABLE_P2P_DEBUG
    #define P2P_DEBUG(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define P2P_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_P2P_TRACE
    #define P2P_TRACE(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define P2P_TRACE(args)
#endif
#ifdef WPRINT_ENABLE_P2P_ERROR
    #define P2P_ERROR(args) do{WPRINT_MACRO(("[WiFi] "));WPRINT_MACRO(args);}while(0)
#else
    #define P2P_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for Platforms*/
#ifdef WPRINT_ENABLE_PLATFORM_INFO
    #define WPRINT_PLATFORM_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_PLATFORM_INFO(args)
#endif
#ifdef WPRINT_ENABLE_PLATFORM_DEBUG
    #define WPRINT_PLATFORM_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_PLATFORM_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_PLATFORM_ERROR
    #define WPRINT_PLATFORM_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_PLATFORM_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif

/* HOST printing macros for Host Internal functions*/
#ifdef WPRINT_ENABLE_HOST_INFO
    #define WPRINT_HOST_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_HOST_INFO(args)
#endif
#ifdef WPRINT_ENABLE_HOST_DEBUG
    #define WPRINT_HOST_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_HOST_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_HOST_ERROR
    #define WPRINT_HOST_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_HOST_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif



/* HOST printing macros for Host Wi-Fi Driver*/
#ifdef WPRINT_ENABLE_MHD_INFO
    #define WPRINT_MHD_INFO(args) WPRINT_MACRO(args)
#else
    #define WPRINT_MHD_INFO(args)
#endif
#ifdef WPRINT_ENABLE_MHD_DEBUG
    #define WPRINT_MHD_DEBUG(args) WPRINT_MACRO(args)
#else
    #define WPRINT_MHD_DEBUG(args)
#endif
#ifdef WPRINT_ENABLE_MHD_ERROR
    #define WPRINT_MHD_ERROR(args) { WPRINT_MACRO(args); HOST_BREAK_IF_DEBUG(); }
#else
    #define WPRINT_MHD_ERROR(args) { HOST_BREAK_IF_DEBUG(); }
#endif


#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ifndef INCLUDED_MHD_DEBUG_H */
