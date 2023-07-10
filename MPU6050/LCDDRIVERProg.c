

/*

LCD driver based on DIO driver


RS -> 1 for data 0-> command (PORTD pin 0)
RW -> zero PORTD PIN 1

VO for POT
VSS -> GND
VDD -> POWER
D0-D7 -> PORT
E - > PORTD pin 2


*/
#include"STD_TYPES.h"
#include"BIT_MATH.h"
#include"LCDinterfaceV5.h"
#include"DIO_interface.h"




#include<avr/delay.h>



#include<avr/delay.h>

#define FUNCTION_SET    0b00111000
#define ON_OFF          0b00001111
#define DISPLAY_CLEAR   0b00000001
#define DATA_PORT 0
#define CONTROL_PORT 3

#define RS 2
#define RW 3
#define E  4


void LCD_VidIntialize()
{
	/*Set output PORT */

	DIO_VidSetPortDirection(DATA_PORT,255);

	/* configre RS RW E */

	DIO_VidSetPinDirection(CONTROL_PORT,RS,1);
	DIO_VidSetPinDirection(CONTROL_PORT,RW,1);
	DIO_VidSetPinDirection(CONTROL_PORT,E,1);


	/*Set of LCD data sheet commands*/

	_delay_ms(40);

	LCD_VidSendCommand(FUNCTION_SET);

	_delay_ms(1);

	LCD_VidSendCommand(ON_OFF);

	_delay_ms(1);

	LCD_VidSendCommand(DISPLAY_CLEAR);

	_delay_ms(2);
}

void LCD_VidSendData(u8 value)
{
	/*Set RS */

	DIO_VidSetPinValue(CONTROL_PORT,RS,1);

	/*RW*/

	DIO_VidSetPinValue(CONTROL_PORT,RW,0);

	/* Send data in ascii */

	DIO_VidSetPortValue(DATA_PORT,value);

	/* enable sequence */

	DIO_VidSetPinValue(CONTROL_PORT,E,1);

	_delay_ms(1);

	DIO_VidSetPinValue(CONTROL_PORT,E,0);

	_delay_ms(1);


}

void LCD_VidSendCommand(u8 value)
{
	/* set RS */
	DIO_VidSetPinValue(CONTROL_PORT,RS,0);

	/*RW*/

	DIO_VidSetPinValue(CONTROL_PORT,RW,0);



	DIO_VidSetPortValue(DATA_PORT,value);


	/* enable sequence */
	DIO_VidSetPinValue(CONTROL_PORT,E,1);

	_delay_ms(1);

	DIO_VidSetPinValue(CONTROL_PORT,E,0);

	_delay_ms(1);

}

void LCD_VidSendString(u8 *ptr)
{
	u8 i;

	for(i=0 ; ptr[i] != '\0' ;i++)
	{
		LCD_VidSendData(ptr[i]);

	}
}

void LCD_VidSendNum(u64 num)
{
	u8 x = 0;
	u64 rev = 0;

	if(num == 0)
	{
		LCD_VidSendData(48);
		return ;

	}

	while(num)
	{
		rev = (rev *10) + (num %10);

		num/=10;
		x++;

	}
	while(x)
	{
		u8 p = rev%10+48;

		LCD_VidSendData(p);

		rev/=10;

		x--;

	}
}


void LCD_VidSendFloatNum(f64 num)
{

	if(num < 0)
	{
		num = - num;
	}

	s32 real_part;
	s32 float_part;

	real_part = num ;

	float_part = (num - float_part) * 100;

	LCD_VidSendNum(real_part);
	LCD_VidSendData(".");
	LCD_VidSendNum(float_part);



}





void LCD_VidGOTOPOS(u8 row,u8 col)
{
	if( 0 == row)
	{
		LCD_VidSendCommand(128 + col);
	}

	if(1 == row)
	{
		LCD_VidSendCommand(128 + 64 + col);
	}
}



void LCD_VidDraw()
{
	LCD_VidSendCommand(64);

	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);
	LCD_VidSendData(0b00000001);

	/* got to DDRAM  */
	LCD_VidGOTOPOS(0,0);

	LCD_VidSendData(0);
}





