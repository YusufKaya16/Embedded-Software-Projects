#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "MyLCD.h"

GPIO_InitTypeDef GPIO_InitStruct;
I2C_InitTypeDef I2C_InitStruct;

char I2C_Buffer[10];
int i=0, counter = 0;

void LED_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_I2C1);		//PB6 -> SCL,
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_I2C1);		//PB7 -> SDA

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

void I2C_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStruct.I2C_ClockSpeed = 400000;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;

	I2C_Init(I2C1, &I2C_InitStruct);
	I2C_Cmd(I2C1, ENABLE);

}

void I2C_Write(uint8_t address, uint8_t data){


	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));									//SDA hatti mesgul mu, degil mi? if 1-> wait else 0-> continue.
	I2C_GenerateSTART(I2C1, ENABLE);												//I2C' yi baslatma komutu gondererek baslatiyorum.	HIGH -> LOW
	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));					//MASTER Mode secilene kadar bekle.
	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);					//Slave cihaz iletisimi icin adres bilgisi gonderiyorum.
	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));		//Adres iletimi gerceklesti mi?.
	I2C_SendData(I2C1, data);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));				//mesaj iletimi bitti mi?

	I2C_GenerateSTOP(I2C1, ENABLE);

}

void I2C_Read(uint8_t address){

	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);
	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)));
	I2C_Send7bitAddress(I2C1, address, I2C_Direction_Transmitter);
	while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));		//Adres iletimi gerceklesti mi?.

	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE)){
		I2C_Buffer[i] = I2C_ReceiveData(I2C1);
		i++;
	}
	i=0;
	I2C_GenerateSTOP(I2C1, ENABLE);

}


int main(void)
{

	GPIO_Config();
	I2C_Config();
	Display_Init();
	LED_Config();

	DisplayClear();
	Delay();
	DisplayPutCursor(1, 0);
	Delay();



  while (1)
  {

	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)){
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0));
		  if(counter < 2){
			  counter++;
		  }
		  else{
			  counter = 1;
		  }
	  }
	  switch(counter){
	  case 1:
		  GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
		  DisplaySendCommand(0x80);
		  DisplaySendString("LedLer Yandi");
		  break;
	  case 2:
	  		  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	  		  DisplaySendCommand(0x80);
	  		  DisplaySendString("Ledler Sondu");
	  		  break;
	  }

  }

}



void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
