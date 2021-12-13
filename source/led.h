/*
 *  @file		: led.h
 *
 *  @description: includes the APIs required for the RGB LED control
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */

#ifndef LED_H_
#define LED_H_

/*
 * @function: ledInit()
 *
 * Initializes RGB led's by setting clock to the port and making them as GPIO along
 * with setting their alternate function for TPM2 and/or TPM0
 *
 * Parameters:
 * 		None
 *
 * Returns:
 * 		None
 */
extern void ledInit();

/*
 * @function: LedOff()
 *
 * This function turns of the RGB led
 *
 * Parameters:
 * 		None
 *
 * Returns:
 * 		None
 */
extern void LedOff();

/*
 * @function: ledInit()
 *
 * Turns on the RGB led to given color
 *
 * Parameters:
 * 		color <- 32-bit color code
 *
 * Returns:
 * 		None
 */
extern void RGB_LED_ON(uint32_t color);

#endif /* LED_H_ */
