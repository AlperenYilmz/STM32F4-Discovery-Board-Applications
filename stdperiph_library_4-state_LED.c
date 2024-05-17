
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

GPIO_InitTypeDef GPIO_InitStruct;

void Delayullah(uint32_t t)
{
    while (t--);
}

void GPIO_Config(void)
{
	/*   ÖNEMLÝ NOT!!!!
	    	Yerleþik ledler D portunda, 12-13-14-15. pinlerde bulunuyor
	    	User button A portunda, 0 pininde bulunuyor
	 */


	//  LED part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);   // D portu enable ediliyor

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14;   // 12 ve 14. pinlerini seçiyorum
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;   // output olarak ayarlýyorum
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // pupd seçip pull down yapýcaz, od yaparsak düz topraða akar led yanmaz
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;   // çalýþma frekansý 50 MHz
	GPIO_Init(GPIOD, &GPIO_InitStruct);



	// BUTTON part
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;   // button PA0'da
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;   // buttonu input olarak alýyoruz
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;   // built-in olarak pull-down direnç var
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}


int state = 0;
int main(void)
{
	GPIO_Config();
	GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);



	while (1)
	{
		if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0)==1)
		{
			Delayullah(10000000);
			state++;
		}

		switch (state)
		{
			case 0:
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				break;

			case 1:
				GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				Delayullah(1000000);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				Delayullah(1000000);
				break;

			case 2:
				GPIO_SetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				Delayullah(1000000);
				GPIO_ResetBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_14);
				Delayullah(1000000);
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
