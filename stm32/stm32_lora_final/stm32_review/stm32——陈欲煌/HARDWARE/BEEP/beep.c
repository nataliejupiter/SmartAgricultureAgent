#include "delay.h"
#include "hdc1080.h"
#include "lcd.h"
#include "TS.h"
#include "adc.h"
#include <stdio.h>
// 温度设定范围
#define TEMP_UPPER_LIMIT 25  // 温度上限（单位：摄氏度）
#define TEMP_LOWER_LIMIT 10  // 温度下限（单位：摄氏度）

// 定义湿度范围
#define HUMI_UPPER_LIMIT 100  // 湿度上限
#define HUMI_LOWER_LIMIT 20  // 湿度下限


// 定义水位范围
#define SHUIWEI_UPPER_LIMIT 12  // 水位上限
#define SHUIWEI_LOWER_LIMIT 5  // 水位下限
void BEEP_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
	//GPIO_SetBits(GPIOF,GPIO_Pin_8);//GPIOF9,F10设置高，灯灭
}


void beep_control(void)
{
    u16 temp, humi;
    uint8_t beep_active = 0;  // 蜂鸣器状态标志：0-关闭，1-打开

    while (1)
    {
        // 读取温湿度数据
        Convert_HDC1080_TempHumidity(&temp, &humi);

        // 判断温度是否超出设定范围
        if (temp > TEMP_UPPER_LIMIT || temp < TEMP_LOWER_LIMIT)
        {
            if (!beep_active)  // 如果蜂鸣器未启动
            {
                // 打开蜂鸣器
                GPIO_SetBits(GPIOF, GPIO_Pin_8);  // 设置GPIO引脚为高电平
                beep_active = 1;  // 设置蜂鸣器状态为打开
                printf("[ALERT] Beep ON - Temperature out of range: %d°C\r\n", temp);  // 打印调试信息
            }
        }
        else  // 温度回到范围内
        {
            if (beep_active)  // 如果蜂鸣器正在运行且温度回到范围内
            {
                // 关闭蜂鸣器
                GPIO_ResetBits(GPIOF, GPIO_Pin_8);  // 设置GPIO引脚为低电平
                beep_active = 0;  // 设置蜂鸣器状态为关闭
                printf("[INFO] Beep OFF - Temperature back to range: %d°C\r\n", temp);  // 打印调试信息
            }
        }

        // 每5秒打印一次当前温度数据
        printf("[DATA] Current Temperature: %d°C\r\n", temp);

        // 延时5秒（5,000毫秒）
        delay_ms(5000);
    }
}

// 蜂鸣器控制函数
void beep_control1(void)
{
    u16 humi;  // 湿度值
    uint8_t beep_active = 0;  // 蜂鸣器状态标志：0-关闭，1-打开

    while (1)
    {
        // 读取湿度数据
        humi = TS_GetData(5, 20);  // 假设通道 5 用于读取湿度

        // 判断湿度是否超出设定范围
        if (humi > HUMI_UPPER_LIMIT || humi < HUMI_LOWER_LIMIT)
        {
            if (!beep_active)  // 如果蜂鸣器未启动
            {
                // 打开蜂鸣器
                GPIO_SetBits(GPIOF, GPIO_Pin_8);  // 设置 GPIO 引脚为高电平
                beep_active = 1;  // 设置蜂鸣器状态为打开
                printf("[ALERT] Beep ON - Humidity out of range: %d%%\r\n", humi);  // 打印调试信息
            }
        }
        else  // 湿度回到范围内
        {
            if (beep_active)  // 如果蜂鸣器正在运行且湿度回到范围内
            {
                // 关闭蜂鸣器
                GPIO_ResetBits(GPIOF, GPIO_Pin_8);  // 设置 GPIO 引脚为低电平
                beep_active = 0;  // 设置蜂鸣器状态为关闭
                printf("[INFO] Beep OFF - Humidity back to range: %d%%\r\n", humi);  // 打印调试信息
            }
        }

        // 每5秒打印一次当前湿度数据
        printf("[DATA] Current Humidity: %d%%\r\n", humi);

        // 延时5秒（5,000毫秒）
        delay_ms(5000);
    }
}


// 蜂鸣器控制函数
void beep_control2(void)
{
    u16 shuiwei;  // 湿度值
    uint8_t beep_active = 0;  // 蜂鸣器状态标志：0-关闭，1-打开

    while (1)
    {
        // 读取湿度数据
        shuiwei=Get_Adc_Average(ADC_Channel_3,20);

        // 判断湿度是否超出设定范围
        if (shuiwei > SHUIWEI_UPPER_LIMIT || shuiwei <SHUIWEI_LOWER_LIMIT)
        {
            if (!beep_active)  // 如果蜂鸣器未启动
            {
                // 打开蜂鸣器
                GPIO_SetBits(GPIOF, GPIO_Pin_8);  // 设置 GPIO 引脚为高电平
                beep_active = 1;  // 设置蜂鸣器状态为打开
                printf("[ALERT] Beep ON - shuiwei out of range: %d%%\r\n", shuiwei);  // 打印调试信息
            }
        }
        else  // 湿度回到范围内
        {
            if (beep_active)  // 如果蜂鸣器正在运行且湿度回到范围内
            {
                // 关闭蜂鸣器
                GPIO_ResetBits(GPIOF, GPIO_Pin_8);  // 设置 GPIO 引脚为低电平
                beep_active = 0;  // 设置蜂鸣器状态为关闭
                printf("[INFO] Beep OFF - shuiwei back to range: %d%%\r\n", shuiwei);  // 打印调试信息
            }
        }

        // 每5秒打印一次当前湿度数据
        printf("[DATA] Current Humidity: %d%%\r\n", shuiwei);

        // 延时5秒（5,000毫秒）
        delay_ms(5000);
    }
}
