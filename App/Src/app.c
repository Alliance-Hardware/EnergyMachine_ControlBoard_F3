#include "app.h"

#include "bsp_adc.h"
#include "bsp_can.h"
#include "bsp_timer.h"
#include "Config.h"
Color_t color = COLOR_BLUE;
void App_Init(void) {
	Bsp_CAN_Init();
	Bsp_ADC_Init();
	Bsp_Timer_Init();
}
