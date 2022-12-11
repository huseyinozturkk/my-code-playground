/**
 * @file task_manager.c
 * @author Hüseyin Öztürk
 * @brief Task manager driven by 2 dimension linked list.
 * @version 0.1
 * @date 2022-12-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "task_manager.h"
#include "task_manager_config.h"

#include "stdlib.h"

static task_manager_t *manager = NULL;

/* caveman debug (printf) */
#if TM_DEBUG

#include "stdio.h"

#endif

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t initTaskManager()
{
    uint8_t err_code = TM_OK;

    // init manager first
    manager = (task_manager_t*) malloc(sizeof(task_manager_t));
    if (manager == NULL) {
        err_code = TM_M_NEM;
        goto error;
    }

    // init first priority group head
    priority_t *priority_head = NULL;
    priority_head = (priority_t*) malloc(sizeof(priority_t));

    if (priority_head == NULL) {
        err_code = TM_P_NEM;
        goto error;
    }

    manager->priority_head = priority_head;
    manager->priority_head->priority_id = 0;
    manager->priority_head->priortiy_next = NULL;

error:
#if TM_DEBUG
    printf("DEBUG >> Task manager init return: %d\r\n", err_code);
#endif
    return err_code;
}

/**
 * @brief 
 * 
 * @return uint8_t 
 */
uint8_t addPriorityGroups()
{
    uint8_t status = TM_OK;
    uint8_t index = 1;
    priority_t *curr_p = manager->priority_head;

    if (curr_p == NULL) {
#if TM_DEBUG
        printf("DEBUG >> Head of priority group not inited.\r\n");
#endif
    }

    /* walk end of the list */
    while (curr_p->priortiy_next != NULL)
    {
        index ++;
        curr_p = curr_p->priortiy_next;
    }

    /* control for priority len exceed */
    if (index > MAX_PRIORITY) {
        status = TM_PG_EXCEED;
        goto error;
    }

    /* alloc mem for new priority group */
    curr_p->priortiy_next = (priority_t*) malloc(sizeof(priority_t));
    if (curr_p->priortiy_next == NULL) {
        status = TM_P_NEM;
        goto error;
    }

    /* alloc mem for new priority group's task head */
    task_t *temp = NULL;
    temp = (task_t*) malloc(sizeof(task_t));
    temp->task_id = 0;
    temp->task_handler = NULL;  // TODO: maybe can be added ??
    temp->task_next = NULL;
    
    if (temp != NULL) {
        curr_p->task_head = temp;
    } else {
        status = TM_T_NEM;
        goto error;
    }

    /* set priority id by index */
    curr_p->priortiy_next->priority_id = index;
    /* set end of the list */
    curr_p->priortiy_next->priortiy_next = NULL;
    
error:
    return status;
}

/**
 * @brief 
 * 
 * @param priority_group_id 
 * @param task_id 
 * @param handler 
 * @return uint8_t 
 */
uint8_t addTask(uint8_t priority_group_id, uint8_t task_id, task_handler_t handler)
{
    uint8_t status = TM_OK;
    
    /* check for inputs */
    if (priority_group_id > MAX_PRIORITY) {
        status = TM_PG_EXCEED;
        goto error;
    }

    if (handler == NULL) {
        status = TM_HANDLER_NULL;
        goto error;
    }

    /* go for priority group by id */
    priority_t *curr_p = manager->priority_head;

    for (int i = 0 ; i < priority_group_id ; i++) 
    {
        curr_p = curr_p->priortiy_next;
    }
    
    /* check id same task id in list */
    uint8_t flag = 0;
    task_t *temp = curr_p->task_head;
    while(temp != NULL) {
        if (temp->task_id == task_id) {
            flag = 1;
            break;
        }
        temp = temp->task_next;
    }

    if (flag != 0) {
        status = TM_TID_ALRDY;
        goto error;
    }


    /* go end of the task list and add new task */
    task_t *curr_t = curr_p->task_head;
    
    while (curr_t->task_next != NULL) 
    {   
        curr_t = curr_t->task_next;
    }
    
    /* set inputs */
    curr_t->task_next = (task_t*) malloc(sizeof(task_t));

    if (curr_t != NULL) {
        curr_t->task_next->task_id = task_id;
        curr_t->task_next->task_handler = handler;

        /* set end of the task list */
        curr_t->task_next->task_next = NULL;  
    } else {
        status = TM_T_NEM;
        goto error;
    } 
error:
#if TM_DEBUG
        printf("DEBUG >> addTask(%d, %d) ret : %d\r\n",priority_group_id ,task_id ,status);
#endif
    return status;
}

/**
 * @brief 
 * 
 * @param priority_group_id 
 * @param task_id 
 * @return uint8_t 
 */
uint8_t removeTask(uint8_t priority_group_id, uint8_t task_id)
{
    uint8_t status = TM_OK;

    /* check for input limit */
    if (priority_group_id > MAX_PRIORITY) {
        status = TM_PG_EXCEED;
        goto error;
    }

    /* task id 0 is default for priority heads so it mustnt deleted */
    if (task_id == 0) {
        status = TM_ERR;
        goto error;
    }   

    /* go for priority group by id */
    priority_t *curr_p = manager->priority_head;

    for (int i = 0 ; i < priority_group_id ; i++) 
    {
        curr_p = curr_p->priortiy_next;
    }

    /* check if id in list */
    uint8_t flag = 0;
    task_t *check = curr_p->task_head;
    while( check != NULL) 
    {
        if (check->task_id == task_id)
        {
            flag = 1;
            break;
        }
        check = check->task_next;
    }

    if (flag != 1) {
        status = TM_TID_NOT;
        goto error;
    }

    /* find task by id */
    task_t *curr_t = curr_p->task_head;
    while (curr_t != NULL) 
    {   
        if (curr_t->task_next->task_id == task_id) {
            break;
        }
        curr_t = curr_t->task_next;
    }

    if (curr_t->task_next->task_next != NULL) {
        task_t *temp;

        temp = curr_t->task_next->task_next;
        free(curr_t->task_next);
        curr_t->task_next = temp;
    } else {
        /* element is last element on the list */
        /* delete the end of the list */
        free(curr_t->task_next);

        /* make current node end of the list */
        curr_t->task_next = NULL;
    }

error:
#if TM_DEBUG
    printf("DEBUG >> removeTask(%d, %d) ret : %d\r\n", priority_group_id, task_id, status);
#endif
    return status;
}

/**
 * @brief 
 * 
 */
void taskController()
{
    /* go through in group list */
    priority_t *curr_p = manager->priority_head;
    while (curr_p != NULL)
    {
        /* go through in task list */
        task_t *curr_t = curr_p->task_head;
        while(curr_t != NULL)
        {   
            /* execute task */
            if (curr_t->task_handler != NULL) {
                curr_t->task_handler();
            }
            curr_t = curr_t->task_next;
        }

        curr_p = curr_p->priortiy_next;
    }    

}

/**
 * @brief 
 * 
 */
void printTaskManagerStatus()
{
    printf("----------------------------------------------------\r\n");
    priority_t *curr_p = manager->priority_head;
    while (curr_p != NULL)
    {
        task_t *curr_t = curr_p->task_head;
        while(curr_t != NULL)
        {
#if TM_DEBUG 
            printf("DEBUG >> Current priority group : %d - task : %d\r\n", curr_p->priority_id, curr_t->task_id);
#endif
            curr_t = curr_t->task_next;
        }

        curr_p = curr_p->priortiy_next;
    }
    printf("----------------------------------------------------\r\n");
}