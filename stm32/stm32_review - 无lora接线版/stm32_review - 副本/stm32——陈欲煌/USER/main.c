#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "adc.h"
#include "HDC1080.h"
#include "DHT11.h"
#include "myiic.h"
#include "beep.h"
#include "TS.h"
#include "include.h"
#include "image.h"
#include "JW01.h"     // 二氧化碳传感器
#include "YL-69.h"    // 土壤湿度


u16 CO2 = 0;
u8 temp = 0, humi = 0;
uint16_t light_raw;
uint8_t light_percent;
u8 shidu = 0;          // 土壤湿度百分比
u16 shuiwei = 0;        
// u16 ph_value = 0;

envir_data envir_data1 = {0};  // 

// USART3 接收相关（PH值等）
#define RX_BUFFER_SIZE 64
volatile uint8_t USART3_RX_BUF[RX_BUFFER_SIZE] = {0};
volatile uint8_t USART3_RX_CNT = 0;
volatile uint8_t USART3_RX_Flag = 0;

// 光照采样次数
#define SAMPLE_TIMES 10


uint16_t Get_Light_Single(void);
uint16_t Get_Light_Stable(void);
void Send_Data_To_Host(void);
void USART2_Init(u32 bound);

// =============== 光照传感器 ===============
uint16_t Get_Light_Single(void)
{
    return Get_Adc(5);   // PA5 通道
}

uint16_t Get_Light_Stable(void)
{
    uint32_t sum = 0;
    for (uint8_t i = 0; i < SAMPLE_TIMES; i++)
    {
        sum += Get_Light_Single();
        delay_ms(3);
    }
    return (uint16_t)(sum / SAMPLE_TIMES);
}

// =============== USART2 初始化（用于 printf 和向上位机发送） ===============
void USART2_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    // TX: PA2, RX: PA3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART2, &USART_InitStructure);

    USART_Cmd(USART2, ENABLE);
}

// 重定向 printf 到 USART2（避免冲突 USART1）
//int fputc(int ch, FILE *f)
//{
    //while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    //USART_SendData(USART2, (uint8_t)ch);
    //return ch;
//}

// =============== USART3 初始化 ===============
void USART3_Init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // TX PB10 (可不用)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);

    // RX PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_Mode = USART_Mode_Rx;   // 只收
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART3, &USART_InitStructure);

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE);
}

// USART3 中断服务函数
void USART3_IRQHandler(void)
{
    static uint8_t state = 0;
    uint8_t data;

    if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART3);

        switch (state)
        {
        case 0:
            if (data == 0xAA)
            {
                USART3_RX_CNT = 0;
                USART3_RX_BUF[USART3_RX_CNT++] = data;
                state = 1;
            }
            break;

        case 1:
            USART3_RX_BUF[USART3_RX_CNT++] = data;
            if (USART3_RX_CNT >= 4)
            {
                if (USART3_RX_BUF[3] == 0xBB)
                {
                    USART3_RX_Flag = 1;
                }
                state = 0;
            }
            break;
        }
        USART_ClearITPendingBit(USART3, USART_IT_RXNE);
    }
}

// 解析 PH 值
//uint16_t Parse_PH_Value(void)
//{
//    if (USART3_RX_Flag)
//    {
//        uint16_t ph_value = (USART3_RX_BUF[1] << 8) | USART3_RX_BUF[2];
//        USART3_RX_Flag = 0;
//        return ph_value;
//    }
//    return 0xFFFF;
//}

// =============== 向上位机发送数据帧（通过 USART2） ===============
void Send_Data_To_Host(void)
{
    uint8_t frame[16];
    // uint8_t checksum;
    uint8_t i;

    // 帧格式：0xAF + +1数据长度 + 6字节数据  + 0xFE
    // 数据：CO2(2) + temp(1) + humi(1) + light_percent(1) + soil_humi(1) 
    frame[0] = 0xAF;
	frame[1] = 6; // 数据长度
    frame[2] = (CO2 >> 8) & 0xFF;
    frame[3] = CO2 & 0xFF;
    frame[4] = temp;
    frame[5] = humi;
    frame[6] = light_percent;
    frame[7] = shidu;
    // frame[8] = (ph_value>>8)&0xFF;  // 保留
    // frame[9] = ph_value&0xFF;

    // 计算校验和（所有数据字节低8位累加）
//    checksum = 0;
//    for (i = 1; i <= 10; i++)
//        checksum += frame[i];
//    frame[11] = checksum;

    frame[8] = 0xFE;

    // 发送整个帧
    for (i = 0; i < 9; i++)
    {
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        USART_SendData(USART2, frame[i]);
    }
}

// =============== 主函数 ===============
int main(void)
{
    // 系统初始化
    delay_init(168);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   

    // 初始化各个外设
    Adc_Init();
    JW01_Init(9600);          // USART1 接收 CO2
    USART2_Init(115200);      // 调试 printf 及向上位机发送
    USART3_Init(9600);        // 接收 PH 等下位机数据
    SoilMoisture_Init();      // 初始化土壤湿度 ADC 引脚
    LCD_Init();
    //LCD_ShowPicture(0, 0, 317, 300, (u16*)image);

    // DHT11 初始化
    uint8_t retry = 5;
    while (DHT11_Init() && retry--)
    {
        printf("DHT11 init fail, retry...\r\n");
        delay_ms(1000);
    }
    if (retry == 0)
    {
        printf("DHT11 error!\r\n");
    }

    while (1)
    {
        // 1. 读取光照
        light_raw = Get_Light_Stable();
        light_percent = (light_raw * 100) / 4095;   

        // 2. 读取土壤湿度
        shidu = SoilMoisture_GetPercent();

        // 3. 读取 CO2
        CO2GetData(&CO2);

        // 4. 读取温湿度
        DHT11_Read_Data(&temp, &humi);

        // 5. 可选：读取 PH 值
        // ph_value = Parse_PH_Value();

        // 6. 更新 LCD 显示（带单位）
        LCD_ShowString(30, 120, 72, 20, 24, "CO2:");
        LCD_ShowNum(200, 120, CO2, 3, 24);
        LCD_ShowString(240, 120, 50, 20, 24, "ppm");

        LCD_ShowString(30, 160, 128, 20, 24, "Temp:");
        LCD_ShowNum(200, 160, temp, 3, 24);
        LCD_ShowString(240, 160, 30, 20, 24, "C");

        LCD_ShowString(30, 200, 128, 20, 24, "Humi:");
        LCD_ShowNum(200, 200, humi, 3, 24);
        LCD_ShowString(240, 200, 30, 20, 24, "%");

        LCD_ShowString(30, 240, 128, 20, 24, "Light:");
        LCD_ShowNum(200, 240, light_percent, 3, 24);
        LCD_ShowString(240, 240, 30, 20, 24, "%");

        LCD_ShowString(30, 280, 128, 20, 24, "Soil:");
        LCD_ShowNum(200, 280, shidu, 3, 24);
        LCD_ShowString(240, 280, 30, 20, 24, "%");
		
//		LCD_ShowString(30, 550, 128, 20, 24, "PH:");
//        if (ph_value == 0xFFFF)
//        {
//            LCD_ShowString(200, 550, 50, 20, 24, "---");
//        }
//        else
//        {
//            LCD_ShowNum(200, 550, ph_value, 5, 24);   // 
//        }

        // 7. 向上位机发送数据帧
        Send_Data_To_Host();

        delay_ms(500);   // 
    }
}