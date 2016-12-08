/*
 * profile.c
 *
 *  Created on: 12-Oct-2016
 *      Author: Vikhyat
 */

#include "main.h"

static uint32_t count = 0;
volatile uint32_t traveltimer = 0;

void TaskTimer_init()
{
	//Step 1: Clock config
    MCG_C1 |= MCG_C1_IREFS_MASK | MCG_C1_IRCLKEN_MASK;		// Internal Clock and Enable it(MCGIRCLK)
    MCG_C2 |= MCG_C2_IRCS_MASK;								// Fast internal clock mode

	// Enable TPM clock
	SIM_SCGC6 |= SIM_SCGC6_TPM1_MASK;
    SIM_SOPT2 |= SIM_SOPT2_TPMSRC(3);						// MCGIRCLK as timer source clock
    SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK; // Clock gate enable for Port B and D

	//Nullify the control registers to ensure counter is not running

	TPM1_SC = 0;
	TPM1_CONF = 0;

	//Set prescalar to 1 when counter is disabled
	TPM1_SC = TPM_SC_PS(0);

	//Enable Interrupts for the Timer Overflow
	TPM1_SC |= TPM_SC_TOIE_MASK;

	// Setting modulo value to set 10us as the execution timer
	TPM1_MOD = 40;

	//Enable the TPM COunter
	TPM1_SC |= TPM_SC_CMOD(1);

	//NVIC_ClearPendingIRQ(TPM0_IRQn);
	NVIC_EnableIRQ(TPM1_IRQn);
	//enable_irq(INT_TPM0 - 16);

	count = 0;
}

void stop_TaskTimer()
{
	NVIC_DisableIRQ(TPM1_IRQn);
	//Disabling the counter
	TPM1_SC = 0;
	TPM1_CONF = 0;
}

void TPM1_IRQHandler()
{
	if(TPM1_SC & TPM_SC_TOF_MASK)
	{
		TPM1_SC |= TPM_SC_TOF_MASK;
		count++;
		traveltimer++;

	   if((count % 8) == 0){
				midtask_trig = 0;
			    fasttask_trig = 0;
				slowtask_trig = 1;
		}
	   else if((count % 4) == 0){
			midtask_trig = 1;
		    fasttask_trig = 0;
			slowtask_trig = 0;
		}
	   else {
		    fasttask_trig = 1;
		    midtask_trig = 0;
		    slowtask_trig = 0;
	   }

		if (count == 15){
			count = 0;
		}
	}
}

