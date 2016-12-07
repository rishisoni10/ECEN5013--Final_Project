/*
 * nvic.c
 *
 *  Created on: Oct 30, 2016
 *      Author: VIKHYAT
 */

#include "main.h"

uint8_t packet_byte, rx_byte =0;

void UART0_IRQHandler (void)
{
  if (UART0_S1&UART_S1_RDRF_MASK)
  	{
	  	packet_byte = UART0_D;
	  	UART0_D = packet_byte;
		UART0_C2 &= ~UART0_C2_RIE_MASK; 		//Peripheral interrupt disable (RX)
		rx_byte = 1;
  	}

  if ((UART0_S1&UART_S1_TDRE_MASK)||(UART0_S1&UART_S1_TC_MASK))
    {

    }
}


void RTC_Seconds_IRQHandler(void){

	onesecond = 1;
	seconds = RTC_TSR;
	if (seconds >59){
		minutes++;
		RTC_SR &= ~RTC_SR_TCE_MASK;
		RTC_TSR = 0x00; //Reset counter
		seconds = RTC_TSR;
		RTC_SR |= RTC_SR_TCE_MASK;
		int alarmTime = RTC_TAR;
		RTC_TAR = alarmTime - 60;
	}
	if(minutes > 59){
		hours++;
		minutes =0;
	}
}


void RTC_IRQHandler(void){

	RTC_TAR = totalAlarmSeconds;
}


