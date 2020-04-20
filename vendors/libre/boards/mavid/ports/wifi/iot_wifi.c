/**
******************************************************************************
* @file    iot_wifi.c
* @author  HT
* @version V1.0
* @date    22-May-2017
* @brief   Main WiFi.
*
*
******************************************************************************
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <lwip/netdb.h>
/* Basic FreeRTOS definitions. */
#include "projdefs.h"
#include "FreeRTOS.h"

#include "iot_wifi.h"
#include "wifi_apis.h"
#include "lwip/mem.h"
#ifdef VERBOSE_PRINT
#define printf     vLoggingPrintf    
#else
#define printf(...)
#endif // VERBOSE_PRINT
    




WIFIReturnCode_t WIFI_GetIP( uint8_t * pucIPAddr )
{
  uint32_t ip;
  if(!pucIPAddr)
    return eWiFiFailure;
  ip = get_ip_address();
  memcpy(pucIPAddr, &ip, 4);
  return eWiFiSuccess;
}

WIFIReturnCode_t WIFI_GetMAC( uint8_t * pucMac )
{
  if(!pucMac)
    return eWiFiFailure;
  get_sta_macid((char*)pucMac);
  return eWiFiSuccess;
}

WIFIReturnCode_t WIFI_On( void )
{
  WIFIReturnCode_t ret = eWiFiSuccess;
  if(set_wifi_deepsleep(0) != 0)
    ret = eWiFiTimeout;
  return ret; 
}

WIFIReturnCode_t WIFI_Off( void )
{
  WIFIReturnCode_t ret = eWiFiSuccess;
  if(set_wifi_deepsleep(1) != 0)
    ret = eWiFiTimeout;
  return ret; 
}


WIFIReturnCode_t WIFI_Scan( WIFIScanResult_t * pxBuffer,
                           uint8_t ucNumNetworks )
{
  WIFIReturnCode_t ret = eWiFiFailure;
  int i;
  
  if(!pxBuffer)
  	return eWiFiFailure;
  do {   	
    char* data = (char*)mem_malloc((ucNumNetworks*sizeof(ap_info_t)+sizeof(int)));
    if(data == NULL)    
      break;    
    scan_result_info_t *scaninfo = (scan_result_info_t*)data;
    scaninfo->res_len = ucNumNetworks;
    printf("b4 res_len : %d\n", scaninfo->res_len);
    if ( get_drv_scan_results(scaninfo->scanptr, &scaninfo->res_len) )
    {
      printf("scan failed\n");
      break;
    }
    printf("after res_len : %d\n", scaninfo->res_len);
    ap_info_t *aplist = &scaninfo->scanptr[0];
    for (i = 0; i < scaninfo->res_len; i++)
    {
      pxBuffer->cChannel = aplist->channel;
      pxBuffer->cRSSI = aplist->rssi;
      strcpy(pxBuffer->cSSID, aplist->ssid);
      memcpy(pxBuffer->ucBSSID, aplist->bssid, wificonfigMAX_BSSID_LEN);
      switch(aplist->security)
      {
      case OPEN:
        pxBuffer->xSecurity = eWiFiSecurityOpen;
        break;
      case WPA_PSK_AES:
      case WPA_PSK_TKIP:
      case WPA_PSK_MIXED:
        pxBuffer->xSecurity = eWiFiSecurityWPA;
        break;
      case WPA2_PSK_AES:
      case WPA2_PSK_TKIP:
      case WPA2_PSK_MIXED:
        pxBuffer->xSecurity = eWiFiSecurityWPA2;
        break;
      case WEP_OPEN:
      case WEP_SHARED:
        pxBuffer->xSecurity = eWiFiSecurityWEP;
        break;
      default:
        pxBuffer->xSecurity = eWiFiSecurityNotSupported;
      }
      aplist++;
      pxBuffer++;      
    }
    ret = eWiFiSuccess;
  }while(0);
  return ret;
}

#define CHECK_VALID_SSID_LEN(x) \
        ((x) > 0 && (x) <=  wificonfigMAX_SSID_LEN)
#define CHECK_VALID_PASSPHRASE_LEN(x) \
        ((x) > 0 && (x) <= wificonfigMAX_PASSPHRASE_LEN)

WIFIReturnCode_t WIFI_ConnectAP( const WIFINetworkParams_t * const pxNetworkParams )
{
  WIFIReturnCode_t ret = eWiFiSuccess;  
  wifitrlmsg *msg;
  uint32_t retryPeriodMs = 250;
  BaseType_t xMaxRetries = 5, lRetries = 0;

  printf("WIFI_ConnectAP\n"); 
  if (pxNetworkParams == NULL || pxNetworkParams->pcSSID == NULL
            || (pxNetworkParams->xSecurity != eWiFiSecurityOpen && pxNetworkParams->pcPassword == NULL)) {
        return eWiFiFailure;
  }
  if (!CHECK_VALID_SSID_LEN(pxNetworkParams->ucSSIDLength) ||
      (pxNetworkParams->xSecurity != eWiFiSecurityOpen && !CHECK_VALID_PASSPHRASE_LEN(pxNetworkParams->ucPasswordLength))) {
      return eWiFiFailure;
  }

  connectparam *cfg = malloc(sizeof(connectparam));
  memcpy(cfg->ssid, pxNetworkParams->pcSSID, pxNetworkParams->ucSSIDLength );
  cfg->ssidlen = pxNetworkParams->ucSSIDLength;
  memcpy(cfg->password, pxNetworkParams->pcPassword, pxNetworkParams->ucPasswordLength );  
  cfg->pwdlen = pxNetworkParams->ucPasswordLength;  
  msg = create_ctrlmsg(WIFI_CONNECT, cfg, sizeof(connectparam), true, 15000);
  if(postmsg_wifi(msg) != 0)
    ret = eWiFiTimeout;

  if( eWiFiSuccess == ret )
  {
    ret = eWiFiFailure;
    for( ; lRetries < xMaxRetries; lRetries++ ) {                      
      vTaskDelay( pdMS_TO_TICKS( retryPeriodMs ) );               
      if( pdTRUE == WIFI_IsConnected() )
      {
        ret = eWiFiSuccess;
        break;
      }
      printf( "retry %d fail, timeout = %d \n",lRetries, retryPeriodMs );  
      retryPeriodMs *= 2;                                         
    }                                                                
  }

  return ret;
}

WIFIReturnCode_t WIFI_Disconnect( void )
{
  WIFIReturnCode_t ret = eWiFiSuccess;
  wifitrlmsg *msg;
  msg = create_ctrlmsg(WIFI_DISCONNECT, NULL, 0, false, 10000);    
  if(postmsg_wifi(msg) != 0)
    ret = eWiFiTimeout;
  return ret;  
}

BaseType_t WIFI_IsConnected(void )
{
  wifiinfo_t wlinfo = {0};
  get_wifi_info(WIFI_LINK_STATUS, &wlinfo);
  return (BaseType_t)wlinfo.linkstat;
}

WIFIReturnCode_t WIFI_GetMode( WIFIDeviceMode_t * pxDeviceMode )
{
  wifiinfo_t wlinfo = {0};
  if (pxDeviceMode == NULL)
    {
        return eWiFiFailure;
    }
  if(!get_wifi_info(WIFI_MODE, &wlinfo))
    *pxDeviceMode = (WIFIDeviceMode_t)wlinfo.mode;
  return eWiFiSuccess;
}

WIFIReturnCode_t WIFI_SetMode( WIFIDeviceMode_t xDeviceMode )
{
  WIFIReturnCode_t ret = eWiFiSuccess;
  wifitrlmsg *msg;
  wifimsgtype msgtype;
  
  if(xDeviceMode == eWiFiModeStation)
    stop_access_point(0, false, true);
  else if(xDeviceMode == eWiFiModeAP)
  {
    msg = create_ctrlmsg(WIFI_APMODE, NULL, 0, false, 10000);
    if(postmsg_wifi(msg) != 0)
      ret = eWiFiTimeout;
  }
  else
    ret = eWiFiNotSupported;
  return ret;  
}


WIFIReturnCode_t WIFI_NetworkAdd( const WIFINetworkProfile_t * const pxNetworkProfile,
                                  uint16_t * pusIndex )
{
  return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_NetworkGet( WIFINetworkProfile_t * pxNetworkProfile,
                                  uint16_t usIndex )
{
  return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_NetworkDelete( uint16_t usIndex )
{
  return eWiFiNotSupported;
}


WIFIReturnCode_t WIFI_Ping( uint8_t * pucIPAddr,
                            uint16_t usCount,
                            uint32_t ulIntervalMS )
{
  return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_Reset( )
{
  WIFIReturnCode_t ret;
  ret = WIFI_Off();
  if (eWiFiSuccess == ret )
    ret = WIFI_On();
  return ret;
}

WIFIReturnCode_t WIFI_SetPMMode( WIFIPMMode_t xPMModeType,
                                 const void * pvOptionValue )
{
   return eWiFiNotSupported;
}

WIFIReturnCode_t WIFI_GetPMMode( WIFIPMMode_t * pxPMModeType,
                                 void * pvOptionValue )
{
   return eWiFiNotSupported;
}


WIFIReturnCode_t WIFI_GetHostIP( char * pcHost,
                                uint8_t * pucIPAddr )
{
  WIFIReturnCode_t ret = eWiFiFailure;
  struct addrinfo *addr_list = NULL, *cur;
  struct sockaddr_in* addinfo;
  
  if (pcHost == NULL || pucIPAddr == NULL) {
        return ret;
    }

  if(pucIPAddr && pcHost &&
     !getaddrinfo( pcHost, NULL, NULL, &addr_list) &&
       addr_list)
  {
    cur = addr_list;
    do
    {
      /*The test is expecting a IPV4 address*/
      if(cur->ai_family == AF_INET)
      {
        addinfo = (struct sockaddr_in*)cur->ai_addr;		  
        memcpy(pucIPAddr, &addinfo->sin_addr, sizeof(uint32_t));
        ret = eWiFiSuccess;
        break;
      }
      cur = cur->ai_next;
    }while(cur);
    freeaddrinfo( addr_list );    
  }  
  return ret;
}

WIFIReturnCode_t WIFI_ConfigureAP( const WIFINetworkParams_t * const pxNetworkParams )
{
  WIFIReturnCode_t ret = eWiFiFailure;
  wifitrlmsg *msg;
  wifimsgtype msgtype;
  WIFIDeviceMode_t mode;
  
  printf("WIFI_ConfigureAP\n"); 
  
  do {    
    if(!pxNetworkParams || !pxNetworkParams->pcSSID || 
       !pxNetworkParams->ucSSIDLength || pxNetworkParams->ucSSIDLength > wificonfigMAX_SSID_LEN	||	
         pxNetworkParams->cChannel < 1 || pxNetworkParams->cChannel > 13 ||
           (pxNetworkParams->xSecurity != eWiFiSecurityOpen && (pxNetworkParams->pcPassword == NULL) || 
            !pxNetworkParams->ucPasswordLength || pxNetworkParams->ucPasswordLength < 8 ||
              pxNetworkParams->ucPasswordLength > wificonfigMAX_PASSPHRASE_LEN) )
    {
      printf("Got invalid params\n");
      break;
    }
    
    printf("Got valid params\n");
    
    WIFI_GetMode(&mode);
    
    if(mode == eWiFiModeAP || WIFI_IsConnected())
      WIFI_Disconnect();  
    
    wifitrlmsg *msg;	 
    apconfig_t *cfg ;
    
    cfg = malloc(sizeof(apconfig_t));	 
    memcpy(cfg->pcSSID, pxNetworkParams->pcSSID, pxNetworkParams->ucSSIDLength );
    cfg->ucSSIDLength = pxNetworkParams->ucSSIDLength;
    
    if(pxNetworkParams->ucPasswordLength)
    {
      memcpy(cfg->pcPassword, pxNetworkParams->pcPassword, pxNetworkParams->ucPasswordLength );  
      cfg->ucPasswordLength = pxNetworkParams->ucPasswordLength;  
    }
    else
      cfg->ucPasswordLength = 0;
    
    switch(pxNetworkParams->xSecurity)
    {
    case eWiFiSecurityOpen:
      cfg->Security = eOPEN;
      break;
    case eWiFiSecurityWEP:
      cfg->Security = eWEP;
      break;
    case eWiFiSecurityWPA:
      cfg->Security = eWPA;
      break;
    case eWiFiSecurityWPA2:
      cfg->Security = eWPA2;
      break;	
    default:
      cfg->Security = eUNKNWN;
      break;
    }
    
    if(cfg->Security == eUNKNWN)
    {
      ret = eWiFiNotSupported;
      break;
    }	 
    cfg->cChannel = pxNetworkParams->cChannel;    
    msg = create_ctrlmsg(WIFI_CONF_AP, cfg, sizeof(apconfig_t), true, 3000);
    if(postmsg_wifi(msg) != 0)
      ret = eWiFiTimeout;     
    ret = eWiFiSuccess;
  }while(0);
  return ret;  
}

/************************ (C) LibreWireless Inc *****END OF FILE****/
