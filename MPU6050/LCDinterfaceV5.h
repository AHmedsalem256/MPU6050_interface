#ifndef LCDINTERFACEV5_H
#define LCDINTERFACEV5_H

#include"STD_TYPES.h"
void LCD_VidIntialize();
void LCD_VidSendCommand(u8 value);
void LCD_VidSendData(u8 value);
void LCD_VidSendString(u8 *ptr);

void LCD_VidSendNum(u64 num);

void LCD_VidGOTOPOS(u8 row,u8 col);

void LCD_VidSendFloatNum(f64 num);


#endif

