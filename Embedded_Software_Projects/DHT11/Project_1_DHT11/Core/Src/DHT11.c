/*
 * DHT11.c
 *
 *  Created on: Jun 5, 2023
 *      Author: Yusuf KAYA
 */

#include "DHT11.h"
#include "dwt_stm32_delay.h"

#define DATA_Pin	GPIO_PIN_1
#define DATA_PORT	GPIOA

extern TIM_HandleTypeDef htim2;
uint8_t Buffer[5];

void DHT11_Init(void){

	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = DATA_Pin;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(DATA_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(DATA_PORT, DATA_Pin, 0);
	DWT_Delay_us(18000);						//18ms
	HAL_GPIO_WritePin(DATA_PORT, DATA_Pin, 1);
	DWT_Delay_us(40);

	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pin = DATA_Pin;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(DATA_PORT, &GPIO_InitStruct);


}


HAL_StatusTypeDef  CheckResponse(void){

	GPIO_PinState gpio_status;
	DWT_Delay_us(40);
	gpio_status = HAL_GPIO_ReadPin(DATA_PORT, DATA_Pin);

	if(GPIO_PIN_RESET == gpio_status){
		DWT_Delay_us(80);
		gpio_status = HAL_GPIO_ReadPin(DATA_PORT, DATA_Pin);
		if(GPIO_PIN_SET == gpio_status){
			while(HAL_GPIO_ReadPin(DATA_PORT, DATA_Pin));
			return HAL_OK;
		}
	}

	return HAL_ERROR;
}

uint8_t *DHT11_Read(void){

	uint8_t value = 0;
	GPIO_PinState status;

	DHT11_Init();
	while((HAL_OK != CheckResponse()));				// wait answer from DHT11

	for(int i=0; i<5; i++){

		for(int j=0; j<8; j++){

			DWT_Delay_us(100);
			status = HAL_GPIO_ReadPin(DATA_PORT, DATA_Pin);

			if(GPIO_PIN_RESET == status){
				//MSB bit First
				value &= ~(1<<(7-j));			//bit is 0
			}
			else{
				value |= (1<<(7-j));			//bit is 1
			}

		}

		Buffer[i] = value;
		value = 0;

	}

	return Buffer;

}







