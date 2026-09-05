#include "TS.h"
//#include "adc.h"


void TS_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //使能ADC1时钟
		GPIO_InitStructure.GPIO_Pin = TS_GPIO_PIN;					// 配置 ADC IO 引脚模式
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;		// 设置为模拟输入
		
		GPIO_Init(TS_GPIO_PORT, &GPIO_InitStructure);				// 初始化 ADC IO

		Adc_Init();
}

//uint16_t TS_ADC_Read(void)
//{
//	//设置指定ADC的规则组通道，采样时间
//	return Get_Adc(1, ADC_SampleTime_480Cycles);
//}

//uint16_t TS_GetData(void)
//{
//	uint32_t  tempData = 0;
//	for(u8 i = 0; i < TS_READ_TIMES; i++)
//	{
//		tempData += TS_ADC_Read();
//		delay_ms(5);
//	}

//	tempData /= TS_READ_TIMES;
//	return 100 - (float)tempData/40.96;
//}

u16 TS_GetData(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	temp_val /= times;
	return 100 - (float)temp_val/40.96;
} 

// 假设Get_Adc函数返回一个u16类型的值与湿度相关
u16 TS_GetData1(u8 ch, u8 times)
{
    u16 temp_val = 0;
    u8 t;
    for (t = 0; t < times; t++)
    {
        temp_val += Get_Adc(ch);
        delay_ms(5);
    }
    temp_val /= times;
    // 获取高8位
    u8 high_byte = (u8)(temp_val >> 8);
    // 获取低8位
    u8 low_byte = (u8)(temp_val & 0xFF);
    // 这里可以根据实际需求对high_byte和low_byte进行进一步处理或者直接返回
    // 如果要返回一个包含高8位和低8位的结构体，可以定义如下结构体并返回
    typedef struct {
        u8 high;
        u8 low;
    } HumidityBytes;
    HumidityBytes result = {high_byte, low_byte};
    return *(u16*)&result;
}
	 
//uint16_t TS_GetData(int times)
//{
//    uint32_t H_all = 0;
//    float H_arg = 0;
//    uint8_t t;
// 
//    // 进行多次ADC转换并累加
//    for (t = 0; t < times; t++) {
//        H_all += Get_Adc(ch);
//        Delay_ms(1); // 延时1毫秒
//    }
//    // 计算平均值
//    H_arg = (H_all / times);
//    // 根据转换公式计算湿度值
//    uint16_t data = (4095 - H_arg) / 3292 * 100;
//    // 确保湿度值在合理范围内（0~100）
//    data = data > 100 ? 100 : (data < 0 ? 0 : data);
//    return data;
//}
