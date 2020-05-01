/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


/*
 * Amazon FreeRTOS
 * Copyright (C) 2017 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://aws.amazon.com/freertos
 * http://www.FreeRTOS.org
 */


/*
 * Debug setup instructions:
 * 1) Open the debug configuration dialog.
 * 2) Go to the Debugger tab.
 * 3) If the 'Mode Setup' options are not visible, click the 'Show Generator' button.
 * 4) In the Mode Setup|Reset Mode drop down ensure that
 *    'Software System Reset' is selected.
 */

#include "main.h"
#include "stdint.h"
#include "stdarg.h"
#include "stm32f7xx.h"

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
/* Test includes */
#include "aws_test_runner.h"
//#include "iot_system_init.h"
#include "iot_logging_task.h"
#include "iot_wifi.h"
#include "aws_clientcredential.h"
//#include "aws_dev_mode_key_provisioning.h"

/* The SPI driver polls at a high priority. The logging task's priority must also
 * be high to be not be starved of CPU time. */
#define mainLOGGING_TASK_PRIORITY           ( configMAX_PRIORITIES - 1 )
#define mainLOGGING_TASK_STACK_SIZE         ( configMINIMAL_STACK_SIZE * 4 )
#define mainLOGGING_MESSAGE_QUEUE_LENGTH    ( 15 )

#define mainTEST_RUNNER_TASK_STACK_SIZE     ( configMINIMAL_STACK_SIZE * 8 )


void vApplicationDaemonTaskStartupHook( void );

extern UART_HandleTypeDef xConsoleUart;


/**
 * @brief Initializes the STM32L475 IoT node board.
 *
 * Initialization of clock, LEDs, RNG, RTC, and WIFI module.
 */
static void prvMiscInitialization( void );

/**
 * @brief Application runtime entry point.
 */

int main( void )
{
    /* Perform any hardware initialization that does not require the RTOS to be
     * running.  */
    prvMiscInitialization();

    /* Create tasks that are not dependent on the WiFi being initialized. */
    xLoggingTaskInitialize( mainLOGGING_TASK_STACK_SIZE,
                            mainLOGGING_TASK_PRIORITY,
                            mainLOGGING_MESSAGE_QUEUE_LENGTH );

    /* Start the scheduler.  Initialization that requires the OS to be running,
     * including the WiFi initialization, is performed in the RTOS daemon task
     * startup hook. */
    vTaskStartScheduler();

    return 0;
}


/**
 * @brief Initializes the board.
 */
static void prvMiscInitialization( void )
{
  /*
  Call to Init Mavid SDK, without which the device does not BOOT 
  */
  device_init();
}


/**
 * @brief UART console initialization function.
 */


void Console_UART_Init( void )
{
	xConsoleUart.Instance        = UART5;
	xConsoleUart.Init.BaudRate   = 115200; //460800;//
	xConsoleUart.Init.WordLength = UART_WORDLENGTH_8B;
	xConsoleUart.Init.StopBits   = UART_STOPBITS_1;
	xConsoleUart.Init.Parity     = UART_PARITY_NONE;//UART_PARITY_ODD;
	xConsoleUart.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
	xConsoleUart.Init.Mode       = UART_MODE_TX_RX;

  if (HAL_UART_Init(&xConsoleUart) != HAL_OK)
  {
  }
  print_ver();
  {
    /* Transfer error in transmission process */
    //Error_Handler();
  }
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
    static TickType_t xLastPrint = 0;
    TickType_t xTimeNow;
    const TickType_t xPrintFrequency = pdMS_TO_TICKS( 2000 );

    xTimeNow = xTaskGetTickCount();

    if( ( xTimeNow - xLastPrint ) > xPrintFrequency )
    {
        configPRINT( "." );
        xLastPrint = xTimeNow;
    }
}

/*-----------------------------------------------------------*/

void vApplicationDaemonTaskStartupHook( void )
{
    WIFIReturnCode_t xWifiStatus;

    /* Turn on the WiFi before key provisioning. This is needed because
     * if we want to use OFFLOAD SSL, device certificate and key is stored
     * on the WiFi module during key provisioning which requires the WiFi
     * module to be initialized. */
    start_wifi_threads();
    xWifiStatus = WIFI_On();

    if( xWifiStatus == eWiFiSuccess )
    if (1)
    {
        configPRINTF( ( "WiFi module initialized.\r\n" ) );

        /* A simple example to demonstrate key and certificate provisioning in
         * microcontroller flash using PKCS#11 interface. This should be replaced
         * by production ready key provisioning mechanism. */
        vDevModeKeyProvisioning();

        {
            /* Connect to the wifi before running the demos */
            prvWifiConnect();

            /* Create the task to run tests. */
            xTaskCreate( TEST_RUNNER_RunTests_task,
                         "TestRunner",
                         mainTEST_RUNNER_TASK_STACK_SIZE,
                         NULL,
                         tskIDLE_PRIORITY,
                         NULL );
        }
    }
    else
    {
        configPRINTF( ( "WiFi module failed to initialize.\r\n" ) );

        /* Stop here if we fail to initialize WiFi. */
  //      configASSERT( xWifiStatus == eWiFiSuccess );
    }
}
/*-----------------------------------------------------------*/


void vMainUARTPrintString( char * pcString )
{
    const uint32_t ulTimeout = 3000UL;

    HAL_UART_Transmit( &xConsoleUart,
                       ( uint8_t * ) pcString,
                       strlen( pcString ),
                       ulTimeout );
}
/*-----------------------------------------------------------*/


