#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

void GPIO_Config(void)
{
	/*   IMPORTANT !!
	    	Built-in LEDs are in Port D, at pins 12-13-14-15.
	    	User button is in Port A, at pin 0.
	 */


	//  LED part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   // Port D enabled

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14;   // Pins 12 and 14 are initialized
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;   // Pins 12 and 14 are output
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // outputs are pulled down
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   // freq. is 50 MHz
	GPIO_Init(GPIOD, &GPIO_InitStruct);



	// BUTTON part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;   // push button is at pin PA0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;   // button as input
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // button is pulled down
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}



int main(void)
{
	GPIO_Config();
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);

	// when button is pressed, LEDs in pin 12 & 14 light up
	while (1)
	{
		if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)
		GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
		else if  (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==0)
		GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
	}
}

void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size)
{
  /* TODO, implement your code here */
  return;
}



uint16_t EVAL_AUDIO_GetSampleCallBack(void)
{
  /* TODO, implement your code here */
  return -1;
}
