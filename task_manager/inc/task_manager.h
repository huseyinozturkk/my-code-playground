#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__

#include "stdint.h"

// task
typedef void (*task_handler_t)(void);

typedef struct task
{
    uint8_t task_id;
    task_handler_t handler;
    struct task *task_next;
} task_t;

// priority
typedef struct priority
{
    uint8_t priority_id;
    struct task *task_head;
    struct priority *priority_next;
} priority_t;


// task manager
typedef struct
{
    // TODO: buraya daha fazla birim eklenebilir.
    priority_t *priority_head;
} task_manager_t;

typedef enum
{
    TASK_MANAGER_SUCCESS,
    TASK_MANAGER_ERROR,
    TASK_MANAGER_P_GROUP_MAX_LEN_EXCEED,
    TASK_MANAGER_TASK_MAX_LEN_EXCEED,
    TASK_MAANAGER_NULL_HANDLER,

    TASK_MAX
} task_status_e;

uint8_t task_manager_init(task_manager_t *manager);


uint8_t priority_group_add(task_manager_t *manager);

#endif