#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Delay(void){

	int i = 0;
	while(i<1000000){
		i++;
	}
}

void RCC_Config(void){

	RCC->CR |= (1<<16);				//HSEON
	while(!(RCC->CR & (1<<17)));	//HSE Flag Control
	RCC->CR |= (1<<19);				//CSSON Active
	RCC->PLLCFGR = 0x00000000;		//PLL Setting Reset
	RCC->PLLCFGR |= (4<<0);			//PLL_M = 4
	RCC->PLLCFGR |= (168<<6);		//PLL_N = 168
	RCC->PLLCFGR &= ~(1<<16);
	RCC->PLLCFGR &= ~(1<<17);		//PLL_P = 2
	RCC->CR |= (1<<24);				//PLLON
	while(!(RCC->CR & (1<<25)));	//PLL Flag Control

	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);			//System Clock is PLL
	while(!(RCC->CFGR & (1<<1)));	//System Clock PLL Flag Control

}

//GPIO settings.
void GPIO_Config(void){

	RCC->AHB1ENR |= (1<<3);		//GPIOD PORT CLOCK ENABLE.

	GPIOD->MODER |= (1<<24);
	GPIOD->MODER &= ~(1<<25);	//GPIOD pin 12 = Output Mode

	GPIOD->MODER |= (1<<26);
	GPIOD->MODER &= ~(1<<27);	//GPIOD pin 13 = Output Mode

	GPIOD->MODER |= (1<<28);
	GPIOD->MODER &= ~(1<<29);	//GPIOD pin 14 = Output Mode

	GPIOD->MODER |= (1<<30);
	GPIOD->MODER &= ~(1<<31);	//GPIOD pin 15 = Output Mode

	/* GPIOD->OTYPER = 0	Default Settings */

	//GPIOD Speed settings. Speed is 100MHz
	GPIOD->OSPEEDR |= (1<<24);
	GPIOD->OSPEEDR |= (1<<25);

	GPIOD->OSPEEDR |= (1<<26);
	GPIOD->OSPEEDR |= (1<<27);

	GPIOD->OSPEEDR |= (1<<28);
	GPIOD->OSPEEDR |= (1<<29);

	GPIOD->OSPEEDR |= (1<<30);
	GPIOD->OSPEEDR |= (1<<31);
	//Kisa islem olarak speed degerlerini GPIOD->OSPEEDR |= 0xFF000000; yazilabilir. ya da (FF<<24); olarak da yazilabilir.

}

int main(void)
{

	RCC_Config();					
	SystemCoreClockUpdate();		/* Clock Setting Update */
	GPIO_Config();					

  while (1)
  {

	  GPIOD->ODR |= (1<<12);
	  GPIOD->ODR |= (1<<13);
	  GPIOD->ODR |= (1<<14);
	  GPIOD->ODR |= (1<<15);

	  Delay();

	  GPIOD->ODR &= ~(1<<12);
	  GPIOD->ODR &= ~(1<<13);
	  GPIOD->ODR &= ~(1<<14);
	  GPIOD->ODR &= ~(1<<15);

	  Delay();


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
