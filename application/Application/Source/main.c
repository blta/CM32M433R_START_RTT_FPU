/*******************************************************************************
*
* COPYRIGHT(c) 2020, China Mobile IOT
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*	1. Redistributions of source code must retain the above copyright notice,
*	   this list of conditions and the following disclaimer.
*	2. Redistributions in binary form must reproduce the above copyright notice,
*	   this list of conditions and the following disclaimer in the documentation
*	   and/or other materials provided with the distribution.
*	3. Neither the name of China Mobile IOT nor the names of its contributors
*	   may be used to endorse or promote products derived from this software
*	   without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/

/**
 * @file main.c
 * @author CMIOT Firmware Team
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2020, CMIOT. All rights reserved.
 */

#include "main.h"
#include "log.h"
#include <stdio.h>
#include "rtthread.h"

/* Global Variable */
rt_thread_t thread1 = NULL, thread2 = NULL;
rt_mutex_t mutex1;
float float_func(float r,float h)
{
	volatile float v = 0;
	v = r*r*3.1416*h;
	v = v/h;
	return v;
}
void thread1_entry(void *paramters)
{
	volatile float V = 0 , C= 0, r = 1.0, h=1;
	volatile float a = 1 , b= 1, c = 1, d=1;
	uint32_t res=0;
	rt_thread_mdelay(1);

	while(1)
	{
		V = float_func(r,h);
		V = float_func(r+1,h);
		V = V+a+b+c+d;
		res = V*1000;
        if( res != 54265)
			printf("res: %d, V1= %f\n",res,V);
        else
        	printf("res: %d, V1= %f\n",res,V);
	}
}
void thread2_entry(void *paramters)
{
	volatile float V = 0 , C= 0, r = 2.0, h=2, fac=2;
	volatile float a = 2 , b= 2, c = 2, d=2;

	while(1)
	{
		V = float_func(r,h);
		V = V+a+b+c+d;
	//	rt_mutex_take(mutex1, RT_WAITING_FOREVER);
	//	printf("C2: %f, V2= %f\n",C,V);
	//	rt_mutex_release(mutex1);
	}
}
/** @addtogroup CM32M4XXR_StdPeriph_Examples
 * @{
 */

/** @addtogroup USART_Printf
 * @{
 */

/**
 * @brief Main function
 */
int main(void)
{
	log_init();

    /* Output a message on Hyperterminal using printf function */
    printf("CM32M4XXR RT Thread sample\r\n");
    mutex1 = rt_mutex_create("mutex", RT_IPC_FLAG_PRIO);
	thread1 = rt_thread_create("thread1",thread1_entry, NULL, 1024, 11, 1);
	if(thread1 != NULL)
	{
		rt_thread_startup(thread1);
	}
	else
	{
		printf("\r\n create thread1 failed\r\n");
	}

	thread2 = rt_thread_create("thread2",thread2_entry, NULL, 1024, 11, 1);
	if(thread2 != NULL)
	{
		rt_thread_startup(thread2);
	}
	else
	{
		printf("\r\n create thread2 failed\r\n");
	}
    while (1)
    {
    	rt_thread_mdelay(1000);
        //printf("main thread\r\n");
    }

}
/**
 * @}
 */

/**
 * @}
 */
