#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

extern uint32_t SystemCoreClock;

uint32_t sysClkWatched;

void RCC_Config(void)
{
	RCC_DeInit();
	// 1. Enabling HSE
	RCC->CR |= 1<<16;		// HSEEN=1
	while (!(RCC->CR & (1<<17)));	// Wait until HSE Ready Flag is set
	
	// 2. Enabling Peripheral Power and Voltage Regulator
	RCC->APB1ENR |= 1<<28;	// PWREN=1
	PWR->CR |= 1<<14;	// VOS=1

	// 3. Flash Prefetch & Latency
	FLASH->ACR |= (1<<8) | (1<<9) | (1<<10) | (5<<0);	// Latency=5 wait states,  PREFETCH, DATA CACHE, INSTRUCTION CACHE enabled.

	// 4. Configuring Prescalers
	RCC->CFGR &= ~(15<<4);	// AHB=0
	RCC->CFGR |= 0b101<<10;	// APB1=4
	RCC->CFGR |= 0x4<<13;	// APB2=2

	// 5. PLL Setting
	RCC->PLLCFGR=0x24000000;		// initial reset
	RCC->PLLCFGR |= 4<<0 | 0xA8<<6 | 1<<22;	// PLLM=4, PLLN=168, PLLSRC enabled
	RCC->PLLCFGR &= ~(3<<16);		// PLLP=2

	// 6. Enabling PLL
	RCC->CR |= (1<<24);		// PLLON enabled
	while (!(RCC->CR & (1<<25)));	// wait until flag is 1

	// 7. Selecting PLL as clock source
	RCC->CFGR |= 2;			 // selecting PLL as clock source
	while (!(RCC->CFGR & (2<<2)));   // waiting until bits 2:3 become 0b10
}

int main(void)
{
	sysClkWatched=SystemCoreClock;
	RCC_Config();

	/* !! OPTIONAL !!
	RCC_DeInit();  		  -> Disables HSE, enables internal clock (16MHz)
	SystemCoreClockUpdate();  -> Clock is now 16 MHz
	*/
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
