#ifndef __PLATFORM_PERIPHERAL_H__
#define __PLATFORM_PERIPHERAL_H__

#include "mhd_constants.h"
#include "platform_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

/* GPIO port */
typedef char  platform_gpio_port_t;

typedef struct
{
    platform_gpio_port_t* port;       /* GPIO port. platform_gpio_port_t is defined in <HOST-SDK>/MCU/<MCU>/platform_mcu_interface.h */
    uint8_t               pin_number; /* pin number. Valid range is defined in <HOST-SDK>/MCU/<MCU>/platform_mcu_interface.h         */
} platform_gpio_t;

/**
 * Pin configuration
 */
typedef enum
{
    INPUT_PULL_UP,             /* Input with an internal pull-up resistor - use with devices that actively drive the signal low - e.g. button connected to ground */
    INPUT_PULL_DOWN,           /* Input with an internal pull-down resistor - use with devices that actively drive the signal high - e.g. button connected to a power rail */
    INPUT_HIGH_IMPEDANCE,      /* Input - must always be driven, either actively or by an external pullup resistor */
    OUTPUT_PUSH_PULL,          /* Output actively driven high and actively driven low - must not be connected to other active outputs - e.g. LED output */
    OUTPUT_OPEN_DRAIN_NO_PULL, /* Output actively driven low but is high-impedance when set high - can be connected to other open-drain/open-collector outputs. Needs an external pull-up resistor */
    OUTPUT_OPEN_DRAIN_PULL_UP, /* Output actively driven low and is pulled high with an internal resistor when set high - can be connected to other open-drain/open-collector outputs. */
} platform_pin_config_t;

/**
 * GPIO interrupt trigger
 */
typedef enum
{
    IRQ_TRIGGER_RISING_EDGE  = 0x1, /* Interrupt triggered at input signal's rising edge  */
    IRQ_TRIGGER_FALLING_EDGE = 0x2, /* Interrupt triggered at input signal's falling edge */
    IRQ_TRIGGER_BOTH_EDGES   = IRQ_TRIGGER_RISING_EDGE | IRQ_TRIGGER_FALLING_EDGE,
} platform_gpio_irq_trigger_t;

/**
 * GPIO interrupt callback handler
 */
typedef void (*platform_gpio_irq_callback_t)( void* arg );


/**
 * Initialise the specified GPIO pin
 *
 * @param[in] gpio   : gpio pin
 * @param[in] config : pin configuration
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_gpio_init( const platform_gpio_t* gpio, platform_pin_config_t config );


/**
 * Deinitialise the specified GPIO pin
 *
 * @param[in] gpio : gpio pin
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_gpio_deinit( const platform_gpio_t* gpio );


/**
 * Toggle the specified GPIO pin output high
 *
 * @param[in] gpio : gpio pin
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_gpio_output_high( const platform_gpio_t* gpio );


/**
 * Toggle the specified GPIO pin output low
 *
 * @param[in] gpio : gpio pin
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_gpio_output_low( const platform_gpio_t* gpio );


/**
 * Retrieve logic level of the GPIO input pin specified
 *
 * @param[in] gpio : gpio pin
 *
 * @return @ref platform_result_t
 */
host_bool_t platform_gpio_input_get( const platform_gpio_t* gpio );


/**
 * Enable interrupt on the GPIO input pin specified
 *
 * @param[in] gpio    : gpio pin
 * @param[in] trigger : interrupt trigger type
 * @param[in] handler : callback function that will be called when an interrupt occurs
 * @param[in] arg     : argument that will be passed into the callback function
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_gpio_irq_enable( const platform_gpio_t* gpio, platform_gpio_irq_trigger_t trigger, platform_gpio_irq_callback_t handler, void* arg );


/**
 * Disable interrupt on the GPIO input pin specified
 *
 * @param[in] gpio : gpio pin
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_gpio_irq_disable( const platform_gpio_t* gpio );



platform_result_t platform_mcu_powersave_init         ( void );

/**
 * Enable MCU powersave
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_mcu_powersave_enable( void );


/**
 * Disable MCU powersave
 *
 * @return @ref platform_result_t
 */
platform_result_t platform_mcu_powersave_disable( void );


/**
 * Notify the software stack that MCU has exited powersave mode due to interrupt
 *
 * @return @ref platform_result_t
 */
void platform_mcu_powersave_exit_notify( void );


#ifdef __cplusplus
} /*"C" */
#endif
#endif
