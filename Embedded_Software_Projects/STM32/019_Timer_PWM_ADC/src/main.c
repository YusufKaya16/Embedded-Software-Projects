#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//Function Prototypes.
void GPIO_Config(void);
void TIMER_Config(void);
void ADC_Config(void);
uint16_t ADC_Read(void);
uint32_t Map(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);

//Object of Structures.
GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIMER_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct;
ADC_InitTypeDef ADC_Initstruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	//LED icin GPIOD.
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);

	GPIO_Init(GPIOD, &GPIO_InitStruct);

	//ADC okumak icin GPIOA.
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void TIMER_Config(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	TIMER_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIMER_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIMER_InitStruct.TIM_Period = 99;
	TIMER_InitStruct.TIM_Prescaler = 83;
	TIMER_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM4, &TIMER_InitStruct);
	TIM_Cmd(TIM4, ENABLE);


	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIMOC_InitStruct.TIM_OutputState = ENABLE;

}

void ADC_Config(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_Initstruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_Initstruct);

	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_Cmd(ADC1, ENABLE);

}

uint16_t ADC_Read(void){

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);

	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);

	return ADC_GetConversionValue(ADC1);

}

uint16_t adc_value;
uint8_t pwm_value;

uint32_t Map(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e)
{
	return (a * e) / c;

}

int main(void)
{

	GPIO_Config();
	TIMER_Config();
	ADC_Config();


  while (1)
  {

	  adc_value = ADC_Read();
	  pwm_value = Map(adc_value, 0, 4095, 0, 99);

	  TIMOC_InitStruct.TIM_Pulse = pwm_value;
	  TIM_OC1Init(TIM4, &TIMOC_InitStruct);
	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	  TIMOC_InitStruct.TIM_Pulse = pwm_value;
	  TIM_OC2Init(TIM4, &TIMOC_InitStruct);
	  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

	  TIMOC_InitStruct.TIM_Pulse = pwm_value;
	  TIM_OC3Init(TIM4, &TIMOC_InitStruct);
	  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

	  TIMOC_InitStruct.TIM_Pulse = pwm_value;
	  TIM_OC4Init(TIM4, &TIMOC_InitStruct);
	  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);



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
