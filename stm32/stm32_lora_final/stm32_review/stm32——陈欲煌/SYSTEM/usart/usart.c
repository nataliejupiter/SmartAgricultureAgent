#include "sys.h"
#include "usart.h"	
#include "include.h"

#if SYSTEM_SUPPORT_OS
#include "includes.h"	
#endif

#if 1
#pragma import(__use_no_semihosting)             
              
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
  
void _sys_exit(int x) 
{ 
	x = x; 
} 

// 重定向printf，printf底层是调用fputc这个函数的
//int fputc(int ch, FILE *f)
//{ 	
//	while((USART1->SR&0X40)==0);  // USART2已给LoRa，printf改用USART1
//	USART1->DR = (u8) ch;      
//	return ch;
//}
#endif
 


u16 temperature,humidity,phValue,waterLevel;
#define BUFFER_SIZE 100
 uint8_t packet[10];
 uint8_t i;

void sendPacket(USART_TypeDef *USARTx, uint8_t *data, uint8_t dataLength) {

    packet[0] = 0xaf;
    packet[1] = dataLength;
    for (i = 0; i < dataLength; i++) {
        packet[i + 2] = data[i];
    }
    packet[dataLength + 2] = 0xfe;

    for ( i = 0; i < dataLength + 3; i++) {
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
        USART_SendData(USARTx, packet[i]);
    }
}


void sendExampleData(USART_TypeDef *USARTx)
	{
		u8 *data;
		Read_Temp_Humi_Reg(data);
		Get_Adc_Average(ADC_Channel_3,20);
		TS_GetData1(5, 20);
		u8 high;
		u8 low;
		u8 high_byte;
		u8 low_byte;
		uint8_t dataToSend[] = {data[0],data[1],high, low,0x02,0x05,high_byte,low_byte};
		sendPacket(USARTx, dataToSend, sizeof(dataToSend));
}


//void sendstm32Packet(USART_TypeDef *USARTx) {
//    uint8_t data[8];  
//    uint8_t dataLength = 8;
//    uint8_t packet[dataLength + 3];  
//    uint8_t i;  

//	temperature=envir_data1.temperature;
//	humidity=envir_data1.wet;
//	phValue =envir_data1.ph;
//	waterLevel=envir_data1.water_level;
//    data[0] = (temperature >> 8) & 0xff;
//    data[1] = temperature & 0xff;
//    data[2] = (humidity >> 8) & 0xff;
//    data[3] = humidity & 0xff;
//    data[4] = (phValue >> 8) & 0xff;
//    data[5] = phValue & 0xff;
//    data[6] = (waterLevel >> 8) & 0xff;
//    data[7] = waterLevel & 0xff;

//   
//    packet[0] = 0xaf;  
//    packet[1] = dataLength;
//    for (i = 0; i < dataLength; i++) {
//        packet[i + 2] = data[i];
//    }
//    packet[dataLength + 2] = 0xfe;  

//    
//    for (i = 0; i < dataLength + 3; i++) {
//        while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);
//        USART_SendData(USARTx, packet[i]);
//		LCD_ShowString(100, 310, 72, 20, 24, "send data success!");
//    }
//}


void LoRA_Init(u32 bound) {
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);  // LoRa M0/M1/AUX引脚时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

    GPIO_InitStruct.GPIO_Pin = LORA_M0_PIN | LORA_M1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(LORA_GPIO_PORT, &GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = LORA_AUX_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_Init(LORA_GPIO_PORT,&GPIO_InitStruct);

    USART_InitStruct.USART_BaudRate = bound;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_Init(USART2, &USART_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE);

    LoRA_SetMode(LORA_MODE_NORMAL);
}


void LoRA_SetMode(LoRaMode mode) {
    switch(mode) {
        case LORA_MODE_NORMAL:
            GPIO_ResetBits(LORA_GPIO_PORT, LORA_M0_PIN);
            GPIO_ResetBits(LORA_GPIO_PORT, LORA_M1_PIN);
            break;
        case LORA_MODE_WAKE_UP:
            GPIO_SetBits(LORA_GPIO_PORT, LORA_M0_PIN);
            GPIO_ResetBits(LORA_GPIO_PORT, LORA_M1_PIN);
            break;
        case LORA_MODE_POWER_SAVE:
            GPIO_ResetBits(LORA_GPIO_PORT, LORA_M0_PIN);
            GPIO_SetBits(LORA_GPIO_PORT, LORA_M1_PIN);
            break;
        case LORA_MODE_SLEEP:
            GPIO_SetBits(LORA_GPIO_PORT, LORA_M0_PIN);
            GPIO_SetBits(LORA_GPIO_PORT, LORA_M1_PIN);
            break;
    }
    // 等待AUX引脚拉高确认模式切换完成（E22手册要求）
    {
        uint32_t tout = 100000;
        while (GPIO_ReadInputDataBit(LORA_GPIO_PORT, LORA_AUX_PIN) == RESET)
        {
            if (--tout == 0) break;
        }
    }
}

// AUX就绪等待，带超时保护
static uint8_t LoRA_WaitAuxReady(uint32_t timeout_ms)
{
    while (GPIO_ReadInputDataBit(LORA_GPIO_PORT, LORA_AUX_PIN) == RESET)
    {
        if (timeout_ms == 0) return 0;
        timeout_ms--;
        delay_ms(1);
    }
    return 1;
}



void LoRA_SendData(uint8_t *data, uint16_t length) { 
	if (!LoRA_WaitAuxReady(100)) return; // 等待AUX就绪，超时100ms则放弃 
	for(uint16_t i = 0; i < length; i++) { 
		while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); 
			USART_SendData(USART2, data[i]); 
	} 
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET); 
	LoRA_WaitAuxReady(500);
}



// 这个函数是多余的，因为收到数据直接到中断里面
//uint8_t LoRA_ReceiveData(uint8_t *buffer, uint16_t max_length) {
//    uint16_t count = 0;
//    while(USART_GetFlagStatus(USART2, USART_FLAG_RXNE) != RESET && count < max_length) {
//        buffer[count++] = USART_ReceiveData(USART2);
//    }
//    return count;
//}

#define LORA_RX_BUFFER_SIZE 128
volatile uint8_t LORA_RX_BUF[LORA_RX_BUFFER_SIZE] = {0};
volatile uint8_t LORA_RX_CNT = 0;
volatile uint8_t LORA_RX_Flag = 0;


// USART2 接收中断处理函数（LoRa 数据接收）
void USART2_IRQHandler(void)
{
    uint8_t data;
    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        data = USART_ReceiveData(USART2);
        if (LORA_RX_CNT < LORA_RX_BUFFER_SIZE)
        {
            LORA_RX_BUF[LORA_RX_CNT++] = data;
        }
        if (data == 0xFE)  // 帧尾
        {
            LORA_RX_Flag = 1;
        }
        USART_ClearITPendingBit(USART2, USART_IT_RXNE);
    }
}







