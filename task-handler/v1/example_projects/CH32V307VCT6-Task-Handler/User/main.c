/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* SPDX-License-Identifier: Apache-2.0
*******************************************************************************/

/*
 *@Note
 串口打印调试例程：
 USART1_Tx(PA9)。
 本例程演示使用 USART1(PA9) 作打印调试口输出。

*/

#include "debug.h"
#include "task_handler/task_handler.h"

/* Global typedef */

/* Global define */

/* Global Variable */
uint32_t my_tick;

void t0_handler(void);
void t1_handler(void);
void t2_handler(void);
void t3_handler(void);
void get_temperature(void);

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	Delay_Init();
	USART_Printf_Init(115200);
	printf("SystemClk:%d\r\n",SystemCoreClock);

	printf("This is printf example\r\n");

	task_t t0, t1, t2, t3, t4;
	t0 = task_struct_config(TASK_ID_0, 100, t0_handler);
	t1 = task_struct_config(TASK_ID_1, 500, t1_handler);
	t2 = task_struct_config(TASK_ID_2, 1000, t2_handler);
	t3 = task_struct_config(TASK_ID_3, 2000, t3_handler);
	t4 = task_struct_config(TASK_ID_10, 5000, get_temperature);

	task_init(t0);
	task_init(t1);
	task_init(t2);
	task_init(t3);
	task_init(t4);

	my_tick = 0;

	while(1)
    {
	    my_tick ++;
	    Delay_Ms(1);

	    /*
	     *  Implement this in 1KHz interrupt with your timer.
	     */
	    task_handler(my_tick);
	}
}

void t0_handler()
{
    printf("TASK 0\r\n");
}

void t1_handler()
{
    printf("TASK 1\r\n");
}

void t2_handler()
{
    printf("TASK 2\r\n");
}

void t3_handler()
{
    printf("TASK 3\r\n");
}

void get_temperature()
{
    printf("Temperature is : 32 C\r\n");
}
/*
 * You can add your own functions.
 *
 *
 */
