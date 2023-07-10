

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"DIO_interface.h"
#include"TWI.h"

#include<avr/delay.h>

/* Just use them in main.c file and devide them over 16384.0 */

f64 Acc_x;
f64 Acc_y;
f64 Acc_z;
f64 Temp;
f64 Gyro_x;
f64 Gyro_y;
f64 Gyro_z;

#define ERROR 0

u8 MPU6050_Init()
{

	/* ACCESS simle rate register */

	TWI_start();
	TWI_writeByte(0xD0);
	TWI_writeByte(0x19);
	TWI_writeByte(0x07); // 8KHz
	TWI_stop();

	/* ACCESS power mangment register */

	TWI_start();
	TWI_writeByte(0xD0);
	TWI_writeByte(0x6B);
	TWI_writeByte(0x01); // PLL with x AXIS
	TWI_stop();

	/* ACCESS Configration Register  */

	TWI_start();
	TWI_writeByte(0xD0);
	TWI_writeByte(0x1A);
	TWI_writeByte(0x00);  // Fs 8Hz
	TWI_stop();

	/* ACCESS Gyro Configration Register  */


	TWI_start();
	TWI_writeByte(0xD0);
	TWI_writeByte(0x1B);
	TWI_writeByte(0x18);  // Fs 8Hz
	TWI_stop();

	return 1;

}


void MPU_6050_StartLoc()
{
	TWI_start();
	TWI_writeByte(0xD0); // write write bit to ADDRESS slave
	TWI_writeByte(0x3B); // write on Get reading registers
	TWI_start(); // send repeted start condition
	TWI_writeByte(0xD1); // Read balues from register
}



void MPU_6050_Reading()
{
	MPU_6050_StartLoc();

	/*Start read the values from MPU6050 sensor registers*/

	Acc_x  = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithACK());
	Acc_y  = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithACK());
	Acc_z  = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithACK());
	Temp   = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithACK());
	Gyro_x = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithACK());
	Gyro_y = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithACK());
	Gyro_z = (((int)TWI_readByteWithACK()<<8) | (int)TWI_readByteWithNACK());  // Nack to indicate to stop reading
	TWI_stop(); // Sending the stop condition
}



