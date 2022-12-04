#include "task_manager.h"
#include "stdio.h"

void print_priority_group_list(task_manager_t *manager);

int main(int argc, char const *argv[])
{
    printf("Task manager test...\r\n");   

    task_manager_t my_manager;
    task_manager_init(&my_manager);
    printf("task_manager_inited first node with id :%d\r\n", my_manager.priority_head->priority_id);
    
    print_priority_group_list(&my_manager);

    priority_group_add(&my_manager);
    priority_group_add(&my_manager);
    priority_group_add(&my_manager);
    priority_group_add(&my_manager);

    print_priority_group_list(&my_manager);

    
    return 0;
}

void print_priority_group_list(task_manager_t *manager)
{
    printf("printing priority group list ...\r\n");

    priority_t *curr_priority = manager->priority_head;
    while (curr_priority != NULL)
    {
        printf("current priority id : %d\r\n", curr_priority->priority_id);
        curr_priority = curr_priority->priority_next;

    }
}

void print_priority_group_and_task(task_manager_t *manager)
{

}