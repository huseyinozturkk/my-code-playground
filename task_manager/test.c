#include "stdio.h"
#include "task_manager.h"
#include "task_manager_config.h"

void test_handler0(void){printf("TEST HANDLER0\r\n");}
void test_handler1(void){printf("TEST HANDLER1\r\n");}
void test_handler2(void){printf("TEST HANDLER2\r\n");}
void test_handler3(void){printf("TEST HANDLER3\r\n");}
void test_handler4(void){printf("TEST HANDLER4\r\n");}

int main(int argc, char const *argv[])
{
    printf("TASK MANAGER TEST\r\n");

    initTaskManager();
    
    for (int i = 0; i < (MAX_PRIORITY + 5); i++)
    {
        printf("TEST - addPriorityGroup ret : %d\r\n",addPriorityGroups());
    }
    
    printTaskManagerStatus();
    
    addTask(2, 1, test_handler0);
    addTask(2, 3, test_handler1);
    addTask(2, 4, test_handler2);
    addTask(2, 5, test_handler3);
    addTask(4, 12, test_handler4);
    addTask(4, 12, test_handler0);

    printTaskManagerStatus();
    
    removeTask(2, 1);
    removeTask(2, 0);
    removeTask(2, 9);

    printTaskManagerStatus();

    taskController();

    return 0;
}
