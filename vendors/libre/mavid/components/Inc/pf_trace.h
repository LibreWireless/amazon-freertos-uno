#ifndef PF_TRACE_H
#define PF_TRACE_H

#include <stdint.h>


#ifdef LIBRE_PORT     
     
// This is UART defined for trace UART     
#define USARTx                           UART5
     
#define USARTx_CLK_ENABLE()              __UART5_CLK_ENABLE()
#define USARTx_RX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __GPIOB_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __UART5_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __UART5_RELEASE_RESET()     
     
     
/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_9
#define USARTx_TX_GPIO_PORT              GPIOB
#define USARTx_TX_AF                     GPIO_AF7_UART5
#define USARTx_RX_PIN                    GPIO_PIN_5
#define USARTx_RX_GPIO_PORT              GPIOB
#define USARTx_RX_AF                     GPIO_AF1_UART5

/* Definition for USARTx's NVIC IRQ and IRQ Handlers */
#define USARTx_IRQn                      UART5_IRQn
#define USARTx_IRQHandler                UART5_IRQHandler
     
     
     
#else
     
#define USARTx                           USART2
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART2_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOA_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART2_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_2
#define USARTx_TX_GPIO_PORT              GPIOA
#define USARTx_TX_AF                     GPIO_AF7_USART2
#define USARTx_RX_PIN                    GPIO_PIN_3
#define USARTx_RX_GPIO_PORT              GPIOA
#define USARTx_RX_AF                     GPIO_AF7_USART2

#endif     


typedef union 
{
    unsigned char sigs;
    unsigned char error;
}tP_DATA;

typedef void (pf_trace_cplt_cb_t)(unsigned char port, unsigned char event, tP_DATA* p_data);

void pf_trace_init(pf_trace_cplt_cb_t* cb);
void pf_trace_deinit(void);
void pf_trace(const char* fmt, ...);
unsigned int pf_trace_send(unsigned char * data, unsigned int length);
unsigned int pf_trace_receive(unsigned char * data, unsigned int length);
uint8_t pf_trace_get_status(void);


#endif
