#include "app.h"
#include "bsp_adc.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "Config.h"
Color_t color = COLOR_BLUE;
uint8_t led_flag = 0;
void App_Init(void) {
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	Bsp_CAN_Init();
	Bsp_ADC_Init();
	Bsp_Timer_Init();
}
