/*
 * logger.h
 *
 *  Created on: Oct 30, 2016
 *      Author: vikhyat
 */

#ifndef INCLUDES_HSW_LOGGER_H_
#define INCLUDES_HSW_LOGGER_H_

/********************************************************************/
/*description: this function prints a string on terminal over uart  */
/*parameter: string to be print 								    */
/*return:    void								                    */
/********************************************************************/
void LOG_0(uint8_t * data);

/********************************************************************/
/*description: this function prints a string						*/
/*				followed by a integer value on terminal				*/
/*parameter: string to be print and the integer value to be appended*/
/*return:    void								                    */
/********************************************************************/
void LOG_1(uint8_t * data, uint32_t  param);

/********************************************************************/
/*description: this function prints a string
				followed by a float value on terminal
/*parameter: string to be print and the float value to be appended  */
/*return:    void								                    */
/********************************************************************/
void LOG_2(uint8_t * data, float param);

/********************************************************************/
/*description: this function returns the cursor to home on terminal
/*parameter: void										            */
/*return:    void								                    */
/********************************************************************/
void LOG_return(void);

/********************************************************************/
/*description: This function converts integer to ascii
/*parameter: void										            */
/*return:    unit8_t 0 = failed 1 = success                         */
/********************************************************************/
int8_t itoa(int8_t *str, int32_t data, int32_t base);

/********************************************************************/
/*description: This function converts ascii to integer
/*parameter: void										            */
/*return:    unit8_t 0 = failed 1 = success                         */
/********************************************************************/
uint8_t myAtoi(uint8_t *str);

/********************************************************************/
/*description: This function converts the float value into ascii
/*parameter: void										            */
/*return:    char 0 = failed 1 = success                            */
/********************************************************************/
char *ftoa(float f);

#endif /* INCLUDES_HSW_LOGGER_H_ */
