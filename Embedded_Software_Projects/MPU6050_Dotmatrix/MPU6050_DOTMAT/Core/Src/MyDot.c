/*
 * MyDot.c
 *
 *  Created on: Jun 4, 2023
 *      Author: Yusuf KAYA
 */

#include "Mydot.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;


void Zeros(void){

	for(int i=1; i<9; i++){
		MAX_SendData(i, 0x00);
	}

}


MAX_Status MAX7219_Init(void){

	MAX_SendData(0x09, 0x00);			//No decoding.
	MAX_SendData(0x0A, 0x03);			//Brightness intensity.
	MAX_SendData(0x0B, 0x07);			//Scan limit leds = 8.
	MAX_SendData(0x0C, 0x01);			//power down = 0, normal mode = 1.
	MAX_SendData(0x0F, 0x00);			//No test display.
	Zeros();
	return MAX_OK;
}

MAX_Status MAX_SendData(uint8_t address, uint8_t data){

	HAL_StatusTypeDef status;

	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, 0);
	status = HAL_SPI_Transmit(&hspi1, &address, 1, 100);
	if(HAL_OK == status){
		status = HAL_SPI_Transmit(&hspi1, &data, 1, 100);
		if(HAL_OK == status){
			HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, 1);
			return MAX_OK;
		}
		return MAX_ERROR;
	}
	return status;
}




