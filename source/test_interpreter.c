/*
 *  @file		: test_interpreter.c
 *
 *  @description: includes the APIs required for executing the test suite of Morse code interpreter
 *
 *  Created on	: December 1, 2021
 *  Author    	: Santhosh, santhosh@colorado.edu
 */


#include "test_interpreter.h"
#include "uCUnit.h"
#include "assert.h"
#include "stdio.h"

//Lookup table to test the conversion modules from MorseCodeInterpreter
static char *MorseCode[]= {
						"dD\n","Dddd\n","DdDd\n","Ddd\n","d\n","ddDd\n","DDd\n","dddd\n","dd\n","dDDD\n",
						"DdD\n","dDdd\n","DD\n","Dd\n","DDD\n","dDDd\n","DDdD\n","dDd\n","ddd\n","D\n",
						"ddD\n","dddD\n","dDD\n","DddD\n","DdDD\n","DDdd\n","dDDDD\n","ddDDD\n","dddDD\n",
						"ddddD\n","ddddd\n","Ddddd\n","DDddd\n","DDDdd\n","DDDDd\n","DDDDD\n"};

//Array of valid inputs to be tested by uCUnit
static char Character[] = {
						'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T',
						'U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9','0'};

//Refer the header file for function documentation

void MorseCodeIntUnitTest(void)
{
	char TTC_output;
	char *CTC_output;

	//Invalid input test cases
	assert(CharToMcode('*') == NULL);
	assert(CharToMcode('@') == NULL);
	assert(CharToMcode('$') == NULL);
	assert(CharToMcode('+') == NULL);
	assert(CharToMcode('~') == NULL);
	assert(CharToMcode('.') == NULL);
	assert(CharToMcode(',') == NULL);
	assert(CharToMcode('}') == NULL);
	assert(CharToMcode('<') == NULL);

	//Check for lower case input
	assert(CharToMcode('a') == MorseCode[0]);
	assert(CharToMcode('b') == MorseCode[1]);
	assert(CharToMcode('c') == MorseCode[2]);
	assert(CharToMcode('d') == MorseCode[3]);
	assert(CharToMcode('e') == MorseCode[4]);
	assert(CharToMcode('f') == MorseCode[5]);

	//Check for Invalid inputs from TapToChar
	assert(TapToChar("DDDDDD\n") == 0);
	assert(TapToChar("\n") == 0);
	assert(TapToChar("DddddD\n") == 0);
	assert(TapToChar("DDddddd\n") == 0);
	assert(TapToChar("DDDdddDD\n") == 0);
	assert(TapToChar("dddddDDDddddD\n") == 0);
	assert(TapToChar(" ") == 0);

	//Unit testing
	UCUNIT_Init();

	//size of the lookup test table
	int length = sizeof(MorseCode)/sizeof(MorseCode[0]);

	//Unit test for the function TapToChar
	UCUNIT_TestcaseBegin("TapToChar");
	for(int i=0;i<length;i++){
		TTC_output = TapToChar(MorseCode[i]);
		printf("\n\rOutput| Expected : %c Actual: %c\n\r",Character[i],TTC_output);
		UCUNIT_CheckIsEqual(TTC_output,Character[i]);
	}
	UCUNIT_TestcaseEnd();

	//Unit test for the function CharToMcode
	UCUNIT_TestcaseBegin("CharToMcode");
	for(int j=0;j<length;j++){
		CTC_output = CharToMcode(Character[j]);
		printf("\n\rOutput:\n\rExpected: %s \rActual  : %s\r",MorseCode[j],CTC_output);
		UCUNIT_CheckIsEqual(CTC_output,MorseCode[j]);
	}
	UCUNIT_TestcaseEnd();



	//finish all the tests and prints tehe summary of the unit tests
	UCUNIT_WriteSummary();

}
