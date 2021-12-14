/*
 *  @file		: main.c
 *
 *  @description: implements the Morse code interpreter sequence and executes the both way conversions
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */


//Headers
#include "MorseCodeInterpreter.h"
#include "test_interpreter.h"
#include "cbuffer.h"
#include "uart.h"
#include "gpio.h"
#include "systick.h"
#include "led.h"
#include "tpm.h"

#define ENTER_KEY  (0x0d)
#define BACK_SPACE (0x7F)

int main()
{

  	/* Init board hardware. */

j	BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

    Init_MorseCodeInterpreter();
#ifdef DEBUG
    printf("\n\rMorsecode Interpreter uCUnit tests.\n\r");
    MorseCodeIntUnitTest();
#endif

    Boot_Sequence();

	printf("\n\rWelcome to the Morse code Interpreter!\n\r");

	int duration;
	int valid=0;
	uart_input();

    while(1) {
    	valid=1;

    	//If push botton input is detected
    	if(button_status()==1){

    		disable_uart();				//disable UART till the read from button ends
    		reset_timer();
    		button_StatusReset(0);
    		delay();					//delay to avoid switch debouncing

    		if(PTD->PDIR == 0x40)		//checks again for the valid input
    			button_StatusReset(0);	//resets the button press status

    		else{
    			//measure the tap duartion
    			RGB_LED_ON(GREEN);
				while(button_status()!=1);
				LedOff();
				duration = get_timer();

				//recognize the DOT
				if(duration<=5){
					cbuffer_enqueue(&mcode,'d');
					delay();
					RGB_LED_ON(RED);
	    			delay();
	    			LedOff();

				}
				//recognize the DASH
				else if(duration>5 && duration<=14){
	    			delay();
					RGB_LED_ON(BLUE);
	    			delay();
	    			LedOff();
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

    		//waits for the next tap or to consider for end of the character input
        	duration=now();
        	while((now()-duration)<=8 && button_status() != 1 && valid==1);

        	//If end of character detected
        	if((now()-duration)>8){
    			delay();
				RGB_LED_ON(YELLOW);
    			delay();
    			LedOff();
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
        		char character = TapToChar(TapCode);
        		if(character == 0 )
        			printf("Invalid Input\n\r");
        		else
        			printf("Character detected: %c\n\r",TapToChar(TapCode));
        		NVIC_EnableIRQ(PORTD_IRQn);
        	}

        	enable_uart();								//enable UART back

    	}//if button_pressed

    	//If input is detected from the UART terminla
    	if (uart_input() ==1){
    		disable_gpio();								//disable GPIO
    		uint8_t data;
    		data=getchar();
    		printf("UART Input: %c",data);
    		while(data != ENTER_KEY){
    			if(data == BACK_SPACE)
    				cbuffer_dequeue(&mcode);
    			else
    				cbuffer_enqueue(&mcode,data);
    			delay();
    			data=getchar();
    			printf("%c",data);
    		}
    		printf("\n\r");
    		cbuffer_enqueue(&mcode,'|');

    		//Conversion to Morse code
    		data = cbuffer_dequeue(&mcode);
    		while(data != '|'){
    			if(CharToMcode(data) == NULL)
    				printf("Invalid Input\n\r");
    			data=cbuffer_dequeue(&mcode);
    		}

    		uart_input();
    		enable_gpio();									//Enable GPIO and reset all status values to 0;
    		button_StatusReset(0);
    	}//if UART Rx

    }//while
    return 0 ;
}
