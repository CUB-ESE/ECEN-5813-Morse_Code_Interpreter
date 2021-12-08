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

char* CharToMcode(char);

char TapToChar(char* TapCode);

int MorseCodeInterpreter(void);

void Init_MorseCodeInterpreter(void);


#endif /* MORSECODEINTERPRETER_H_ */
