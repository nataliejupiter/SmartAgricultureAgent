#include "stm32f4xx.h"                  // Device header
#include "YL-69.h"
#include "delay.h"       // 总系统的延时函数
#include "adc.h"         // 总系统的 ADC 头文件（里面有 Get_Adc_Average 等）

void SoilMoisture_Init(void)
{
  	RCC_AHB1PeriphClockCmd(SM_GPIO_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SM_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(SM_GPIO_PORT, &GPIO_InitStructure);
}

uint16_t SoilMoisture_GetPercent(void)
{
    uint32_t sum = 0;
    uint16_t avg;
    uint16_t humidity;
    
    for (uint8_t i = 0; i < SM_SAMPLE_TIMES; i++) {
        sum += Get_Adc_Average(SM_ADC_CHANNEL, 1);  // 每次读1次，循环累计
        delay_ms(5);
    }
    avg = sum / SM_SAMPLE_TIMES;
    
    // 限制范围
    if (avg > SM_ADC_DRY) avg = SM_ADC_DRY;
    if (avg < SM_ADC_WET) avg = SM_ADC_WET;
    
    // 反向计算湿度
    humidity = (uint32_t)(SM_ADC_DRY - avg) * 100 / (SM_ADC_DRY - SM_ADC_WET);
    return humidity;
}
