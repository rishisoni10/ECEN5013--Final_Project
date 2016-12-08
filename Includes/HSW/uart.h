/*
 * uart.h
 *
 *  Created on: Oct 30, 2016
 *      Author: Vikhyat
 */

#ifndef INCLUDES_BASE_UART_H_
#define INCLUDES_BASE_UART_H_

#include <stdint.h>

/********************************************************************/
/*description: this function initializes the UART 					*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void uart_init(uint32_t baud);

/********************************************************************/
/*description: this function is the interrupt handler for uart		*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void UART0_IRQHandler (void);

#define BAUD_RATE       38400

#endif /* INCLUDES_BASE_UART_H_ */
