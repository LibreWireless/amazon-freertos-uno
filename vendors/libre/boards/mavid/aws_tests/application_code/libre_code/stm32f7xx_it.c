/**
  ******************************************************************************
  * @file    stm32f7xx_it.c
  * @author  Ac6
  * @version V1.0
  * @date    02-Feb-2015
  * @brief   Default Interrupt Service Routines.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "stm32f7xx_hal.h"
#include "stm32f7xx.h"
#ifdef USE_RTOS_SYSTICK
#include <cmsis_os.h>
#endif
#include "stm32f7xx_it.h"

void stackDump(uint32_t stack[]);
#define START_APPLICATION_MAGIC         ((uint32_t)0xDEADBEEFU)

enum { r0, r1, r2, r3, r12, lr, pc, psr};
extern void vLoggingPrint( const char * pcMessage );
#define configPRINT( X )     vLoggingPrint( X )

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M7 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
    while(1);
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
/*void HardFault_Handler(void)
{
    // Go to infinite loop when Hard Fault exception occurs

    printf("HardFault_Handler");
    HAL_PWR_EnableBkUpAccess();
    RTC->BKP0R = START_APPLICATION_MAGIC;
    HAL_PWR_DisableBkUpAccess();
    HAL_NVIC_SystemReset();
    while (1)
    {
    }
}*/


void SystemReset()
{
  HAL_PWR_EnableBkUpAccess();
  RTC->BKP0R = START_APPLICATION_MAGIC;
  HAL_PWR_DisableBkUpAccess();
  HAL_NVIC_SystemReset();
  while (1)
  {
  }
}

void HardFault_Handler(void)
{

   __asm(   "TST lr, #4          \n"

            "ITE EQ              \n"

            "MRSEQ r0, MSP       \n"

            "MRSNE r0, PSP       \n"

		   	"MOV sp, r0          \n"

		   "bkpt #1              \n"

            "B Hard_Fault_Handler\n"

   );
}

void Hard_Fault_Handler(uint32_t stack[])
{
  static char msg[80];

//  configPRINT("In Hard Fault Handler\n");

//  xDumpTaskInfo();
  sprintf(msg, "SCB->HFSR = 0x%08x\n", SCB->HFSR);
//  configPRINT(msg);

  if ((SCB->HFSR & (1 << 30)) != 0) {
//	  configPRINT("Forced Hard Fault\n");
    sprintf(msg, "SCB->CFSR = 0x%08x\n", SCB->CFSR );
//    configPRINT(msg);

    if((SCB->CFSR & 0xFFFF0000) != 0) {
    	sprintf(msg, "Usage Fault\n");
    }

    if((SCB->CFSR & 0xFF00) != 0) {
    	sprintf(msg, "Usage Fault\n");
    }

    if((SCB->CFSR & 0xFF) != 0) {
    	sprintf(msg, "Usage Fault\n");
    }
  }
  stackDump(stack);

  SystemReset();

}


void stackDump(uint32_t stack[])
{

   static char msg[80];

   sprintf(msg, "r0  = 0x%08x\n", stack[r0]);

//   configPRINT(msg);

   sprintf(msg, "r1  = 0x%08x\n", stack[r1]);

//   configPRINT(msg);

   sprintf(msg, "r2  = 0x%08x\n", stack[r2]);

//   configPRINT(msg);

   sprintf(msg, "r3  = 0x%08x\n", stack[r3]);

//   configPRINT(msg);

   sprintf(msg, "r12 = 0x%08x\n", stack[r12]);

//   configPRINT(msg);

   sprintf(msg, "lr  = 0x%08x\n", stack[lr]);

//   configPRINT(msg);

   sprintf(msg, "pc  = 0x%08x\n", stack[pc]);

 //  configPRINT(msg);

   sprintf(msg, "psr = 0x%08x\n", stack[psr]);

 //  configPRINT(msg);

}
/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/******************************************************************************/
/*            	  	    Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles SysTick Handler, but only if no RTOS defines it.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
#ifdef USE_RTOS_SYSTICK
	osSystickHandler();
#endif
}
void WWDG_IRQHandler(void)
{

}
void EXTI9_5_IRQHandler(void)
{
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_5) != RESET)
	  {
	    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
	  }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_6) != RESET)
	  {
	    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
	  }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_7) != RESET)
	  {
	    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
	  }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_8) != RESET)
	  {
	    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
	  }
	  if(__HAL_GPIO_EXTI_GET_IT(GPIO_PIN_9) != RESET)
	  {
	    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
	  }

}

/* When using the ST HAL, we must implement their systick callback. So, here,
 * we simply call the RTOS systick handler that resides in the core level abstraction.
 */

void HAL_SYSTICK_Callback( void )
{
	xPortSysTickHandler( );
}

