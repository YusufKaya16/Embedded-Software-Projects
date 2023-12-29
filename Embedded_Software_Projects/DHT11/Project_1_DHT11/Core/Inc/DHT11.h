/*
 * DHT11.h
 *
 *  Created on: Jun 5, 2023
 *      Author: Yusuf KAYA
 */

#ifndef INC_DHT11_H_
#define INC_DHT11_H_

#include "main.h"


void Delay_us(uint16_t timing);
void DHT11_Init(void);
HAL_StatusTypeDef CheckResponse(void);
uint8_t *DHT11_Read(void);












#endif /* INC_DHT11_H_ */
