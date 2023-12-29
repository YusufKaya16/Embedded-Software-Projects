#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

uint8_t adc_value;
float adc_voltage;

void RCC_Config(void);
void GPIO_Config(void);
void ADC_Config(void);
uint8_t ADC_Reading(void);

void RCC_Config(void){

	RCC->CR |= (1<<16);					//HSE ON.
	while(!(RCC->CR & (1<<17)));		//HSERDY FLAG CONTROL.
	RCC->CR |= (1<<19);					//CSS ON.
	RCC->PLLCFGR |= 0x00000000;			//PLL SETTING WAS RESET.
	RCC->PLLCFGR |= (1<<22);			//HSE SELECTED FOR PLLSRC.
	RCC->PLLCFGR |= (168<<6);			//PLL_N = 168.
	RCC->PLLCFGR |= (4<<0);				//PLL_M = 4.
	RCC->PLLCFGR |= 0x00000000;			//PLL_P = 2.
	RCC->CFGR |= (1<<1);
	RCC->CFGR &= ~(1<<0);				//PLL SELECTED FOR RCC.
	RCC->CFGR |= 0x00000000;			//AHB PRESCALER = 1.
	RCC->CFGR |= 0x00008000;			//APB2 PRESCALER = 2.
	RCC->CFGR |= 0x00001400;			//APB1 PRESCALER = 4.
	RCC->CIR |= 0x00008000;				//HSERDY CLEAN.
	RCC->CIR |= 0x00800000;				//CSS FLAG CLEAN.

}

void GPIO_Config(void){

	RCC->AHB1ENR |= 0x00000009;

	//GPIOD PORT SETTINGS.
	GPIOD->MODER |= 0x55000000;
	GPIOD->OTYPER |= 0x00000000;
	GPIOD->OSPEEDR |= 0xFF000000;
	GPIOD->PUPDR |= 0x00000000;

	//GPIOA PORT SETTINGS.
	GPIOA->MODER |= 0x00000030;
	GPIOA->OSPEEDR |= 0x00000030;

}

void ADC_Config(void){

	RCC->APB2ENR |= (1<<8);			//ADC1 ENABLE.
	ADC->CCR |= 0x00010000;			//ADC PRESCALER

	ADC1->CR1 |= 0x02000000;		//ADC1 RESOLUTION = 8.
	ADC1->CR2 |= 0x00000001;		//ADC ENABLE.
	ADC1->SMPR2 |= 0x00000100;		//ADC1 SAMPLING TIME = 84 CYCLES.

}


uint8_t ADC_Reading(void){

	uint8_t value;

	ADC1->CR2 |= 0x40000000;		//CYCLES START.
	while(!(ADC1->SR & 0x00000002));	//CEVRIM BITTI MI. EOC FLAG.
	value = ADC1->DR;

	return value;

}

int main(void)
{

	RCC_Config();
	GPIO_Config();
	ADC_Config();


  while (1)
  {
	  adc_value = ADC_Reading();
	  adc_voltage = adc_value * ((3.3) / 255);


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
