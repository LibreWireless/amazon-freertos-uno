/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
 *  Defines functions to manage the HOST system
 */

#pragma once

#include "mhd_network_interface.h"
#include "host_tcpip_ext.h"
#include "host_wifi.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                     Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/** IP address configuration options */
typedef enum
{
    HOST_USE_EXTERNAL_DHCP_SERVER, /**< Client interface: use an external DHCP server  */
    HOST_USE_STATIC_IP,            /**< Client interface: use a fixed IP address       */
    HOST_USE_INTERNAL_DHCP_SERVER  /**< softAP interface: use the internal DHCP server */
} host_network_config_t;

/** HOST Network link subscription types denote whether
 *  to subscribe for link up or link down events */
typedef enum
{
    HOST_LINK_UP_SUBSCRIPTION,     /**< Link up event subscription   */
    HOST_LINK_DOWN_SUBSCRIPTION    /**< Link down event subscription */
} host_link_subscription_t;

/** HOST Network link status */
typedef enum
{
    HOST_LINK_UP,   /**< Link status up   */
    HOST_LINK_DOWN  /**< Link status down */
} host_link_status_t;

/******************************************************
 *                 Type Definitions
 ******************************************************/

/** Network link callback */
typedef void (*host_network_link_callback_t)(void);

/******************************************************
 *                    Structures
 ******************************************************/

/** IP address settings */
typedef struct
{
    host_ip_address_t ip_address;  /**< IP address      */
    host_ip_address_t gateway;     /**< Gateway address */
    host_ip_address_t netmask;     /**< Netmask         */
} host_ip_setting_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 *
 ******************************************************/

/*****************************************************************************/
/** @defgroup mgmt       Management
 *
 *  HOST Management Functions
 */
/*****************************************************************************/


/*****************************************************************************/
/** @addtogroup initconf       Initialisation & configuration
 *  @ingroup mgmt
 *
 * Initialisation/Deinitialisation of HOST and device configuration functions
 *
 *  @{
 */
/*****************************************************************************/

/** Enables all powersave features
 *
 *  This is a convenience function that calls each of the powersave related functions listed below \n
 *  Please review the documentation for each function for further information
 *  \li @ref host_platform_mcu_enable_powersave()
 *  \li @ref host_wifi_enable_powersave()
 *  \li @ref host_network_suspend()
 *
 * @return @ref host_result_t
 */
extern host_result_t host_enable_powersave( void );


/** Disables all powersave features
 *
 *  This is a convenience functions that calls each of the powersave related functions listed below \n
 *  Please review the documentation for each function for further information
 *  \li @ref host_platform_mcu_disable_powersave()
 *  \li @ref host_wifi_disable_powersave()
 *  \li @ref host_network_resume()
 *
 * @return HOST_SUCCESS
 */
extern host_result_t host_disable_powersave( void );

/** @} */



/*****************************************************************************/
/** @addtogroup netmgmt       Network management
 *  @ingroup mgmt
 *
 * Functions to manage the network interfaces
 *
 *  @{
 */
/*****************************************************************************/

/** Brings up a network interface
 *
 *
 * @param[in] interface     : the interface to bring up
 * @param[in] config        : the network IP configuration
 * @param[in] ip_settings   : static IP settings that are mandatory for the AP interface,
 *                        but are optional for the STA interface
 *
 * @return @ref host_result_t
 */
extern host_result_t host_network_up( host_interface_t interface, host_network_config_t config, const host_ip_setting_t* ip_settings );

/** Brings down a network interface
 *
 * @param[in] interface : the interface to bring down
 *
 * @return @ref host_result_t
 */
extern host_result_t host_network_down( host_interface_t interface );


/** Suspends network services and disables all network related timers
 *
 * This function must only be called before entering deep sleep. Prior to calling this function, ensure all
 * network sockets are in a disconnected state. After calling this function, networking functions
 * should not be used. To resume network operation, use the @ref host_network_resume() function.
 *
 * Example usage:
 *   @code
 *      host_network_suspend();
 *      host_rtos_delay_milliseconds(DEEP_SLEEP_TIME);
 *      host_network_resume();
 *   @endcode
 *
 * @return    HOST_SUCCESS : Network services are suspended.
 *            HOST_ERROR   : Network services were unable to be suspended, active sockets still exist
 */
extern host_result_t host_network_suspend( void );


/** Resumes network services
 *
 * This function resumes network services after suspension
 * with the host_network_suspend() function. After calling this function, all network functions
 * are available for use.
 *
 * Example usage:
 *   @code
 *      host_network_suspend();
 *      host_rtos_delay_milliseconds(DEEP_SLEEP_TIME);
 *      host_network_resume();
 *   @endcode
 *
 * @return @ref host_result_t
 */
extern host_result_t host_network_resume( void );


/** Checks if a network interface is up at the 802.11 link layer
 *
 * @param[in] interface : the interface to check
 *
 * @return @ref host_bool_t
 */
extern host_bool_t host_network_is_up( host_interface_t interface );

/** Checks if a network interface is up at the IP layer
 *
 * @param[in] interface : the interface to check
 *
 * @return @ref host_bool_t
 */
extern host_bool_t host_network_is_ip_up( host_interface_t interface );

/** Register callback function/s that gets called when a change in network link status occurs
 *
 * @param link_up_callback   : the optional callback function to register for the link up event
 * @param link_down_callback : the optional callback function to register for the link down event
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred with any step
 */
extern host_result_t host_network_register_link_callback( host_network_link_callback_t link_up_callback, host_network_link_callback_t link_down_callback );

/** De-register network link status callback function/s
 *
 * @param link_up_callback   : the optional callback function to deregister for the link up event
 * @param link_down_callback : the optional callback function to deregister for the link down event
 *
 * @return @ref host_result_t
 */
extern host_result_t host_network_deregister_link_callback( host_network_link_callback_t link_up_callback, host_network_link_callback_t link_down_callback );



extern void host_network_notify_link_up( void );
extern void host_network_notify_link_down( void );
extern host_result_t host_network_link_down_handler( void* arg );
extern host_result_t host_network_link_up_handler( void* arg );
extern host_result_t host_network_link_renew_handler( void* arg );
extern uint32_t host_network_get_ipv4_address( host_interface_t interface );



/** @} */

#ifdef __cplusplus
} /*extern "C" */
#endif
