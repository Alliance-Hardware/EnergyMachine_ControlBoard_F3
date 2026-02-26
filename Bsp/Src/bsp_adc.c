#include "adc.h"
#include "stm32f3xx_hal_adc_ex.h"
#include "bsp_adc.h"
#include "bsp_can.h"
#include "Config.h"

extern uint8_t timer;
static uint16_t adc_sample[10] = {0};	// ADC采样的数据缓存到其中
static uint8_t last_target_mask = 0;	// 上次击打检测到的环数
const uint8_t index_to_ring[10] = {6, 7, 8, 9, 10, 5, 4, 3, 2, 1};	// 实际环数与ADC通道对应关系

void Bsp_ADC_Init(void) {
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	HAL_Delay(100);
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_sample, 10);
}

// ADC处理函数,用于比较哪一环被打中
uint8_t Bsp_ADC_Detect(void) {
	uint8_t current_mask = Display_Disable;
	uint8_t max_ring = 0;

	// 找出最高环号
	for (int i = 0; i < 10; i++) {
		if (adc_sample[i] > ADC_THRESHOLD) {
			uint8_t current_ring = index_to_ring[i];
			if (current_ring > max_ring) {
				max_ring = current_ring;
			}
		}
	}

	// 将环号转换为位掩码
	if (max_ring > 0) {
		switch(max_ring) {
			case 1: current_mask = Target_Ring_10; break;
			case 2: current_mask = Target_Ring_9; break;
			case 3: current_mask = Target_Ring_8; break;
			case 4: current_mask = Target_Ring_7; break;
			case 5: current_mask = Target_Ring_6; break;
			case 6: current_mask = Target_Ring_5; break;
			case 7: current_mask = Target_Ring_4; break;
			case 8: current_mask = Target_Ring_3; break;
			case 9: current_mask = Target_Ring_2; break;
			case 10: current_mask = Target_Ring_1; break;
			default:break;
		}
	}

	return current_mask;
}

// 在中断中处理的函数
void Bsp_ADC_Process(void) {
	if(timer < TIMER_THRESHOLD){
		return;
	}
	uint16_t id = CAN_BASE_ID + EM_ID;
	uint8_t tx_data[8] = {0};
	uint8_t current_mask = Bsp_ADC_Detect();
	// 比较当前掩码与上次掩码
	if (current_mask != 0) {
		
		tx_data[0] = current_mask;
		Bsp_CAN_SendMsg(&hcan, id, tx_data);
		//更新上次掩码
		last_target_mask = current_mask;
		timer = 0;
	}
}

