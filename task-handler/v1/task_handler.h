/*
 * task_handler.h
 *
 *  Created on: Nov 22, 2022
 *      Author: huseyin ozturk
 */

#ifndef _TASK_HANDLER_H_
#define _TASK_HANDLER_H_

#include "stddef.h"
#include "stdint.h"

#define DEBUG_TASK          ( 0 )
#define TASK_COUNT_MAX      ( 16 )

typedef enum
{
    TASK_ID_0,
    TASK_ID_1,
    TASK_ID_2,
    TASK_ID_3,
    TASK_ID_4,
    TASK_ID_5,
    TASK_ID_6,
    TASK_ID_7,
    TASK_ID_8,
    TASK_ID_9,
    TASK_ID_10,
    TASK_ID_11,
    TASK_ID_12,
    TASK_ID_13,
    TASK_ID_14,
    TASK_ID_15
} task_id_t;


typedef enum
{
    TASK_OK,
    TASK_ERR,
    TASK_NULL,
    TASK_EMPTY,
    TASK_NOT_EMPTY,
    TASK_PERIOD_ZERO
} task_status_e;


typedef void (*task_handler_t)(void);

typedef struct
{
    uint8_t task_id;
    uint16_t task_period;
    uint32_t task_last_time;
    task_handler_t task_handler;
} task_t;

task_t task_struct_config(task_id_t id, uint16_t period, task_handler_t handler);
task_status_e task_init(task_t t);
void task_handler(uint32_t tick);


#endif /* _TASK_HANDLER_H_ */
