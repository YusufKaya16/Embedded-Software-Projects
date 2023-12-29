#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Delay(void);
void RCC_Config(void);
void GPIO_Config(void);

void Delay(void){

	int i=0;
	while(i<1000000){
		i++;
	}
}

//Clock Configuration.
void RCC_config(void){

	RCC->CR |= (1<<16);		//HSE on.

	while(!(RCC->CR & (1<<17)));	//HSE flag control.

	RCC->CR |= (1<<19);		//CSS on.

	RCC->PLLCFGR = 0x00000000;		//PLL settings reset.
	RCC->PLLCFGR |= (1<<22);		//HSE selected for PLL.
	RCC->PLLCFGR |= (4<<0);			//PLL_M = 4.
	RCC->PLLCFGR |= (168<<6);		//PLL_N = 168.
	RCC->PLLCFGR &= ~(1<<16);
	RCC->PLLCFGR &= ~(1<<17);		//PLL_P = 2.

	RCC->CR |= (1<<24);				//PLL on.

	while(!(RCC->CR & (1<<25)));	//PLL flag control.

	RCC->CFGR  &= ~(1<<0);
	RCC->CFGR |= (1<<1);			//Selected PLL for RCC source.

	while(!(RCC->CFGR & (1<<1)));	//RCC flag control.

}

//GPIO Konfigurasyonu.
void GPIO_Config(void){

	RCC->AHB1ENR |= (1<<3);		//GPIOD Port is active.

	//led configuration.
	GPIOD->MODER |= 0x00055555;		//LED's output mode.
	GPIOD->OTYPER = 0x00000000;		//LED's otype push pull.
	GPIOD->OSPEEDR |= 0x000FFFFF;	//LED's ospeed 100MHz.
	GPIOD->PUPDR = 0x00000000;		//LED's nopull.

}

int counter = 1;

int main(void)
{

	RCC_config();
	GPIO_Config();

  while (1)
  {

	  for(int i=0; i<=(10-counter); i++){
		  GPIOD->ODR |= (1<<i);
		  Delay();
	  }

	  for(int j=0; j<(10-counter); j++){
		  GPIOD->ODR &= ~(1<<j);
		  Delay();
	  }

	  counter++;
	  if(counter > 9){
		  counter=0;

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
