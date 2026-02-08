#ifndef STM32F334_NEW_HUB75_CONFIG_H
#define STM32F334_NEW_HUB75_CONFIG_H
// ADC的阈值
#define THRESHOLD 200
// 符叶ID,范围3-7
#define EM_ID				0x07
#define CAN_BASE_ID			0x400
#define SMALL_EM			0xAA
#define BIG_EM				0xBB
#define Display_Disable		0x00
#define Target_Ring_1		0x01
#define Target_Ring_2		0x02
#define Target_Ring_3		0x03
#define Target_Ring_4		0x04
#define Target_Ring_5		0x05
#define Target_Ring_6		0x06
#define Target_Ring_7		0x07
#define Target_Ring_8		0x08
#define Target_Ring_9		0x09
#define Target_Ring_10		0x0A
#define Energy_Mechanism	0xA0
// 颜色定义
typedef enum {
	COLOR_RED = 0xC0,
	COLOR_GREEN,
	COLOR_BLUE,
} Color_t;
#endif //STM32F334_NEW_HUB75_CONFIG_H