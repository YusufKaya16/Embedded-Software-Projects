#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int counter = 0;

void Delay(void){
	int i;
	while(i<1000000){
		i++;
	}
}

GPIO_InitTypeDef GPIO_Struct;

//GPIO Settings.
void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	//GPIOA Pin 1 settings.
	GPIO_Struct.GPIO_Pin = GPIO_Pin_1;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_Struct);

	//GPIOE Pins settings.
	GPIO_Struct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE, &GPIO_Struct);

}


int main(void)
{

	GPIO_Config();

  while (1)
  {

	  if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1)){
		  while(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1));
		  Delay();
		  counter++;
	  }

	  Delay();

	  switch(counter){

	  case 0:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_13);
		  break;

	  case 1:
		  GPIO_SetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_9);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		  break;

	  case 2:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_12);
		  break;

	  case 3:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_12);
		  break;

	  case 4:
		  GPIO_SetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 );
		  break;

	  case 5:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_11);
		  break;

	  case 6:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_8);
		  break;

	  case 7:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
		  GPIO_ResetBits(GPIOE,  GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		  break;

	  case 8:
		  GPIO_SetBits(GPIOE, GPIO_Pin_All);
		  break;

	  case 9:
		  GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13);
		  GPIO_ResetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_11);
		  break;

	  default:
		  counter = 0;
		  break;

	  }
  }
}




















void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}


uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
