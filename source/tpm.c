/*
 * tpm.c
 *
 *  Created on: Dec 6, 2021
 *      Author: ajsan
 */


#include "TPM.h"

//Refer the header file for function documentation

void INIT_RGB_LED_PWM(void)
{

	// Configure TPM
	SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_TPM2_MASK;

	//set clock source for tpm: 48 MHz
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);

	//load the counter and mod
	TPM0->MOD = PWM_PERIOD-1;
	TPM2->MOD = PWM_PERIOD-1;

	//set TPM count direction to up with a divide by 128 prescaler
	TPM0->SC =  TPM_SC_PS(7);
	TPM2->SC =  TPM_SC_PS(7);
	TPM0->SC = (TPM_SC_CPWMS(0));
	TPM2->SC = (TPM_SC_CPWMS(0));

	// Continue operation in debug mode
	TPM0->CONF |= TPM_CONF_DBGMODE(3);
	TPM2->CONF |= TPM_CONF_DBGMODE(3);

	// Set channel 1 to edge-aligned low-true PWM
	TPM0->CONTROLS[1].CnSC =TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[0].CnSC =TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	TPM2->CONTROLS[1].CnSC =TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;


	// Set initial duty cycle
	TPM0->CONTROLS[1].CnV = 0;
	TPM2->CONTROLS[0].CnV = 0;
	TPM2->CONTROLS[1].CnV = 0;


	// Start TPM
	TPM0->SC |= TPM_SC_CMOD(1);
	TPM2->SC |= TPM_SC_CMOD(1);
}
