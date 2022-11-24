#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

typedef void (*task_handler_t)(void);

typedef struct task
{
    uint8_t task_id;
    task_handler_t handler;
    struct task *next_task;
} task_t;

typedef struct priority
{
    int p_id;
    struct task *head_task;
    struct priority *next_priority;
} priority_t;   


void event_controller(priority_t *head);


void task00_handler(void){printf("PRIORITY0, TASK0\r\n");}
void task10_handler(void){printf("PRIORITY1, TASK0\r\n");}
void task11_handler(void){printf("PRIORITY1, TASK1\r\n");}
void task20_handler(void){printf("PRIORITY2, TASK0\r\n");}
void task21_handler(void){printf("PRIORITY2, TASK1\r\n");}
void task22_handler(void){printf("PRIORITY2, TASK2\r\n");}

int 
main()
{
    // Init priority lists
    priority_t *head_priority = NULL;
    head_priority = (priority_t*) malloc(sizeof(priority_t));
    if (head_priority == NULL) {return -1;}
    head_priority->p_id = 0;    // p0
    
    head_priority->next_priority = (priority_t*) malloc(sizeof(priority_t));
    // add check for malloc
    head_priority->next_priority->p_id = 1; // p1
    
    head_priority->next_priority->next_priority = (priority_t*) malloc(sizeof(priority_t));
    // add check for malloc
    head_priority->next_priority->next_priority->p_id = 2; // p2
    
    head_priority->next_priority->next_priority->next_priority = NULL;
    
    // Init task lists for priorities
    // P0
    task_t *head_task_p0 = NULL;
    head_task_p0 = (task_t*) malloc(sizeof(task_t));
    if (head_task_p0 == NULL) {return -1;}
    head_task_p0->task_id = 0;
    head_task_p0->handler = task00_handler;
    head_task_p0->next_task = NULL;
    
    // P1
    task_t *head_task_p1 = NULL;
    head_task_p1 = (task_t*) malloc(sizeof(task_t));
    if (head_task_p1 == NULL) {return -1;}
    head_task_p1->task_id = 0;
    head_task_p1->handler = task10_handler;
    
    head_task_p1->next_task = (task_t*) malloc(sizeof(task_t));
    head_task_p1->next_task->task_id = 1;
    head_task_p1->next_task->handler = task11_handler;
    
    head_task_p1->next_task->next_task = NULL;
    
    
    // P2
    task_t *head_task_p2 = NULL;
    head_task_p2 = (task_t*) malloc(sizeof(task_t));
    if (head_task_p2 == NULL) {return -1;}
    head_task_p2->task_id = 0;
    head_task_p2->handler = task20_handler;
    
    head_task_p2->next_task = (task_t*) malloc(sizeof(task_t));
    head_task_p2->next_task->task_id = 1;
    head_task_p2->next_task->handler = task21_handler;
    
    head_task_p2->next_task->next_task = (task_t*) malloc(sizeof(task_t));
    head_task_p2->next_task->next_task->task_id = 2;
    head_task_p2->next_task->next_task->handler = task22_handler;
    
    head_task_p2->next_task->next_task->next_task = NULL;
    
    // Bind task lists for each priority grup
    head_priority->head_task = head_task_p0;
    head_priority->next_priority->head_task = head_task_p1;
    head_priority->next_priority->next_priority->head_task = head_task_p2;
    
    event_controller(head_priority);
    
    return 0;
}

void 
event_controller(priority_t *head)
{
    // Walk through in priority list
    priority_t *curr_p  = head;
    while (curr_p != NULL)
    {
        task_t *curr_task = curr_p->head_task;
        while (curr_task != NULL)
        {
            // Walk through in priority task list and run handlers.
            curr_task->handler();
            curr_task = curr_task->next_task;
        }
        
        curr_p = curr_p->next_priority;
    }
}
