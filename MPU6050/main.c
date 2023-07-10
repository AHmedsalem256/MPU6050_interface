/*
 * main.c
 *
 *  Created on: Jul 2, 2023
 *      Author: Ahmed
 */


#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"DIO_interface.h"
#include"TWI.h"

#include"MPU6050.h"
#include"LCDinterfaceV5.h"

#include<avr/delay.h>

extern f64 Acc_x;
extern f64 Acc_y;
extern f64 Acc_z;

f64 Xa;
f64 Ya;
f64 Za;
u64 X_a;
u64 Y_a;
u64 Z_a;

/* Indication for Xa,Ya,Za */

// Xa >> B0,B7

//Ya >> B1,B6

//Za >> B2,B5


void Print_values(f64  x_axis,f64  y_axis,f64  z_axis)
{
	LCD_VidGOTOPOS(0,0);
	LCD_VidSendData('x');
	LCD_VidSendFloatNum(x_axis);
	LCD_VidGOTOPOS(1,0);
	LCD_VidSendData('y');
	LCD_VidSendFloatNum(y_axis);

	LCD_VidGOTOPOS(0,9);
	LCD_VidSendData('z');
	LCD_VidGOTOPOS(1,9);
	LCD_VidSendFloatNum(z_axis);
}


void main()
{

	LCD_VidIntialize();

	TWI_ConfigType *TWI = {0x68,480};

	TWI_init(&TWI);

	MPU6050_Init();

	/*Pins configration for output*/

	DIO_VidSetPinDirection(1,0,1);
	DIO_VidSetPinDirection(1,1,1);
	DIO_VidSetPinDirection(1,2,1);
	DIO_VidSetPinDirection(1,5,1);
	DIO_VidSetPinDirection(1,6,1);
	DIO_VidSetPinDirection(1,7,1);



	while(1)
	{


		MPU_6050_Reading();


		Xa = Acc_x / 16384.0;
		Ya = Acc_y / 16384.0;
		Za = Acc_z / 16384.0;

		Print_values(Xa,Ya,Za);
				_delay_ms(100);
			LCD_VidSendCommand(0x01);

	}


}




/*
 * 		X_a = Acc_x / 16384.0;
		Y_a = Acc_y / 16384.0;
		Z_a = Acc_z / 16384.0;

 *
				if(X_a == 1)
				{
					DIO_VidSetPinValue(1,0,1);
					//LCD_VidSendString("x+");
				}

				else if(X_a != 0 && X_a != 1)
				{
					DIO_VidSetPinValue(1,7,1);
					//LCD_VidSendString("-x");
				}

				else if(X_a == 0)
				{
					DIO_VidSetPinValue(1,0,0);
					DIO_VidSetPinValue(1,7,0);
				}

				if(Y_a == 1)
				{
					DIO_VidSetPinValue(1,1,1);
					//LCD_VidSendString("Y+");
				}

				else if(Y_a != 0 && Y_a != 1)
				{
					DIO_VidSetPinValue(1,6,1);
					//LCD_VidSendString("-Y");
				}

				else if(Y_a == 0)
				{
					DIO_VidSetPinValue(1,1,0);
					DIO_VidSetPinValue(1,6,0);
				}

				if(Z_a == 1)
				{
					DIO_VidSetPinValue(1,2,1);
					//LCD_VidSendString("Z+");
				}

				else if(Z_a != 0 && Z_a != 1)
				{

					DIO_VidSetPinValue(1,5,1);
					//LCD_VidSendString("-Z");
				}

				else if(Z_a == 0)
				{
					DIO_VidSetPinValue(1,2,0);
					DIO_VidSetPinValue(1,5,0);
				}
*/


