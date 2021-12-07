/*
 * tpm.h
 *
 *  Created on: Dec 6, 2021
 *      Author: ajsan
 */

#ifndef TPM_H_
#define TPM_H_

//Header files
#include "MKL25Z4.h"
#include "led.h"
#include <MKL25Z4.h>
#include <stdio.h>

#define PWM_PERIOD (255)	//PWM period (step size)


/*
 * Initializes the TSI register to work in poll-in mode
 *
 * Parameters:
 * 	None
 *
 * Returns:
 * 	None
 *
 */
extern void INIT_RGB_LED_PWM(void);


#endif /* TPM_H_ */
