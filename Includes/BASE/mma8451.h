#ifndef MMA8451_H_
#define MMA8451_H_

#include "main.h"

#define MMA8451_I2C_ADDRESS (0x1d<<1)
#define I2C0_B  I2C0_BASE_PTR

extern int16_t resultx, resulty, resultz;

/********************************************************************/
/*description: this function initializes the I2C used for acc sensor*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void hal_dev_mma8451_init(void); //prepare I2C port

/********************************************************************/
/*description: this function reads the data to acc sensor reg      */
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
uint8_t   hal_dev_mma8451_read_reg(uint8_t addr);

/********************************************************************/
/*description: this function writes the data to acc sensor reg      */
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void hal_dev_mma8451_write_reg(uint8_t addr, uint8_t data);

/********************************************************************/
/*description: this function initializes the acc sensor				*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void accel_init(void);

/********************************************************************/
/*description: this function reads the x,y,z value from acc sensor*/
/*parameter: void				 								    */
/*return:    void								                    */
/********************************************************************/
void accel_read(void);


#endif /* MMA8451_H_ */
