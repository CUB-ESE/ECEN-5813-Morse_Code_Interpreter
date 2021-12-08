/*
 * test_interpreter.c
 *
 *  Created on: Dec 7, 2021
 *      Author: ajsan
 */

#include "test_interpreter.h"
#include "uCUnit.h"

static char *MorseCode[]= {
						"dD\n","Dddd\n","DdDd\n","Ddd\n","d\n","ddDd\n","DDd\n","dddd\n","dd\n","dDDD\n",
						"DdD\n","dDdd\n","DD\n","Dd\n","DDD\n","dDDd\n","DDdD\n","dDd\n","ddd\n","D\n",
						"ddD\n","dddD\n","dDD\n","DddD\n","DdDD\n","DDdd\n","dDDDD\n","ddDDD\n","dddDD\n",
						"ddddD\n","ddddd\n","Ddddd\n","DDddd\n","DDDdd\n","DDDDd\n","DDDDD\n"};

static char Character[] = {
						'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
						'U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9','0'};



void MorseCodeIntUnitTest(void) {

	char TTC_output;
	char *CTC_output;
	UCUNIT_Init();

	int length = sizeof(MorseCode)/sizeof(MorseCode[0]);


	UCUNIT_TestcaseBegin("TapToChar");
	for(int i=0;i<length;i++){
		TTC_output = TapToChar(MorseCode[i]);
		printf("\n\rOutput| Expected : %c Actual: %c\n\r",Character[i],TTC_output);
		UCUNIT_CheckIsEqual(TTC_output,Character[i]);
	}
	UCUNIT_TestcaseEnd();


	UCUNIT_TestcaseBegin("CharToMcode");
	for(int j=0;j<length;j++){
		CTC_output = CharToMcode(Character[j]);
		printf("\n\rOutput:\n\rExpected: %s \rActual  : %s\r",MorseCode[j],CTC_output);
		UCUNIT_CheckIsEqual(CTC_output,MorseCode[j]);
	}
	UCUNIT_TestcaseEnd();



	/* finish all the tests */
	UCUNIT_WriteSummary();
//	UCUNIT_Shutdown();
}
