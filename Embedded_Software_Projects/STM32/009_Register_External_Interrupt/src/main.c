#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Delay(void);
void RCC_Config(void);
void GPIO_Config(void);
void EXTI_Config(void);
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);

void Delay(void){

	int i=0;
	while(i<1000000){
		i++;
	}
}

void RCC_Config(void){

	//HSE aktif edildi.
	RCC->CR |= (1<<16);
	while(!(RCC->CR & (1<<17)));

	//clock guvenligi aktif edildi.
	RCC->CR |= (1<<19);

	//PLL configurasyon ayarlari yapildi.
	RCC->PLLCFGR = 0X00000000;
	RCC->PLLCFGR |= (4<<0);
	RCC->PLLCFGR |= (168<<6);
	RCC->PLLCFGR &= ~(1<<16);
	RCC->PLLCFGR &= ~(1<<17);
	RCC->CR |= (1<<24);
	while(!(RCC->CR & (1<<25)));

	//System Clock kaynagi PLL olarak secildi ve bayragi kalkana kadar beklendi.
	RCC->CFGR &= ~(1<<0);
	RCC->CFGR |= (1<<1);
	while(!(RCC->CFGR & (1<<3)));

	// Cevresel clock hatlarini max seviye de kullanmak icin prescaler degerleri ayarlandi.
	RCC->CFGR |= (1<<15);	//APB2 = 2
	RCC->CFGR |= (1<<10);
	RCC->CFGR &= ~(1<<11);
	RCC->CFGR |= (1<<12);	//APB1 = 4

	//Interrupt registerinda HSE ve CSS flag temizleme.
	RCC->CIR |= (1<<19);
	RCC->CIR |= (1<<20);
	RCC->CIR |= (1<<23);


}

void GPIO_Config(void){

	//GPIOA ve GPIOD Portlarý aktif edildi. (0x00000009)
	RCC->AHB1ENR |= (1<<0);
	RCC->AHB1ENR |= (1<<3);

	//GPIOA AYARLARÝ
	GPIOA->PUPDR = 0x0000002A;
	GPIOA->OSPEEDR = 0x0000003F;

	//GPIOD AYARLARÝ
	GPIOD->MODER = 0x55000000;		//GPIOD Pin12 ... Pin15 output
	GPIOD->OTYPER = 0x00000000;		//Pinlerin cikis tipi push pull
	GPIOD->PUPDR = 0x00000000;		//Pinlerin baglanti tipleri NoPull
	GPIOD->OSPEEDR = 0xFF000000;	//Pinlerin calisma hizi 100MHz

}

void EXTI_Config(void){

	//Clock registerlerinden EXTI interrupti aktif edildi.
	RCC->APB2ENR = 0x00004000;

	SYSCFG->EXTICR[0] = 0x00000000;
	SYSCFG->EXTICR[1] = 0x00000000;
	SYSCFG->EXTICR[2] = 0x00000000;

	//NVIC Fonksinyonlarini kullanarak NVIC ayarlari yapildi.
	//NVIC tarafindan interrupt hatlari aktif edildi.
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	//NVIC tarafindan interruptlarin oncelik atamasi yapildi.
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(EXTI1_IRQn, 1);
	NVIC_SetPriority(EXTI2_IRQn, 2);

	//EXTI ayalari yapildi.
	EXTI->IMR = 0x00000007;
	EXTI->FTSR = 0x00000007;

}

void EXTI0_IRQHandler(void){

	if(EXTI->PR & 0x00000001){
		for(int i=0; i<5; i++){
			GPIOD->ODR = 0x00001000;
			Delay();
			GPIOD->ODR = 0x00000000;
			Delay();
		}

		EXTI->PR = 0x00000001;	//flag clean.
	}
}

void EXTI1_IRQHandler(void){

	if(EXTI->PR & 0x00000002){

		for(int i=0; i<5; i++){
			GPIOD->ODR = 0x00002000;
			Delay();
			GPIOD->ODR = 0x00000000;
			Delay();
		}


		EXTI->PR = 0x00000002;
	}
}

void EXTI2_IRQHandler(void){

	if(EXTI->PR & 0x00000004){

		for(int i=0; i<5; i++){
			GPIOD->ODR = 0x00004000;
			Delay();
			GPIOD->ODR = 0x00000000;
			Delay();
		}

		EXTI->PR = 0x00000004;
	}
}

int main(void)
{

	RCC_Config();
	GPIO_Config();
	EXTI_Config();


  while (1)
  {
	  GPIOD->ODR = 0x0000F000;		//GPIOD pins output aktif.

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
