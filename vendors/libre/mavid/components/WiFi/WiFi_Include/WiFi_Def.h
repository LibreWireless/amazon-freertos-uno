/**
******************************************************************************
* @file    WiFi_Def.h
* @author  HT
* @version V1.0.0
* @date    22-April-2017
* @brief   This file contains all WiFi Def
*          
******************************************************************************
*
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __WIFI_DEF_H
#define __WIFI_DEF_H

#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#include "cmsis_os.h"
#include "stm32f7xx_hal.h"
#include "stm32f769i_eval.h"
#include "stm32f7xx_ll_sdmmc.h"    

#include "mhd_debug.h"
#include "mhd_constants.h"
#include "mhd_platform_interface.h"
#include "mhd_rtos.h"
#include "mhd_rtos_interface.h"
#include "mhd_structures.h"
#include "mhd_sdpcm.h"
#include "wifi_apis.h"



#ifdef __cplusplus
extern "C" {
#endif
  
  
  //*********************************************************************************************  
  //*********************************************************************************************  
  
  // WiFi Build Options
  
  //*********************************************************************************************  
  //*********************************************************************************************  
  
  
  //#define MAVID_PROFILING
  //#define MAVID_SDPCM_LOG
  //#define MAVID_WIFI_PKT_LOG
  
#define MAVID_WIFI_POWERSAVE
  //#define MAVID_HOST_POWERSAVE
#define IPERF_SERVER_TCP 
#define LOW_MEM_FOOTPRINT
#define SDIO_48MHZ_CLOCK
#define SINGLE_THREAD_TXRX    
//#define WIFI_DEEPSLEEP

// Uncomment for WiFi F2 read/write Polling Mode  , else use OOB Interrupt mode
//#define LIBRE_PORT_POLLING  
  
// Uncomment for WiFi F2 read/write always in byte mode and no block mode  
//#define LIBRE_PORT_FORCE_BYTES_MODE_ALWAYS  


/* 
* Please enable this MACRO To enable the SAC Server
*/
#define WIFI_SAC_ENABLED

//*********************************************************************************************  
//*********************************************************************************************  

// TEST CASES 

//*********************************************************************************************  
//*********************************************************************************************  


//*********************************************************************************************
//************* SSID, PASSPHRASE, CHANNEL *****************************************************
//*********************************************************************************************  

 
//*********************************************************************************************
//*********************************************************************************************  
  
  
  typedef enum {
    WIFI_INIT_MODE,
    WIFI_PROVISIONAL_MODE,    
    WIFI_NORMAL_MODE,
    WIFI_ENTERING_OFF_MODE,
    WIFI_OFF_MODE,
    WIFI_DISCONNECTED,   
    WIFI_DUMMY,
    WIFI_NOT_ALLOWED,
    WIFI_MAX_MODE
  } WIFI_MODE_E;
  
 
  typedef struct
  {
    uint8_t wlcurstate;
    uint32_t profilehistory;
    uint8_t activeprofbkp;
    uint8_t intitreq;
    bool bIsF2Ready;
    bool bIsExercisedDone;
    bool bIsSystenRestarted;  
    bool bIs_OOB_SDIO_IntEnable;
    bool bProcessCmdPending;
    bool bProcessAPiPending;
	ewifimode_t curmode;
    void *apiresult;
    int *apiresultlen;
    int  wlcmdargc;
    char *wlcmdargv[5];
    osSemaphoreId wlcmdlock;
    osSemaphoreId rxThreadWakeSemaphore;  
    osThreadId rxThreadId;
    uint8_t mProvisionmode;
    uint32_t lowcreditcount;
    osThreadId mainThreadId;
    // Power save parameters
    bool bPowerSaveEnable;
    uint32_t powerSaveTickCnt;
    bool bIsSleepModeTriggered;  
    // WiFi Module Parameters and Status
    uint8_t WiFiAddr_STA[6];
    uint8_t WiFiAddr_AP[6]; 
    uint8_t wifiidletosleepdelay;
    uint32_t IP_Addr_STA;
    uint32_t IP_Addr_AP;  
    osSemaphoreId waitforTxDma;       
    osSemaphoreId api_wait;
    osMessageQueueId_t wifictrlQ;
    uint8_t isSAC_Timeout;
    uint8_t *pCurrentSSID;
    apconfig_t ap_config;
  }WIFI_CTRL_S;  
  
  extern WIFI_CTRL_S  gWiFiCtrl; 
  
  
  // RTOS functions
  
#ifdef LIBRE_PORT_POLLING

#define SDIO_OOB_INT_EN      { __enable_interrupt();}
#define SDIO_OOB_INT_DIS     { __disable_interrupt();}   

#else

#if defined(__ICCARM__)
#define SDIO_OOB_INT_EN  { if (gWiFiCtrl.bIs_OOB_SDIO_IntEnable &&   (__get_IPSR() == 0) ) { __enable_interrupt();} }
#define SDIO_OOB_INT_DIS { if (gWiFiCtrl.bIs_OOB_SDIO_IntEnable &&   (__get_IPSR() == 0) ) { __disable_interrupt();}}
#elif defined(__GNUC__)
#define SDIO_OOB_INT_EN  { if (gWiFiCtrl.bIs_OOB_SDIO_IntEnable &&   (__get_IPSR() == 0) ) { __enable_irq();} }
#define SDIO_OOB_INT_DIS { if (gWiFiCtrl.bIs_OOB_SDIO_IntEnable &&   (__get_IPSR() == 0) ) { __disable_irq();}}
#else
#define SDIO_OOB_INT_EN
#define SDIO_OOB_INT_DIS
#endif


#endif

int WiFiInit(void);
void WiFi_Ctrl_Param_Init(void);
void WiFiMainThreadFunc(void *argument);
void WiFiF2TXThreadFunc(void const *argument);
void WiFiF2TxThreadResume(void);  
void WiFiF2RXThreadFunc(void *argument);
void Iperf_Thread(void const * argument);
void WiFi_Platform_Deinit(void);
void sac_server_thread(void * argument);


void wl_print_stats(void);        


  
// WiFi GPIO pins  
//PI13 groupI
//#define WL_REG_ON_PIN           GPIO_PIN_13 //liju-module
#define WL_REG_ON_PIN           GPIO_PIN_10
// Pin7 groupK
//#define WL_HWAKE_INT_PIN        GPIO_PIN_7 //liju-module
#define WL_HWAKE_INT_PIN        GPIO_PIN_1
#define WL_HWAKE_INT_PIN_1_1    GPIO_PIN_7


#ifdef WIFI_SAC_ENABLED
#define NW_SETUP_PIN                    GPIO_PIN_13
#endif


#define Max_Wifi_profiles 5

//PI13 groupI
#define HOST_READY_PIN           GPIO_PIN_0 //liju-module
  
//BT --Liju
#define BT_REG_ON_PIN               GPIO_PIN_10
#define BT_DEV_WAKE_PIN             GPIO_PIN_9
#define BT_GPIO_PORT                GPIOH
  

#define BT_UART_TX_PIN             GPIO_PIN_9
#define BT_UART_RX_PIN             GPIO_PIN_10
#define BT_UART_CTS_PIN            GPIO_PIN_11
#define BT_UART_RTS_PIN            GPIO_PIN_12
#define BT_UART_PORT               GPIOA
// SDIO CMD52 & 53 defines
  
#define CMD_52_IDX (uint8_t)0x34
#define CMD_53_IDX (uint8_t)0x35
    
#define CMD52_RESP_COM_CRC_ERROR           0x00008000
#define CMD52_RESP_ILLEGAL_CMD             0x00004000  
#define CMD52_RESP_IO_CURRENT_STATE_MASK   0x00003000  
#define CMD52_RESP_UNKNOWN_ERROR           0x00000800  
#define CMD52_RESP_FUNCTION_ERROR          0x00000200  
#define CMD52_RESP_OUT_OF_RANGE_ERROR      0x00000100  
  
#define CMD52_RESP_READ_DATA_MASK          0x000000FF  
#define CMD52_RESP_ERROR_MASK              0x0000CB00 

#define ST32_SDIO_MODE                     0x00000800     
#define ST32_SDIO_MODE_RWSTART             0x00000100

#define ST32_SDIO_DATABLCK_SIZE(a)      (a == 64 ? 0x60 : 0x90) // log2(a) << 4

#define IS_IN_RANGE(x, y) (x > 0 && x <= y)


typedef enum
{
  CMD52_53_RESPONSE_NO_ERROR            = 0x0,
  CMD52_53_RESPONSE_CRC_ERROR           = 0x1,
  CMD52_53_RESPONSE_ILLEGAL_CMD         = 0x2,
  CMD52_53_RESPONSE_UNKNOWN_ERROR       = 0x3,
  CMD52_53_RESPONSE_FUNCTION_ERROR      = 0x4,
  CMD52_53_RESPONSE_OUT_OF_RANGE_ERROR  = 0x5,
  CMD52_53_RESPONSE_CMD_INDEX_ERROR     = 0x6,
  CMD52_53_RESPONSE_ERRORS              = 0x7 //safety
    
}CMD52_53_RESPONSE_STS_STRUCT;  


// TEST functions

void mhd_scan( void );
void mhd_scan_test_for_Libre( int retry_count, uint32_t time_ms );


// Interrupt, status update functions

void WiFi_F2_Ready_Callback( void); 
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);


// Reset, Init Functions

void Libre_WiFi_GPIO_Init(void);  
void WiFi_Module_Init(void);
void WiFi_Power_On_Cycle(void);
// SDIO functions 

uint32_t WiFi_SDIO_Reset(uint8_t * dataPtr);
uint32_t WiFi_SDIO_CMD5_Init_Sequences(uint32_t ocrData);

void WiFi_Init_SDIO_4Bits_Data_Transfer(void);
void WiFi_Init_SDIO_Normal_Clock(void);
  
uint32_t SDMMC_CMD52_WriteSingleByte(SDMMC_TypeDef *SDMMCx, mhd_bus_sdio_cmd52_argument_t arg, uint8_t * dataPtr);
uint32_t SDMMC_CMD52_ReadSingleByte(SDMMC_TypeDef *SDMMCx, mhd_bus_sdio_cmd52_argument_t arg, uint8_t * dataPtr);

uint32_t SDMMC_CMD53_ReadMultipleBytesOrBlocks(SDMMC_TypeDef *SDMMCx, mhd_bus_sdio_cmd53_argument_t arg, uint32_t blockSize, uint8_t * dataPtr);
uint32_t SDMMC_CMD53_WriteMultipleBytesOrBlocks(SDMMC_TypeDef *SDMMCx, mhd_bus_sdio_cmd53_argument_t arg,uint32_t blockSize, uint8_t * dataPtr);

// Misc
uint32_t SDIO_Read_CCCR( uint32_t addr, uint8_t * dataPtr);
void SDIO_Write_4Bytes_Check( uint32_t addr, uint8_t * dataPtr);

uint8_t mmc_crc7 (uint8_t *data,  uint8_t length);




  
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

extern SD_HandleTypeDef uSdHandle;


// Power save function prototypes

// Default, use powersave timer for better precise timing 
#define USE_SAVE_POWER_TIMER

#define POWERSAVE_PERIODIC_TICK_MS      200
#define POWERSAVE_TIME_WINDOW_MS        20000
#define POWERSAVE_TIME_WINDOW_TICK_CNT  (POWERSAVE_TIME_WINDOW_MS)/(POWERSAVE_PERIODIC_TICK_MS)
  
  void PowerSaveInit(void);
  void powerSaveActivityReg( void );
  void powerSaveOnOff( uint32_t bOn );
  void start_wifi_threads();
  void handle_sac_trigger(void);  
  /* Exported functions ------------------------------------------------------- */
  extern int mhd_get_mac_address(char addr[]);
  int mhd_get_fw_version( void );
  int mhd_module_init( void );
  void test_crc(void);
  
  int mhd_module_exit( void );
  int mhd_suspend( void );
  
  int mhd_resume( void );
  void mhd_set_country_code(uint32_t country);
  int mhd_set_mac_address(char addr[], int iface );
  
  void trigger_nw_setup(void);
  void run_wl_cmd(char  **argv, int argc );
  
  
  void mhd_test_softap_start( void );
  void mhd_test_softap_stop( void );
  
  // test
  int8_t MHD_send_one_packet(void);   
  int8_t MHD_receive_one_packet(void);
  extern void Netif_Config(void);
  extern void cmd_wifi_wlutil( uint32_t argc, uint8_t **argv );
  
  //Debug related functions
  void debugInit(uint32_t baudrate);
  
  void cmd_wifi_wlutil( uint32_t argc, uint8_t **argv );
  void mhd_read_current_config(void);
  
  
#define WiFiF2TxThreadResume( )   osSemaphoreRelease( gWiFiCtrl.rxThreadWakeSemaphore)

#ifdef __cplusplus
}
#endif

#endif /* __WIFI_DEF_H */


/************************ (C) COPYRIGHT LibreWireless Inc *****END OF FILE****/
