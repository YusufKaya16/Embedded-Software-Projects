#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void Delay(void){

	int i=0;
	while(i<5000000){
		i++;
	}
}

GPIO_InitTypeDef GPIO_Struct;

//GPIO Settings.
void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	//GPIOE Pins settings.
	GPIO_Struct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOE, &GPIO_Struct);

	GPIO_Struct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Struct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Struct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOD, &GPIO_Struct);

}

void Display_1(int birler){

	switch(birler){

	case 0:
		GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
		GPIO_ResetBits(GPIOE, GPIO_Pin_13);
		break;

	case 1:
		GPIO_SetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_9);
		GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		break;

	case 2:
		 GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13);
		 GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_12);
		 break;

	case 3:
		 GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13);
		 GPIO_ResetBits(GPIOE, GPIO_Pin_11 | GPIO_Pin_12);
		 break;

	case 4:
		 GPIO_SetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13);
		 GPIO_ResetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_10 | GPIO_Pin_11 );
		 break;

	case 5:
		 GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_13);
		 GPIO_ResetBits(GPIOE, GPIO_Pin_8 | GPIO_Pin_11);
		  break;

	case 6:
		GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		GPIO_ResetBits(GPIOE, GPIO_Pin_8);
		break;

	case 7:
		GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9);
		GPIO_ResetBits(GPIOE,  GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		break;

	case 8:
		GPIO_SetBits(GPIOE, GPIO_Pin_All);
		break;

	case 9:
		GPIO_SetBits(GPIOE, GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_12 | GPIO_Pin_13);
		GPIO_ResetBits(GPIOE, GPIO_Pin_10 | GPIO_Pin_11);
		break;

	}
}


void Display_2(int onlar){

	switch(onlar){

	case 0:
		GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		break;

	case 1:
		GPIO_SetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_10);
		GPIO_ResetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		break;

	case 2:
		 GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14);
		 GPIO_ResetBits(GPIOD, GPIO_Pin_10 | GPIO_Pin_13);
		 break;

	case 3:
		 GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14);
		 GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
		 break;

	case 4:
		 GPIO_SetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_13 | GPIO_Pin_14);
		 GPIO_ResetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_11 | GPIO_Pin_12);
		 break;

	case 5:
		 GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14);
		 GPIO_ResetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_12);
		  break;

	case 6:
		GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		GPIO_ResetBits(GPIOD, GPIO_Pin_9);
		break;

	case 7:
		GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10);
		GPIO_ResetBits(GPIOD,  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);
		break;

	case 8:
		GPIO_SetBits(GPIOD, GPIO_Pin_All);
		break;

	case 9:
		GPIO_SetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12);
		GPIO_ResetBits(GPIOD, GPIO_Pin_11 | GPIO_Pin_12);
		break;

	}
}


int i = 0;

int main(void)
{

	GPIO_Config();

  while (1)
  {

	  Display_2(i);

	  for(int j=0; j<=9; j++){
		  Display_1(j);
		  Delay();

	  }

	  i++;

	  if(i>9){
		  i=0;
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
