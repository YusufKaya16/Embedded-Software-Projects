#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void TIMER_Config(void);
void GPIO_Config(void);
void Delay(uint32_t time);

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIMER_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM2);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void TIMER_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIMER_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMER_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER_InitStruct.TIM_Period = 19999;
	TIMER_InitStruct.TIM_Prescaler = 83;
	TIMER_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2, &TIMER_InitStruct);
	TIM_Cmd(TIM2, ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIMOC_InitStruct.TIM_OutputState = ENABLE;

}

void Delay(uint32_t time){

	while(time--);

}


int main(void)
{
	TIMER_Config();
	GPIO_Config();

  while (1)
  {

	  TIMOC_InitStruct.TIM_Pulse = 500;
	  TIM_OC1Init(TIM2, &TIMOC_InitStruct);
	  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	  Delay(21000000);

	  TIMOC_InitStruct.TIM_Pulse = 1500;
	  TIM_OC1Init(TIM2, &TIMOC_InitStruct);
	  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	  Delay(21000000);

	  TIMOC_InitStruct.TIM_Pulse = 2500;
	  TIM_OC1Init(TIM2, &TIMOC_InitStruct);
	  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

	  Delay(21000000);

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
