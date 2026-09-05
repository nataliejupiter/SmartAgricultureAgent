#ifndef __YL-69_H
#define __YL-69_H

#include "stm32f4xx.h"   

// 引脚配置：AO 接 PA4 (ADC1 通道4)
#define SM_ADC_CHANNEL    ADC_Channel_4
#define SM_GPIO_PORT      GPIOA
#define SM_GPIO_PIN       GPIO_Pin_4
#define SM_GPIO_CLK       RCC_AHB1Periph_GPIOA

// 极值校准
#define SM_ADC_DRY        4000   // 空气中读数
#define SM_ADC_WET        500   // 水中读数

// 采样次数
#define SM_SAMPLE_TIMES   10

// 外部接口
void SoilMoisture_Init(void);
uint16_t SoilMoisture_GetPercent(void);

#endif
