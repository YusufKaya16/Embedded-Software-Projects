#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

int value = 0;

void Delay(uint32_t count){
	while(count > 0){
		count--;
	}
}

void RCC_Config(){

	RCC->CR = 0x00000000;
	RCC->CR |= 0x00010000;
	while(!(RCC->CR & (0x00020000)));
	RCC->CR |= 0x00080000;

	RCC->PLLCFGR = 0x00000000;
	RCC->PLLCFGR |= 0x00400000;
	RCC->PLLCFGR |= 0x00000004;		//PLL_M = 4
	RCC->PLLCFGR |= 0x00002A00;		//PLL_N = 168
	RCC->CR |= 0x01000000;			//PLL ON
	while(!(RCC->CR & 0x02000000));

	RCC->CFGR = 0x00000000;
	RCC->CFGR |= 0x00000002;
	while(!(RCC->CFGR & 0x00000002));

}

void DAC1_Config(){

	RCC->AHB1ENR |=	0x00000001;		//GPIOA CLOCK ENABLE.
	RCC->APB1ENR |= 0x20000000;		//DAC1 CLOCK ENABLE.
	DAC->CR |= 0x00000001;			//DAC1 ENABLE.
	DAC->SWTRIGR |= 0x00000000;		//SOFTWARE TRIGGER DISABLE.
	DAC->DHR12R1 |= 0x00000000;		//DAC1 12 BIT RIGHT ALIGNMENT.

}


int main(void)
{

	RCC_Config();
	DAC1_Config();



  while (1)
  {
	  for(value=0; value<4096; value++){
		  DAC->DHR12R1 = value;
		  Delay(16800);
	  }

	  for(value = 4095; value>0; value--){
		  DAC->DHR12R1 = value;
		  Delay(16800);
	  }

	  value=0;

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
