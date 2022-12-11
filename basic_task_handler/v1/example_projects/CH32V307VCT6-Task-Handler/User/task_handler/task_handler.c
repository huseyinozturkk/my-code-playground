/*
 * task_handler.c
 *
 *  Created on: Nov 22, 2022
 *      Author: huseyin ozturk
 */

#include "task_handler.h"

static task_t tasks[TASK_COUNT_MAX];

task_t task_struct_config(task_id_t id, uint16_t period, task_handler_t handler)
{
    task_t task_init_struct = {0};

    task_init_struct.task_id = id;
    task_init_struct.task_period = period;
    task_init_struct.task_handler = handler;
    task_init_struct.task_last_time = 0;

    return task_init_struct;
}

task_status_e task_init(task_t t)
{
    task_status_e status = TASK_OK;

    // TODO : check for limits
    if (t.task_id > TASK_COUNT_MAX) {
        status = TASK_ERR;
        goto error;
    }

    if (t.task_period == 0) {
        status = TASK_PERIOD_ZERO;
        goto error;
    }

    if (t.task_handler == NULL) {
        status = TASK_NULL;
        goto error;
    }

    if (tasks[t.task_id].task_handler != NULL)
    {
        status = TASK_NOT_EMPTY;
        goto error;
    }

    tasks[t.task_id].task_handler = t.task_handler;
    tasks[t.task_id].task_id = t.task_id;
    tasks[t.task_id].task_period = t.task_period;
    tasks[t.task_id].task_last_time = 0;


error:
#if DEBUG_TASK
    printf("task_init() - task id : %d ,task period : %d ,return status : %d\r\n",t.task_id ,t.task_period ,status);
#endif

    return status;
}

void task_handler(uint32_t tick)
{
    for (int i = 0; i < TASK_COUNT_MAX; i++) {

        if (tasks[i].task_handler != NULL) {

            if ((tasks[i].task_last_time + tasks[i].task_period) < tick) {

                /* TODO : calculate task time
                * add task_last_execution_time to task_t and implement
                * store start_time in temporary var.
                * when function executed calculate execution time with previous - start time
                */

                // execute task
                tasks[i].task_handler();

                // update last tick
                tasks[i].task_last_time = tick;

            }
        } else {
                // TODO : error catch ?
        }
    }
}

