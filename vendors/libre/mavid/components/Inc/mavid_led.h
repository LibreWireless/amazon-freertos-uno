
/* File Not Used */
#if 0

#ifndef _GPIO_TEST_H_
#define _GPIO_TEST_H_


#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_gpio.h"
#include "os_port.h"
#include <compiler_port.h>

#define LED_CNT                              (6)
#define BUTTON_CNT                           (10)

#define WAKEUP_PIN                 GPIO_PIN_0
#define PAIR_SHARE_PIN             GPIO_PIN_3
#define SOURCE_SEL_PIN             GPIO_PIN_15
#define SETUP_PIN                  GPIO_PIN_13
#define NEXT_PIN                   GPIO_PIN_4
#define PREV_PIN                   GPIO_PIN_5
#define VOL_PLUS_PIN               GPIO_PIN_11
#define VOL_MINS_PIN               GPIO_PIN_4
#define PLAY_PAUSE_PIN             GPIO_PIN_6
#define MIC_ON_OFF_PIN             GPIO_PIN_10

#define LVM_RED                             GPIOB
#define LVM_RED_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LVM_RED_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define LVM_RED_PIN                         GPIO_PIN_11

#define LVM_BLUE                             GPIOB
#define LVM_BLUE_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOB_CLK_ENABLE()
#define LVM_BLUE_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOB_CLK_DISABLE()
#define LVM_BLUE_PIN                         GPIO_PIN_10

#define LVM_GREEN                             GPIOC
#define LVM_GREEN_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()
#define LVM_GREEN_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()
#define LVM_GREEN_PIN                         GPIO_PIN_14

#define RED                                  GPIOD
#define RED_GPIO_CLK_ENABLE()                __HAL_RCC_GPIOD_CLK_ENABLE()
#define RED_GPIO_CLK_DISABLE()               __HAL_RCC_GPIOD_CLK_DISABLE()
#define RED_PIN                              GPIO_PIN_6

#define GREEN                                GPIOH
#define GREEN_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOH_CLK_ENABLE()
#define GREEN_GPIO_CLK_DISABLE()             __HAL_RCC_GPIOH_CLK_DISABLE()
#define GREEN_PIN                            GPIO_PIN_13

#define BLUE                                GPIOH
#define BLUE_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOH_CLK_ENABLE()
#define BLUE_GPIO_CLK_DISABLE()             __HAL_RCC_GPIOH_CLK_DISABLE()
#define BLUE_PIN                            GPIO_PIN_14

#define LEDx_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LVM_RED_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 1) LVM_BLUE_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 2) LVM_GREEN_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 3) GREEN_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 4) BLUE_GPIO_CLK_ENABLE(); else \
											if((__INDEX__) == 5) RED_GPIO_CLK_ENABLE(); \
                                            }while(0)

#define LEDx_CLK_DISABLE(__INDEX__)  do{if((__INDEX__) == 0) LVM_RED_GPIO_CLK_DISABLE(); else \
                                             if((__INDEX__) == 1) LVM_BLUE_GPIO_CLK_DISABLE(); else \
                                             if((__INDEX__) == 2) LVM_GREEN_GPIO_CLK_DISABLE(); else \
                                             if((__INDEX__) == 3) GREEN_GPIO_CLK_DISABLE(); else \
                                             if((__INDEX__) == 4) BLUE_GPIO_CLK_DISABLE(); else\
											 if((__INDEX__) == 5) RED_GPIO_CLK_DISABLE(); \
                                             }while(0)

#define TRUE 1
#define FALSE 0
#define DEBOUNCE_DELAY 50 //50 milliseconds
#define LONG_PRESS_THRESHOLD 3000 //milliseconds

#define GPIO_PORT_A 1
#define GPIO_PORT_B 2
#define GPIO_PORT_C 3
#define GPIO_PORT_D 4
#define GPIO_PORT_E 5
#define GPIO_PORT_F 6
#define GPIO_PORT_G 7
#define GPIO_PORT_H 8
#define GPIO_PORT_I 9
typedef enum {
		pressed=0,
		released
	}State;

struct gpioState{
	uint32_t gpio_pin;
	int gpio_port;
	State state;
	uint32_t pressedTime,releasedTime,pressedDuration;
	bool_t isSinglePressEnabled;
	bool_t isDoublePressEnabled;
	bool_t isLongPressEnabled;
	uint32_t gpioDirection;
	bool_t isNewTime;
	bool_t isLongPress;
	struct gpioState *next;
};

typedef struct
{
char_t name[20];
uint32_t gpio_no;
bool_t shortpress;
bool_t longpress;
bool_t doublepress;
int gpio_port;
bool_t isLED;
uint32_t blink_rate;
}setupGPIOs;

typedef enum
{
 LVM_RED_LED = 0,
 LVM_BLUE_LED,
 LVM_GREEN_LED,
 GREEN_LED,
 BLUE_LED,
 RED_LED,
 NO_LED
}Leds_TypeDef;

typedef enum
{
  SW1 = 1,
  SW2 = 2,
  SW3 = 8,
  SW4 = 16,
  SW5 = 32,
  SW6 = 64,
  SW7 = 128,
  SW8 = 512,
  SW9 = 1024,
  SW10 = 2048
}Switch_typeDef;

typedef enum
{
  COMBI_000 = 0,
  COMBI_00B,
  COMBI_0G0,
  COMBI_0GB,
  COMBI_R00,
  COMBI_R0B,
  COMBI_RG0,
  COMBI_RGB,
  COMBI_YG0,
  COMBI_RY0,
  COMBI_0YB,
  COMBI_0GY,
  COMBI_Y0B,
  COMBI_R0Y
}Combi_TypeDef;

typedef enum
{
    AVS_MIC_MUTE             = 0,
    AVS_ACTIVE               = 1,
    AVS_NOT_ACTIVE           = 2,
    AVS_ALEXA_LISTENING      = 3,
    AVS_ALEXA_BUSY           = 4,
    AVS_ALEXA_PLAYING        = 5,
    AVS_VOICE_NO_DISTURB     = 6,
    AVS_WAKE_ALEXA           = 7,
    AVS_MESSAGE_WAITING      = 8,

    WIFI_STATE_CONNECTING    = 9,
    WIFI_STATE_CONNECTED     = 10,
    WIFI_STATE_DISCONNECTED  = 11,
    WIFI_STATE_SETUP_MODE    = 12,

    DEVICE_STATE_BOOTING     = 13,
    DEVICE_STATE_ACTIVE      = 14,
    DEVICE_VOLUME_CHANGE     = 15,
    DEVICE_STATE_LOW_POWER   = 16
    
} LedFeature_Wistron;
typedef enum
{
  OFF = 0,
  ON = 1,
  STOP = 2
  
}LedState_Wistron;


typedef struct
{
  LedFeature_Wistron Feature;
  LedState_Wistron   State;
}LedContext;

//typedef void OsTask;
//#define OsTask int

//Invalid handle value
#define OS_INVALID_HANDLE NULL
 
extern Leds_TypeDef dim_Led;



//void ledsInit(void);
//void switchInit(Switch_typeDef switchs);
void switchInit(setupGPIOs sg);
void ledToggle(Leds_TypeDef Led);
void ledOn(Leds_TypeDef Led);
void ledOff(Leds_TypeDef Led);
void ledDim(Leds_TypeDef Led);
void led_dimmer(void * Led);
void setLed(Combi_TypeDef combination);
void setLVMLed(Combi_TypeDef combination);
struct gpioState* GetNewNode(setupGPIOs sg);
struct gpioState* SearchGpioPin(uint32_t gpio_pin);
void InsertAtHead(setupGPIOs sg);
void printList();
void ledsInit(uint32_t gpio_pin,uint32_t Speed, int gpio_port);



void SetFeature(LedFeature_Wistron Feature, LedState_Wistron State);

#endif // _GPIO_TEST_H_
#endif