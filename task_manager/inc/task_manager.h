/**
 * @file task_manager.h
 * @author Hüseyin Öztürk
 * @brief 
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "stdint.h"

typedef void (*task_handler_t)(void);

typedef struct task
{
    uint8_t task_id;
    task_handler_t task_handler;
    struct task *task_next;
} task_t;

typedef struct priority 
{
    uint8_t priority_id;
    struct task *task_head;
    struct priority *priortiy_next;
} priority_t;

typedef struct
{
    priority_t *priority_head;
} task_manager_t;

typedef enum
{
    TM_OK,              /* Ok */
    TM_ERR,             /* Error */
    TM_PG_EXCEED,       /* Max priority group len exceed. */
    TM_T_EXCEED,        /* Max task list len exceed. */
    TM_M_NEM,           /* Not enough mem for task manager init */
    TM_P_NEM,           /* Not enough mem for priority add */
    TM_T_NEM,           /* Not enough mem for task add */
    TM_HANDLER_NULL,    /* Task handler is null */
    TM_TID_NOT,         /* Task id not in task list */
    TM_TID_ALRDY,       /* Task id is already in task list */

    ENUM_MAX
} task_manager_status_e;


uint8_t initTaskManager(void);

uint8_t addPriorityGroups(void);

uint8_t addTask(uint8_t priority_group_id, uint8_t task_id, task_handler_t handler);

uint8_t removeTask(uint8_t priority_group_id, uint8_t task_id);

void taskController(void);

void printTaskManagerStatus(void);

#endif /* __TASK_MANAGER_H__ */