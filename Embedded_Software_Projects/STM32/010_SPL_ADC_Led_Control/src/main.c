#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint16_t adc_value = 0;
float adc_voltage = 0.0;

void GPIO_Config(void);
void ADC_Config(void);
uint16_t ADC_Reading(void);

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	//GPIOD PORT
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

}

void ADC_Config(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_CommonInitStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonInitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init(ADC1, &ADC_InitStruct);
	ADC_Cmd(ADC1, ENABLE);

}

uint16_t ADC_Reading(void){

	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(!(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)));

	return ADC_GetConversionValue(ADC1);

}


int main(void)
{

	GPIO_Config();
	ADC_Config();


  while (1)
  {
	  adc_value = ADC_Reading();
	  adc_voltage = adc_value * ((3.3) / 4095);

	  if(adc_value >= 0 && adc_value <= 100){

		  GPIO_ResetBits(GPIOD, GPIO_Pin_All);
	  }

	  if(adc_value >= 101 && adc_value <= 1000){

		  GPIO_SetBits(GPIOD, GPIO_Pin_12);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

	  }

	  if(adc_value >= 1001 && adc_value <= 2000){

		  GPIO_SetBits(GPIOD, GPIO_Pin_13);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);

	  }

	  if(adc_value >= 2001 && adc_value <= 3000){

		  GPIO_SetBits(GPIOD, GPIO_Pin_14);
		  GPIO_ResetBits(GPIOD, GPIO_Pin_15);

	  }

	  if(adc_value >= 3001 && adc_value <= 4095){

		  GPIO_SetBits(GPIOD, GPIO_Pin_15);

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
