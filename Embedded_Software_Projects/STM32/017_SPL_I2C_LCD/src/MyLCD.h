/*
 * MyLCD.h
 *
 *  Created on: 17 Nis 2023
 *      Author: Yusuf KAYA
 */

#ifndef MYLCD_H_
#define MYLCD_H_

#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "MyLCD.h"
#include "math.h"
#include "string.h"
#include "stdio.h"
#include "stdbool.h"

#define SLAVEADRESS 0x4E			//Slave cihaz (PCF8574) adresi.



void I2C_Write(uint8_t address, uint8_t data);
void I2C_Read(uint8_t address);

void Delay(void);

void Display_Init(void);
void DisplaySendCommand(char cmd);
void DisplaySendData(char data);
void DisplaySendString(char *str);
void DisplayPutCursor(int row, int col);
void DisplayClear(void);
void FloatoStr(char *str, float data);





#endif /* MYLCD_H_ */
