/*
 *  @file		: tpm.h
 *
 *  @description: includes the APIs required to initialize TPM2 and TPM0
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
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
 * Initializes the RGB led to PWM mode using TPM2 and TPM0
 *
 * Parameters:
 * 		None
 *
 * Returns:
 * 		None
 *
 */
extern void INIT_RGB_LED_PWM(void);


#endif /* TPM_H_ */
