#include "main.h"
uint16_t MASK = 0x8000;
float MUL = 64;

void DS1631_Start_Continuos_Conversion (void)
{
	I2C_WriteCommand(DS1631_SLAVE_ID, CMD_START_CONVERSION);
}

float convert_temp(uint16_t val){
	uint8_t i = 0, j =14;
	float tempval,result = 0;
	uint16_t temp,mask_value;

	for(i = 1 ; i < 15 ; i++){
	 mask_value = MASK >> i;
     temp = (val & mask_value);
     temp = temp >> j;
     tempval = temp*MUL;
     MUL = MUL/2;
     j--;
     result = result + tempval;
	}
	MUL = 64;
	return result;
}

float DS1631_Read_Temperature (void)
{
	uint8_t read_temp[4] = {5,5,5};
	uint16_t readvalue;
	float temp;
	I2C_ReadRegisters(DS1631_SLAVE_ID,CMD_READ_TEMP,3,read_temp);
	readvalue = ((read_temp[1] << 8) | read_temp[2]);
	temp = convert_temp(readvalue);
	return temp;
}
