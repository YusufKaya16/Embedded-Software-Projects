#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonStruct;
DMA_InitTypeDef DMAInitStruct;

#define BUFFERSIZE 1

uint16_t adc_value[BUFFERSIZE];		//Tek adc degeri tutacak.


void GPIO_Config(void);
void ADC_Config(void);
void DMA_Config(void);

void GPIO_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA, &GPIO_InitStruct);

}


void ADC_Config(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_CommonStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonStruct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADC_CommonStruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;	//Tek bir kanaldan okuma yapilacagi icin Disabled mode.
	ADC_CommonStruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_18Cycles;

	ADC_CommonInit(&ADC_CommonStruct);

	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_NbrOfConversion = BUFFERSIZE;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;


	ADC_Init(ADC1, &ADC_InitStruct);
	//Cevre birimi aktif.
	ADC_Cmd(ADC1, ENABLE);

	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_56Cycles);
	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);

}

void DMA_Config(void){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	DMAInitStruct.DMA_Channel = DMA_Channel_0;						//kullanilacak cevre birimine gore DMA kanal secimi.
	DMAInitStruct.DMA_Priority = DMA_Priority_VeryHigh;				//Coklu DMA uygulamalari icin DMA onceligi.
	DMAInitStruct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		//// degerin nereden okundugunu veren ifadedir ADC_DR adres degeri
	//vermek zorundayiz. 0x4001204C olarakta yazilabilirdi. ADC1 registerinin adresidir.
	DMAInitStruct.DMA_Memory0BaseAddr = (uint32_t)&adc_value;		//DMA' nin verileri kaydedecegi adres bilgisi.
	DMAInitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMAInitStruct.DMA_BufferSize = BUFFERSIZE;
	DMAInitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMAInitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
	DMAInitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMAInitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMAInitStruct.DMA_Mode = DMA_Mode_Circular;
	DMAInitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMAInitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMAInitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMAInitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;

	DMA_Init(DMA2_Stream0, &DMAInitStruct);
	DMA_Cmd(DMA2_Stream0, ENABLE);

}

int main(void)
{

	GPIO_Config();
	ADC_Config();
	DMA_Config();

	ADC_SoftwareStartConv(ADC1);		//CPU' yu kullanmadan burada adc cevrimini yaparak DMA' ya yaziyoruz. O yuzden while icini kullanmadik.

  while (1)
  {


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
