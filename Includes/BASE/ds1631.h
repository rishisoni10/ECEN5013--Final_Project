/*
 * ds1631.h
 *
 *  Created on: 20-Nov-2016
 *      Author: Vikhyat
 */

#ifndef DS1631_H_
#define DS1631_H_

#define DS1631_SLAVE_ID 0x48
#define CMD_START_CONVERSION 0x51
#define CMD_READ_TEMP 0xAA

/********************************************************************/
/*description: this function configures external
   temperature sensor and starts continuous conversion
/*parameter: void										            */
/*return:    void						                            */
/********************************************************************/
void DS1631_Start_Continuos_Conversion (void);

/********************************************************************/
/*description: this function reads the last converted value
				over I2C from the external sensor
/*parameter: void										            */
/*return:    float value of last read temperature                   */
/********************************************************************/
float DS1631_Read_Temperature (void);


#endif
