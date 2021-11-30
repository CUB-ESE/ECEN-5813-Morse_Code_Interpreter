 
/**
 * @file    MorseCodeInterpreter.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"


#include "cbuffer.h"
#include "uart.h"

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

   	 //Initializing the UART0 with baud rate 38400, Data size 8, Parity None and  2 Stop bits
	InitUart();

	printf("\n\rWelcome to Morse code Interpreter!\n\r");

    while(1) {

        __asm volatile ("nop");
    }
    return 0 ;
}
