#ifndef PF_CTRL_H
#define PF_CTRL_H

//#include "stm32f4xx_hal.h"
#include "stm32f7xx_hal.h"


#ifdef LIBRE_PORT

// BT GPIO pins

// WiFi OUT Pin13 groupI (PH10)
#define WIFI_CTRL_REGON_PIN               GPIO_PIN_10
#define WIFI_CTRL_REGON_ACCESS_EN         __HAL_RCC_GPIOH_CLK_ENABLE();
#define WIFI_CTRL_REGON_PORT              GPIOH
 
// OUT Pin5 groupK (PH11)
#define PF_CTRL_REGON_PIN               GPIO_PIN_11
#define PF_CTRL_REGON_ACCESS_EN         __HAL_RCC_GPIOH_CLK_ENABLE();
#define PF_CTRL_REGON_PORT              GPIOH
 
 
#define PF_CTRL_HOST_DEVUP_PIN           GPIO_PIN_9
#define PF_CTRL_HOST_DEVUP_ACCESS_EN    __HAL_RCC_GPIOH_CLK_ENABLE();
#define PF_CTRL_HOST_DEVUP_PORT         GPIOH


// IN Pin4  GroupK ( PH8)
#define PF_CTRL_HOST_WAKEUP_PIN          GPIO_PIN_8
#define PF_CTRL_HOST_WAKEUP_ACCESS_EN   __HAL_RCC_GPIOH_CLK_ENABLE();
#define PF_CTRL_HOST_WAKEUP_PORT        GPIOH   


#define PF_CTRL_HOST_WAKEUP_PIN_1_1          GPIO_PIN_2
#define PF_CTRL_HOST_WAKEUP_ACCESS_EN_1_1   __HAL_RCC_GPIOA_CLK_ENABLE();
#define PF_CTRL_HOST_WAKEUP_PORT_1_1        GPIOA   


// common
#define PF_CTRL_HOST_DEVUP_ACCESS_DIS   __HAL_RCC_GPIOH_CLK_DISABLE();


// OUT Not USE, pin9 GoupB ( PB9)
#define PF_CTRL_RESET_PIN               GPIO_PIN_9
#define PF_CTRL_RESET_ACCESS_EN         __HAL_RCC_GPIOB_CLK_ENABLE();
#define PF_CTRL_RESET_PORT              GPIOB
 

#else

#define PF_CTRL_RESET_PIN		GPIO_PIN_6
#define PF_CTRL_HOST_WAKEUP_PIN		GPIO_PIN_8
#define PF_CTRL_HOST_DEVUP_PIN	   	GPIO_PIN_9
#define PF_CTRL_REGON_PIN		GPIO_PIN_5

#endif


extern void pf_ctrl_init(void);
extern void pf_ctrl_deinit(void);
extern void pf_ctrl_bt_regon(void);
extern void pf_ctrl_bt_regoff(void);
extern void pf_ctrl_host_wakeup(void);
extern void pf_ctrl_dev_wakeup(void);
extern void pf_ctrl_enable_lpm_interrupt(void);
extern void pf_ctrl_disable_lpm_interrupt(void);

#endif
