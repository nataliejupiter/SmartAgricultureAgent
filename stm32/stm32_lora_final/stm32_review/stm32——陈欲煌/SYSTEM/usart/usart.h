#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "stm32f4xx_conf.h"
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.csom
//修改日期:2011/6/14
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	


#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define LORA_UART USART2
#define LORA_BAUDRATE 9600

#define LORA_M0_PIN GPIO_Pin_8
#define LORA_M1_PIN GPIO_Pin_9
#define LORA_AUX_PIN GPIO_Pin_7
#define LORA_GPIO_PORT GPIOB
	  	
typedef enum {
    WAITING_FOR_HEADER,
    RECEIVING_LENGTH,
    RECEIVING_DATA,
    WAITING_FOR_TAIL
} ReceiveState;

// lora四种工作模式
typedef enum {
    LORA_MODE_NORMAL = 0x00,
    LORA_MODE_WAKE_UP = 0x01,
    LORA_MODE_POWER_SAVE = 0x02,
    LORA_MODE_SLEEP = 0x03
} LoRaMode;

void LoRA_Init(u32 bound);
void LoRA_SetMode(LoRaMode mode);
void LoRA_SendData(uint8_t *data, uint16_t length);
uint8_t LoRA_ReceiveData(uint8_t *buffer, uint16_t max_length);

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	

//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void sendPacket(USART_TypeDef *USARTx, uint8_t *data, uint8_t dataLength) ;
void receivePacket(USART_TypeDef *USARTx, uint8_t receivedByte);
void sendExampleData(USART_TypeDef *USARTx);
void sendstm32Packet(USART_TypeDef *USARTx);
//void USART3_Init(u32 bound);
#endif


