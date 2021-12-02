 
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
#include "gpio.h"
#include "systick.h"

void delay(void){
	int t = now();
	while((now()-t)<2);
}

int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

   	 //Initializing the UART0 with baud rate 38400, Data size 8, Parity None and  2 Stop bits
    INIT_SysTick();
    InitUart();
	INIT_GPIO();

	printf("\n\rWelcome to the Morse code Interpreter!\n\r");

	int duration;
    while(1) {

    	//printf("%X\n\r", PTD->PDIR);

    	if(button_status()==1){
    		reset_timer();
    		button_StatusReset(0);
    		delay();
    		if(PTD->PDIR == 0x40){
    			button_StatusReset(0);

    		}else{


				while(button_status()!=1);
				duration = get_timer();
				if(duration<=5)
					printf(". ");
				else if(duration>5 && duration<=14)
					printf("- ");
				else
					printf("\n\rInvalid Input\n\r");

				button_StatusReset(0);
    		}

    	}

//    	if(button_status() == 1)
//    		printf("ON\n\r");
//    	if(button_status() == 0)
//    		printf("OFF\n\r");

    }
    return 0 ;
}
