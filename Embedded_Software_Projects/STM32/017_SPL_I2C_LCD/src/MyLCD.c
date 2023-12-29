/*
 * MyLCD.c
 *
 *  Created on: 17 Nis 2023
 *      Author: Yusuf KAYA
 */

#include "MyLCD.h"

extern I2C_InitTypeDef I2C_InitStruct;

void Delay(void){

	int i=0;
	while(i<1000000){
		i++;
	}
}


void Display_Init(void){


	DisplaySendCommand(0x02);
	DisplaySendCommand(0x28);
	DisplaySendCommand(0x0D);
	DisplaySendCommand(0x80);


	/*

	Delay();					//Display acilma suresi
	DisplaySendCommand(0x30);		//8 - bit mode.
	Delay();
	DisplaySendCommand(0x30);		//8 - bit mode.
	Delay();
	DisplaySendCommand(0x30);
	Delay();
	DisplaySendCommand(0x20); 		//4 - bit mode.
	Delay();

	DisplaySendCommand(0x28);		//Function set: DL = 0, N = 1, F = 0.
	Delay();
	DisplaySendCommand(0x08);		//display on/off control.
	Delay();
	DisplaySendCommand(0x01);		//display clear.
	Delay();
	DisplaySendCommand(0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	Delay();
	DisplaySendCommand(0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)

	*/

}

void DisplaySendCommand(char cmd){

	char data_up, data_low;
	uint8_t datas[4];

	data_up = cmd & 0xF0;
	data_low = (cmd<<4) & 0xF0;

	datas[0] = data_up | 0x0C;
	datas[1] = data_up | 0x08;
	datas[2] = data_low | 0x0C;
	datas[3] = data_low | 0x08;

	for(int i=0; i<4; i++){
		I2C_Write(SLAVEADRESS, datas[i]);
	}

}


void DisplaySendData(char data){

	char data_up, data_low;
	uint8_t datas[4];

	data_up = data & 0xF0;
	data_low = (data<<4) & 0xF0;

	datas[0] = data_up | 0x0D; //en=1, rs=1			//0101 0000 | 0000 1101 = 0101 1101
	datas[1] = data_up | 0x09;  //en=0, rs=1		//0101 0000 | 0000 1001
	datas[2] = data_low | 0x0D;  //en=1, rs=1
	datas[3] = data_low | 0x09;  //en=0, rs=1

	for(int i=0; i<4; i++){
		I2C_Write(SLAVEADRESS, datas[i]);
	}

}

void DisplaySendString(char *str){

	while(*str){
		DisplaySendData(*str);
		str++;
	}
}

void DisplayPutCursor(int row, int col){

	switch(row){

	case 1:
		col = col | 0x80;
		DisplaySendCommand(col);
		break;
	case 2:
		col = col | 0xC0;
		DisplaySendCommand(col);
		break;
	}
}

void FloatoStr(char *str, float data){

	char *chr = data<0 ? "-":"";
	float temp = data<0 ? -data:data;

	int value1 = (int)temp;
	float temp2 = (float)(temp - value1);
	int value2 = trunc(temp2 * 10000);

	sprintf(str, "%s%d.%d", chr, value1, value2);
}

void DisplayClear(void){
	DisplaySendCommand(0x01);
}














