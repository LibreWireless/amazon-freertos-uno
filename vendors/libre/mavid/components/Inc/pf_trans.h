#ifndef PF_TRANS_H
#define PF_TRANS_H

#include <stdint.h>
#include "freeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define PF_TRANS_STATUS_READY  1
#define PF_TRANS_STATUS_STOP   0

extern void  pf_trans_init(uint32_t baud);
extern void  pf_trans_deinit(void);
extern uint8_t pf_trans_get_status(void);
extern void pf_trans_reconfig_baud(uint32_t baud);
extern uint32_t pf_trans_send(unsigned char * data, unsigned int length);
extern uint32_t pf_trans_receive(unsigned char * data, unsigned int length);

#endif
