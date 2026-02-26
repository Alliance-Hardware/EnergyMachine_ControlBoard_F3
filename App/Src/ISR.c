#include "stm32f334x8.h"
#include "stm32f3xx_hal.h"
#include "ISR.h"
#include "app.h"
#include "bsp_adc.h"
#include "bsp_timer.h"
#include "bsp_can.h"
#include "usart.h"
#include "Config.h"
#include "stm32f3xx_hal_gpio.h"
// ADC DMA转换完成中断回调函数
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
	if (hadc->Instance == ADC1) {
		// 在这里立即处理ADC数据并发送
		Bsp_ADC_Process();
	}
}

// 定时器中断回调函数(1ms)
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM2)
	{
		Bsp_Timer2_Handler();
	}
}

// CAN中断回调函数
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef rx1_header;
    uint8_t rx_data[8];
	led_flag = 1;
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx1_header, rx_data);
    Bsp_CAN_Process(rx1_header.StdId, rx_data); // 传入标识符和数据
}

// GPIO中断回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_4 || GPIO_Pin == GPIO_PIN_5){    // SW1 || SW2,颜色切换
		uint16_t id = CAN_BASE_ID + EM_ID;
		uint8_t tx_data[8] = {0};
		switch (color) {
			case COLOR_BLUE:
				color = COLOR_RED;
				tx_data[0] = COLOR_RED;
				HAL_UART_Transmit(&huart2, &tx_data[0], 1,100);
				Bsp_CAN_SendMsg(&hcan, id, tx_data);
				break;
			case COLOR_RED:
				color = COLOR_BLUE;
				tx_data[0] = COLOR_BLUE;
				HAL_UART_Transmit(&huart2, &tx_data[0], 1,100);
				Bsp_CAN_SendMsg(&hcan, id, tx_data);
				break;
			case COLOR_GREEN:
			default:
				break;
		}
	}
}