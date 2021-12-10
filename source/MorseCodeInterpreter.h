/*
 * MorseCodeInterpreter.h
 *
 *  Created on: Dec 7, 2021
 *      Author: ajsan
 */

#ifndef MORSECODEINTERPRETER_H_
#define MORSECODEINTERPRETER_H_

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

#define RED		(0x00FF0000)
#define GREEN	(0x0000FF00)
#define BLUE	(0x000000FF)
#define YELLOW  (0x00FFFF00)
#define PURPLE  (0x00800080)

extern cbuffer mcode;

void delay(void);

char* CharToMcode(char);

char TapToChar(char* TapCode);

void Init_MorseCodeInterpreter(void);


#endif /* MORSECODEINTERPRETER_H_ */
