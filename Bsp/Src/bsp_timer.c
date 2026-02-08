#include "bsp_timer.h"
#include "stm32f3xx_hal_tim.h"
#include "tim.h"
static uint8_t timer = 0;
void Bsp_Timer_Init(void) {
	HAL_TIM_Base_Start_IT(&htim2);
}
void Bsp_Timer2_Handler(void) {
	if(timer < 10){
		timer++;
	}
}

