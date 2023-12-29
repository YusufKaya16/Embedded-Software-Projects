#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void GPIO_Config(void);
void TIMER_Config(void);
void delay_ms(uint32_t time);

int counter;

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIMER_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_TIM5);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void TIMER_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);


	TIMER_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMER_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER_InitStruct.TIM_Period = 49;
	TIMER_InitStruct.TIM_Prescaler = 83;
	TIMER_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM5, &TIMER_InitStruct);
	TIM_Cmd(TIM5, ENABLE);


	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIMOC_InitStruct.TIM_OutputState = ENABLE;

}

void delay_ms(uint32_t time){

	counter = time;
	while(counter);
}


int main(void)
{

	GPIO_Config();
	TIMER_Config();

	SysTick_Config(SystemCoreClock / 1000);		//1ms' de bir interrupt' a girer.

  while (1)
  {

	  //RED
	  for(int i=0; i<=49; i++){

		  TIMOC_InitStruct.TIM_Pulse = i;
		  TIM_OC1Init(TIM5, &TIMOC_InitStruct);
		  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
		  delay_ms(50);
	  }

	  for(int j=49; 0<=j; j--){

		  TIMOC_InitStruct.TIM_Pulse = j;
		  TIM_OC1Init(TIM5, &TIMOC_InitStruct);
		  TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
		  delay_ms(50);

	  }

	  //GREEN
	  for(int i=0; i<=49; i++){

		  TIMOC_InitStruct.TIM_Pulse = i;
		  TIM_OC2Init(TIM5, &TIMOC_InitStruct);
		  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
		  delay_ms(50);

	  }

	  for(int j=49; 0<=j; j--){

		  TIMOC_InitStruct.TIM_Pulse = j;
		  TIM_OC2Init(TIM5, &TIMOC_InitStruct);
		  TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
		  delay_ms(50);

	 }

	  //BLUE
	 for(int i=0; i<=49; i++){

		 TIMOC_InitStruct.TIM_Pulse = i;
		 TIM_OC3Init(TIM5, &TIMOC_InitStruct);
		 TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
		 delay_ms(100);

	 }

	 for(int j=49; 0<=j; j--){

		 TIMOC_InitStruct.TIM_Pulse = j;
		 TIM_OC3Init(TIM5, &TIMOC_InitStruct);
		 TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
		 delay_ms(100);

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
