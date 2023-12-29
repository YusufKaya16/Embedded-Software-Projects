/*
 * Mydot.h
 *
 *  Created on: Jun 4, 2023
 *      Author: Yusuf KAYA
 */

#ifndef INC_MYDOT_H_
#define INC_MYDOT_H_

#include "stdint.h"
#include "main.h"


typedef enum{
	SCROLL_LEFT = 1,
	SCROLL_RIGHT = 0
}Direction;

typedef enum{
	MAX_OK = 1,
	MAX_ERROR = 0
}MAX_Status;

MAX_Status MAX7219_Init(void);
MAX_Status MAX_SendData(uint8_t address, uint8_t data);
void MAX_Send_Char(uint8_t chr);
void MAX_SendString(char *message);
void Zeros(void);





#endif /* INC_MYDOT_H_ */
