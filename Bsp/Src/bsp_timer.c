#include "bsp_can.h"
#include "can.h"
#include "stm32f334x8.h"
#include "stm32f3xx_hal.h"
#include "tim.h"
#include "bsp_timer.h"
#include "app.h"
static uint8_t timer = 0;
static uint8_t led_timer = 0;
void Bsp_Timer_Init(void) {
	HAL_TIM_Base_Start_IT(&htim2);
}
void Bsp_Timer2_Handler(void) {
	if(timer < 10){
		timer++;
	}
	if(led_flag == 1 && led_timer < 100){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
		led_timer++;
	}
	else{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
		led_flag = 0;
		led_timer = 0;
	}
}

