/*
 * led.h
 *
 *  Created on: Dec 1, 2021
 *      Author: ajsan
 */

#ifndef LED_H_
#define LED_H_

/*
 * Initializes the RGB led by setting associated ports as GPIO and direction
 */
extern void ledInit();

/*
 * Function to turn on red led
 */
extern void redLedOn();

/*
 * Function to turn off red led
 */
extern void redLedOff();

/*
 * Function to turn on green led
 */
extern void greenLedOn();

/*
 * Function to turn off green led
 */
extern void greenLedOff();

/*
 * Function to turn on blue led
 */
extern void blueLedOn();

/*
 * Function to turn off blue led
 */
extern void blueLedOff();

/*
 * Function to turn on white led
 */
extern void whiteLedOn();

/*
 * Function to turn off white led
 */
extern void LedOff();


extern void RGB_LED_ON(uint32_t color);

#endif /* LED_H_ */
