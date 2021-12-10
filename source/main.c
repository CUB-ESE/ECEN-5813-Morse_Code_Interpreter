/*
 * main.c
 *
 *  Created on: Dec 7, 2021
 *      Author: ajsan
 */

#include "MorseCodeInterpreter.h"
#include "test_interpreter.h"

#include "cbuffer.h"
#include "uart.h"
#include "gpio.h"
#include "systick.h"
#include "led.h"
#include "tpm.h"

int main()
{

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    Init_MorseCodeInterpreter();

//    printf("\n\rMorsecode Interpreter uCUnit tests.\n\r");
//    MorseCodeIntUnitTest();
	printf("\n\rWelcome to the Morse code Interpreter!\n\r");

	int duration;
	int valid=0;
	uart_input();

    while(1) {
    	valid=1;
    	//printf("%X\n\r", PTD->PDIR);

    	if(button_status()==1){

    		disable_uart();

    		reset_timer();
    		button_StatusReset(0);
    		delay();
    		if(PTD->PDIR == 0x40){
    			button_StatusReset(0);

    		}else{

    			greenLedOn();//
    			RGB_LED_ON(GREEN);
				while(button_status()!=1);
				LedOff();
				duration = get_timer();
				if(duration<=5){
					//greenLedOff();//
	    			//redLedOn();//

					//printf(". ");
					cbuffer_enqueue(&mcode,'d');
					delay();
					RGB_LED_ON(RED);
	    			delay();
	    			LedOff();

				}
				else if(duration>5 && duration<=14){
					//greenLedOff();//
	    			//blueLedOn();//
	    			delay();
					RGB_LED_ON(BLUE);
	    			delay();
	    			LedOff();
					//printf("- ");
					cbuffer_enqueue(&mcode,'D');

				}
				else{
					printf("\n\rInvalid Input\n\r");
	    			valid=0;
					delay();
					RGB_LED_ON(PURPLE);
	    			delay();
	    			LedOff();
				}
				button_StatusReset(0);

    		}

        	duration=now();
        	while((now()-duration)<=8 && button_status() != 1 && valid==1);
        	if((now()-duration)>8){
    			delay();
				RGB_LED_ON(YELLOW);
    			delay();
    			LedOff();
        		//printf("\n\rEnd of Character\n\r");
        		NVIC_DisableIRQ(PORTD_IRQn);

        		cbuffer_enqueue(&mcode,'|');
        		char data = cbuffer_dequeue(&mcode);
        		char TapCode[100];
        		int i;
        		for(i=0; data != '|'; i++){
        			TapCode[i]=data;
        			data = cbuffer_dequeue(&mcode);
        		}
        		TapCode[i]='\n';
        		//printf("%s\n\r",TapCode);
        		printf("%c\n\r",TapToChar(TapCode));
        		NVIC_EnableIRQ(PORTD_IRQn);

        	}

        	enable_uart();

    	}//if button_pressed

    	//uart
    	if (uart_input() ==1){
    		disable_gpio();
    		uint8_t data;
    		data=getchar();
    		printf("%c",data);
    		while(data != 0x0d){
    			cbuffer_enqueue(&mcode,data);

    			data=getchar();
    			printf("%c",data);
    		}

    		printf("\n\r");
    		cbuffer_enqueue(&mcode,'|');
    		//uint8_t data;
    		data = cbuffer_dequeue(&mcode);
    		while(data != '|'){
    			CharToMcode(data);
    			data=cbuffer_dequeue(&mcode);
    		}

    		uart_input();

    		enable_gpio();
    		button_StatusReset(0);
    	}//if UART Rx




    }//while
    return 0 ;
}
