/*
 * systick.h
 *
 *  Created on: Dec 1, 2021
 *      Author: ajsan
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

//Header files
#include <MKL25Z4.H>
#include <stdint.h>
#include <stdio.h>


typedef uint32_t ticktime_t;


/*
 * Initializes the SysTimer to generate an interrupt for every 62.5ms
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void INIT_SysTick(void);


/*
 * Increments the tick counters
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
void SysTick_Handler();


/*
 * function: now()
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	return the number of ticks since system startup
 *
 */
extern ticktime_t now(void);

/*
 * function: reset_timer()
 * reset ticks to zero, without affecting now()
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void reset_timer(void);

/*
 * function: get_timer()
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	returns the ticks since last reset
 *
 */
extern ticktime_t get_timer(void);

#endif /* SYSTICK_H_ */
