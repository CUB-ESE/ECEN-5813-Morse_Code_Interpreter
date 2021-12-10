 
/**
 * @file    MorseCodeInterpreter.c
 * @brief   Application entry point.
 */

#include "MorseCodeInterpreter.h"
#include "cbuffer.h"
#include "uart.h"
#include "gpio.h"
#include "systick.h"
#include "led.h"
#include "tpm.h"


cbuffer mcode;


typedef struct{
	char *Mcode;
	char character;
}Mcode;


static Mcode MorseCode[]={
		{"dD\n",'A'},{"Dddd\n",'B'},{"DdDd\n",'C'},{"Ddd\n",'D'},{"d\n",'E'},{"ddDd\n",'F'},{"DDd\n",'G'},{"dddd\n",'H'},{"dd\n",'I'},
		{"dDDD\n",'J'},{"DdD\n",'K'},{"dDdd\n",'L'},{"DD\n",'M'},{"Dd\n",'N'},{"DDD\n",'O'},{"dDDd\n",'P'},{"DDdD\n",'Q'},{"dDd\n",'R'},
		{"ddd\n",'S'},{"D\n",'T'},{"ddD\n",'U'},{"dddD\n",'V'},{"dDD\n",'W'},{"DddD\n",'X'},{"DdDD\n",'Y'},{"DDdd\n",'Z'},{"dDDDD\n",'1'},
		{"ddDDD\n",'2'},{"dddDD\n",'3'},{"ddddD\n",'4'},{"ddddd\n",'5'},{"Ddddd\n",'6'},{"DDddd\n",'7'},{"DDDdd\n",'8'},{"DDDDd\n",'9'},
		{"DDDDD\n",'0'}
};

const int NCodes = sizeof(MorseCode)/sizeof(MorseCode[0]);

void delay(void){
	int t = now();
	while((now()-t)<2);
}

char* CharToMcode(char data)
{
	//NVIC_DisableIRQ(UART0_IRQn);

	uint8_t CnvFlag;
	char *output;
	CnvFlag=1;
	//data = cbuffer_dequeue(&mcode);
	//while(data!='|'){

		for(int i=0;i<NCodes;i++){
			if(data == MorseCode[i].character){
				output=MorseCode[i].Mcode;
				for(int j=0;MorseCode[i].Mcode[j] != '\n';j++){
					if(MorseCode[i].Mcode[j] == 'd'){
						delay();
						RGB_LED_ON(RED);
						delay();
						LedOff();
					}else{
						delay();
						RGB_LED_ON(GREEN);
						delay();
						LedOff();
					}

				}
				delay();
				RGB_LED_ON(BLUE);
				delay();
				LedOff();
				CnvFlag=0;
				//return 0;

			}
		}

		//data = cbuffer_dequeue(&mcode);
	//}

	if(CnvFlag)
		printf("\n\rInvalid Input\n\r");

	return output;
	//NVIC_EnableIRQ(UART0_IRQn);

}

char TapToChar(char* TapCode)
{
	//NVIC_DisableIRQ(PORTD_IRQn);

	int q=0;
	int j=0;
	for(int i=0; i<NCodes; i++){
		q=0;
		//if(strcmp(TapCode,MorseCode[i].Mcode) == 0)
			for(j=0; ((*(TapCode+j)!='\n'));j++){
				if((*(TapCode+j))==(*(MorseCode[i].Mcode + j)))
					continue;
				else{
					q=1;
					break;
				}
			}
			if((*(MorseCode[i].Mcode + j)=='\n') && (q==0)){
				//printf("%c\n\r",MorseCode[i].character);
				return MorseCode[i].character;
			}
	}

	//NVIC_EnableIRQ(PORTD_IRQn);
	return 0;
}

void Init_MorseCodeInterpreter(void)
{
    INIT_SysTick();
    InitUart();
	INIT_GPIO();
	ledInit();
	INIT_RGB_LED_PWM();
}

int MorseCodeInterpreter(void) {

   	 //Initializing the UART0 with baud rate 38400, Data size 8, Parity None and  2 Stop bits
//    INIT_SysTick();
//    InitUart();
//	INIT_GPIO();
//	ledInit();
//	INIT_RGB_LED_PWM();
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
