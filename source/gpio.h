/*
 * gpio.h
 *
 *  Created on: Dec 1, 2021
 *      Author: ajsan
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
void INIT_GPIO(void);

/*
 * @function: PORTD_IRQHandler()
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
void PORTD_IRQHandler();

int button_status(void);

void button_StatusReset(int);

#endif /* GPIO_H_ */
