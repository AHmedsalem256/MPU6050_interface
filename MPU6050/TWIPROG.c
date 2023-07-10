
/*

Driver to implement TWI protocol ;

Author : AHMED SALEM;

DATE : 26/6/2023


*/

#include"BIT_MATH.h"
#include"STD_TYPES.h"
#include"TWI.h"
#include<avr/delay.h>
#include<avr/io.h>

#define F_CPU 8000000


/*
 *
 * Function to intialize the I2c module
 *
 * */



void TWI_init(const TWI_ConfigType * Config_Ptr )
{
	u8 TWBR_value;
	TWCR = (1<<TWEN);
	TWAR = Config_Ptr->address;
	TWSR = 0x00; /* assuming it is equal to 0 always and get TWBR based on that assumption */
	TWBR = (u8)(((F_CPU/((Config_Ptr->bit_rate)*1000))-16) /2);

}

void TWI_start()
{
	TWCR = (1<<2) | (1<<7) | (1<<5);

	while( BIT_IS_CLEAR(TWCR,7) ){}


}

void TWI_stop()
{
	/*
	 *  Enable TWI
	 * clear TWI INT flag
	 * send stop condtion
	 * */

	TWCR = (1<<2) | (1<<7) | (1<<4);

	while(TWCR & (1<<TWSTO));
}

void TWI_writeByte(u8 byte)
{
	/* Load data on data register
	 * enable TWI
	 * clear INT flag
	 * check for error in INT flag
	 * */

	TWDR = byte;

	TWCR = (1<<2) | (1<<7) ;

	while(BIT_IS_CLEAR(TWCR,7)){}

}

u8 TWI_readByteWithACK(void)
{
	/* enable TWI
	 * clear INT flag
	 * send Ack_Bit
	 * check for error
	 * return data
	 * */

	TWCR = (1<<2)|(1<<7)|(1<<6);

	while(BIT_IS_CLEAR(TWCR,7)){}

	return TWDR;

}


u8 TWI_readByteWithNACK(void)
{
	/* enable TWI
	 * clear INT flag
	 * check for error
	 * return data
	 * */

	TWCR = (1<<2)|(1<<7);

	while(BIT_IS_CLEAR(TWCR,7)){}

	return TWDR;


}






u8 TWI_getStatus(void)
{
	u8 status ;

	status = TWSR & 0xF8;

	return status;
}
