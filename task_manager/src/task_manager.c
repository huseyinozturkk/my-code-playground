#include "task_manager.h"
#include "task_config.h"

#include "stdint.h"
#include "stdlib.h"

// implement your own debug here
#if DEBUG_TASK_MANAGER
#include "stdio.h"

static void debug(char *msg)
{
    printf("DEBUG >> ");
    printf(msg);
}

static void print_state(uint8_t state)
{
    switch (state)
    {
    case TASK_MANAGER_SUCCESS:
        /* code */
        break;

    case TASK_MANAGER_ERROR:
        break;
    
    case TASK_MANAGER_P_GROUP_MAX_LEN_EXCEED:
        break;

    case TASK_MANAGER_TASK_MAX_LEN_EXCEED:
        break;

    case TASK_MAANAGER_NULL_HANDLER:
        break;

    default:
        break;
    }
}

#endif

uint8_t task_manager_init(task_manager_t *manager)
{
    uint8_t err_code = TASK_MANAGER_SUCCESS;
    
    priority_t *priority_head = NULL;
    priority_head = (priority_t*) malloc(sizeof(priority_t));

    if (priority_head == NULL) {
        err_code = TASK_MANAGER_ERROR;
        goto error;
    }

    manager->priority_head = priority_head;
    manager->priority_head->priority_id = 0;
    manager->priority_head->priority_next = NULL;

error:

#if DEBUG_TASK_MANAGER
    debug("task_manager_init()\r\n");
    debug("task manager init state : ");
    err_code == TASK_MANAGER_ERROR ? debug("ERROR\r\n") : debug("SUCCESS\r\n");
#endif

    return err_code;
}

/**
 * @brief 
 * 
 * @param manager 
 * @return uint8_t 
 */
uint8_t priority_group_add(task_manager_t *manager)
{
    uint8_t err_code = TASK_MANAGER_SUCCESS;
    uint8_t p_group_index = 1;

    priority_t *curr = manager->priority_head;
    while (curr->priority_next != NULL)
    {
        p_group_index ++;
        curr = curr->priority_next;
    }

    if (p_group_index >= MAX_PRIORITY_GROUP_LEN) {
        err_code = TASK_MANAGER_P_GROUP_MAX_LEN_EXCEED;
        goto error;
    }

    curr->priority_next = (priority_t*) malloc(sizeof(priority_t));
    curr->priority_next->priority_id = p_group_index;

    curr->priority_next->priority_next = NULL;

error:

#if DEBUG_TASK_MANAGER
    debug("priority_group_add()\r\n");
    print_state(err_code);
#endif

    return err_code;
}

/**
 * @brief 
 * 
 * @param manager 
 * @param task_priority_group 
 * @param task_handler 
 * @return uint8_t 
 */
uint8_t task_add(task_manager_t *manager, uint8_t task_priority_group, task_handler_t task_handler)
{
    uint8_t err_code = TASK_MANAGER_SUCCESS;

    if (task_priority_group > MAX_PRIORITY_GROUP_LEN) {
        err_code = TASK_MANAGER_P_GROUP_MAX_LEN_EXCEED;
        goto error;
    }

    if (task_handler == NULL) {
        err_code = TASK_MAANAGER_NULL_HANDLER;
        goto error;
    }

    

error:
    return err_code;
}

