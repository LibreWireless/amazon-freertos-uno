/**
  ******************************************************************************
  * @file    wifi_events.h
  * @author  Libre
  * @date    07-02-2018
  * @brief   This file contains wifi events 
  *          
  ******************************************************************************
  *
  ******************************************************************************
  */

#ifndef __WIFI_EVENTS_H
#define __WIFI_EVENTS_H

typedef enum  {
	WLAN_CONNECTED,
	WLAN_DISCONNECTED,
	WLAN_SETUP,
	WLAN_OFF,
        WLAN_CONNECTING,
        WLAN_SAC_CONNECTING,
        WLAN_SAC_FAILED,
        WLAN_IDLE,
        WLAN_CONNECTION_FAILED,
} wlan_event;


typedef void (*events_callback_t)(wlan_event evt);
void subscribe_for_events(events_callback_t cb);
void unsubscribe_for_events(events_callback_t cb);

#endif /* __WIFI_EVENTS_H */


/************************ (C) COPYRIGHT LibreWireless Inc *****END OF FILE****/
