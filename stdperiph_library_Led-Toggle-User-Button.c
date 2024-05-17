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
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   // Port D is enabled

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_15;   // pins 12 and 14 are initialized
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;   // pins 12 and 14 are output
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // outputs are pulled down
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_25MHz;   // frequency is 50 MHz
	GPIO_Init(GPIOD, &GPIO_InitStruct);


	// BUTTON part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;   // user button is at PA0 pin
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;   // button as input
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // button is pulled down when not pressed
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}



int main(void)
{

	GPIO_Config();
	GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);


	// Different from the other LED code, this keeps LEDs lit until button is released
	while(1)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);

		while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_13 | GPIO_Pin_15);
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
