#include "stm32f4xx.h"
#include "delay.h"


#define LORA_M0_PIN GPIO_Pin_4
#define LORA_M1_PIN GPIO_Pin_5
#define LORA_GPIO_PORT GPIOB


void LoRa_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);


    GPIO_InitStruct.GPIO_Pin = LORA_M0_PIN | LORA_M1_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;

    GPIO_Init(LORA_GPIO_PORT,&GPIO_InitStruct);


    // 普通透明传输模式
    GPIO_ResetBits(LORA_GPIO_PORT,LORA_M0_PIN);
    GPIO_ResetBits(LORA_GPIO_PORT,LORA_M1_PIN);
}



void LoRa_UART2_Init(uint32_t baud)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    USART_InitTypeDef USART_InitStruct;


    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);



    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    GPIO_Init(GPIOA,&GPIO_InitStruct);



    GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2);



    USART_InitStruct.USART_BaudRate = baud;
    USART_InitStruct.USART_WordLength = USART_WordLength_8b;
    USART_InitStruct.USART_StopBits = USART_StopBits_1;
    USART_InitStruct.USART_Parity = USART_Parity_No;
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;


    USART_Init(USART2,&USART_InitStruct);


    USART_Cmd(USART2,ENABLE);
}



void LoRa_SendString(char *str)
{
    while(*str)
    {
        while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);

        USART_SendData(USART2,*str++);
    }


    while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET);
}

int main(void)
{
    delay_init(168);


    LoRa_GPIO_Init();

    LoRa_UART2_Init(9600);


    while(1)
    {
        LoRa_SendString("hello\r\n");

        delay_ms(1000);
    }
}
