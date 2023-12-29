#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int counter = 0;
int value = 0;

void TIMER_Config(void);
void GPIO_Config(void);
void NVIC_Config(void);
void TIM3_IRQHandler(void);


//TIMER, GPIO and NVIC Structures.
GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_InitStruct);

}

void TIMER_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 1999;
	TIM_InitStruct.TIM_Prescaler = 41999;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM3, &TIM_InitStruct);
	TIM_Cmd(TIM3, ENABLE);

}

void NVIC_Config(void){

	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);		//Timerler ile interrupt' i beraber kullanirken bu fonksiyonu kullanmak gerekiyor.

	NVIC_Init(&NVIC_InitStruct);

}

void TIM3_IRQHandler(void){

	value++;
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);

}

int main(void)
{

	GPIO_Config();
	TIMER_Config();
	NVIC_Config();

  while (1)
  {

	  counter = TIM_GetCounter(TIM3);

	  switch(value){

	  case 1:
		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
		  break;
	  case 2:
		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
		  break;
	  case 3:
		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
		  break;
	  case 4:
		  GPIO_SetBits(GPIOD, GPIO_Pin_15);
		  break;
	  default:
		  value = 0;
		  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
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
