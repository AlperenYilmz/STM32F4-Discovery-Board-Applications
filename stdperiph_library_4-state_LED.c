#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

/* alternative counter (WIP)
volatile uint32_t msTicks = 0;  // real-time milliseconds counter

void sysTickHandler(void)
{
    msTicks++;  // increment every 1 ms
}

void Delay_ms(uint32_t ms)
{
    uint32_t start = msTicks;
    while ((msTicks - start) < ms);
}
*/

void userDefDelay(uint32_t t)	// runtime based counter
{
    while (t--);
}

void GPIO_Config(void)
{
	/*   IMPORTANT !!
	    	Built-in LEDs are in Port D, at pins 12-13-14-15.
	    	User button is in Port A, at pin 0.
	 */

	//  LED part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   // Port D enabled

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14;   // Initializing pins 12 and 14
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;   // pins 12 and 14 are now set as output
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // pull down resistor mode
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   // frequency 50 MHz
	GPIO_Init(GPIOD, &GPIO_InitStruct);



	// BUTTON part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;   // push button is at PA0
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;   // button is initialized as input
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // pull down resistor for push-button
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


int state = 0;    // state machine is initially set at 0 (reset)

int main(void)
{
	GPIO_Config();
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);    // Although initialized at reset, LEDs again are set off, for good measure

	/*
	- Loop below cycles through 4 different states
 	- Each state lights up the LEDS in different configuration and time length
  	- States switched through user button input
 	*/
	
	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)
		{
			userDefDelay(10000000);
			state++;
		}

		switch (state)
		{
			case 0:
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				break;

			case 1:
				GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				userDefDelay(100000000);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				userDefDelay(100000000);
				break;

			case 2:
				GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				userDefDelay(50000000);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				userDefDelay(50000000);
				break;

			case 3:
				GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				break;

			case 4:
				state=0;
				break;
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
