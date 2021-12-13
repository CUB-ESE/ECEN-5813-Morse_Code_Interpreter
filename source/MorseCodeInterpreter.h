/*
 *  @file		: MorseCodeInterpreter.h
 *
 *  @description: includes the APIs required for the Morse code interpreter
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */

#ifndef MORSECODEINTERPRETER_H_
#define MORSECODEINTERPRETER_H_

//Standrard Headers
#include <stdio.h>
#include <string.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"

#include "cbuffer.h"
#include "uart.h"
#include "gpio.h"
#include "systick.h"
#include "led.h"
#include "tpm.h"

//Definition for color codes for RGB LED
#define RED		(0x00FF0000)
#define GREEN	(0x0000FF00)
#define BLUE	(0x000000FF)
#define YELLOW  (0x00FFFF00)
#define PURPLE  (0x00800080)

//Circular buffer to store Morse code input
extern cbuffer mcode;

/*
 * @function: delay()
 *
 * @description: provides a delay of two ticks from systick API
 *
 * Parameter
 * 		None
 *
 * Returns
 * 		None
 */
extern void delay(void);

/*
 * @function: CharToMcode()
 *
 * @description: converts character to morse code and displays using RGB LED
 *
 * Parameter
 * 		Character to be converted to Morse code
 *
 * Returns
 * 		Returns the Morse code of the respective character
 */
extern char* CharToMcode(char);

/*
 * @function: TapToChar()
 *
 * @description: Converts the Morse code input into corresponding character and
 * 				 displays on the UART terminal
 *
 * Parameter
 * 		TapCode <- More code input from the push button
 *
 * Returns
 * 		Returns the corresponding character
 */
extern char TapToChar(char* TapCode);

/*
 * @function: Init_MorseCodeINterpreter()
 *
 * @description: Initializes all the required modules to start Morse Code Interpreter
 *
 * Parameter
 * 		None
 *
 * Returns
 * 		None
 */
extern void Init_MorseCodeInterpreter(void);

/*
 * @function: Boot_Sequence()
 *
 * @description: Displays the Morse Code from A-F using RGB LED
 *
 * Parameter
 * 		None
 *
 * Returns
 * 		None
 */
extern void Boot_Sequence(void);

#endif /* MORSECODEINTERPRETER_H_ */
