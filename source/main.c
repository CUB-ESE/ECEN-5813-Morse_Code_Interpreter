/*
 * main.c
 *
 *  Created on: Dec 7, 2021
 *      Author: ajsan
 */

#include "MorseCodeInterpreter.h"
#include "test_interpreter.h"

int main()
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    Init_MorseCodeInterpreter();

//    printf("\n\rMorsecode Interpreter uCUnit tests.\n\r");
//    MorseCodeIntUnitTest();

    MorseCodeInterpreter();

	return 0;
}
