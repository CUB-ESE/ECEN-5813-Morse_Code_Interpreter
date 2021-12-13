/*
 *  @file		: gpio.h
 *
 *  @description: includes the APIs required for the general purpose input/output
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "MKL25Z4.h"


/*
 * @function: INIT_GPIO()
 *
 * Initializes the GPIO ports
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void INIT_GPIO(void);

/*
 * @function: PORTD_IRQHandler()
 *
 * PORTD Interrupt Service Routine
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void PORTD_IRQHandler();

/*
 * @function: button_status()
 *
 * Returns the input GPIO button status
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	(int) buttonStatus value
 *
 */
extern int button_status(void);

/*
 * @function: button_StatusReset()
 *
 * Resets the buttonStatus value to given value
 *
 * Parameters:
 * 	(int) reset value - ideally zero
 *
 * Returns:
 * 	None
 *
 */
extern void button_StatusReset(int);

/*
 * @function: disable_gpio()
 *
 * Disables the GPIO interrupt
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void disable_gpio(void);

/*
 * @function: enable_gpio()
 *
 * Enables the GPIO interrupt
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void enable_gpio(void);

#endif /* GPIO_H_ */
