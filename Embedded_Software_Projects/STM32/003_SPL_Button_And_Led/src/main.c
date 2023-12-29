#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_Struct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_1;			
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;		
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;		
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;		
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;	

	GPIO_Init(GPIOA, &GPIO_Struct);		

	GPIO_Struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE, &GPIO_Struct);	

}

void Delay(void){

	int i = 0;
	while(i<1000000){
		i++;
	}
}

int counter=0;

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
	  case 1:
		  GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		  GPIO_SetBits(GPIOE, GPIO_Pin_0);
		  break;
	  case 2:
		  GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		  GPIO_SetBits(GPIOE, GPIO_Pin_1);
		  break;
	  case 3:
		  GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		  GPIO_SetBits(GPIOE, GPIO_Pin_2);
		  break;
	  case 4:
		  GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		  GPIO_SetBits(GPIOE, GPIO_Pin_3);
		  break;
	  case 5:
		  GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		  GPIO_SetBits(GPIOE, GPIO_Pin_4);
		  break;
	  case 6:
		  GPIO_SetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		  break;
	  case 7:
		  counter = 0;
		  GPIO_ResetBits(GPIOE, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
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
