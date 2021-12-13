/*
 *  @file		: systick.c
 *
 *  @description: includes the APIs required for timing control
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */

#include "systick.h"

//Global variable to store the tick counts
ticktime_t currentTime;
ticktime_t resetTime;

//Refer the header file for the function documentations

void INIT_SysTick(void)
{

		SysTick->LOAD = (48000000L/16);				//counter value
		NVIC_SetPriority(SysTick_IRQn,3);			//Setting Interrupt prioriy
		SysTick->VAL = 0;							//force loading the reload value to be zero initially
		SysTick->CTRL=  SysTick_CTRL_CLKSOURCE_Msk  //selecting 48MHz clock source
						| SysTick_CTRL_TICKINT_Msk 	//Enable Interrupts
						| SysTick_CTRL_ENABLE_Msk ;	//Enable the SysTick Timer

}

/*
 * Increments the tick counters
 */
void SysTick_Handler()
{
		currentTime++;		//increments the tick counter in ISR
		resetTime++;
}

ticktime_t now(void)
{

		return currentTime;	//return the number of ticks since system startup
}

void reset_timer()
{
		resetTime=0;		//reset ticks to zero, without affecting now()
}

ticktime_t get_timer()
{
		return resetTime;	//returns the ticks since last reset
}
