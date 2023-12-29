#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

//Fonksiyon prototipleri.
void GPIO_Config(void);
void EXTI_Config(void);
void Delay(void);

//STDPERIPH tarafindan olusturulan structlardan nesneler yaratildi.
GPIO_InitTypeDef GPIO_Struct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_Struct);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_Struct);

}

void EXTI_Config(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line2;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;

	EXTI_Init(&EXTI_InitStruct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, GPIO_PinSource0 | GPIO_PinSource2);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 

	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;

	NVIC_Init(&NVIC_InitStruct);


}

void EXTI0_IRQHandler(void){

	if(EXTI_GetITStatus(EXTI_Line0) != RESET){

		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		Delay();
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		Delay();
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		Delay();
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		Delay();

		EXTI_ClearITPendingBit(EXTI_Line0);

	}

}

void EXTI2_IRQHandler(void){

	if(EXTI_GetITStatus(EXTI_Line2)){

		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		Delay();
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		Delay();
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		Delay();
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		Delay();

		EXTI_ClearITPendingBit(EXTI_Line2);

	}
}


void Delay(void){
	int i = 0;
	while(i<10000000){
		i++;
	}
}

int main(void)
{

	GPIO_Config();
	EXTI_Config();


  while (1)
  {

	  GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);

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
