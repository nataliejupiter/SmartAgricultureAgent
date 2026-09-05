#include "stm32f4xx.h"                  // Device header

uint8_t Usart1_RxPacket[6];				//定义接收数据包数组
uint8_t Usart1_RxFlag;					//定义接收数据包标志位

/**
  * 函    数：JW01初始化
  * 参    数：波特率
  * 返 回 值：无
  */
void JW01_Init(uint32_t baudRate)
{

    // 1. 使能 GPIOA 和 USART1 时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // 2. 配置 TX 引脚 PA9 复用推挽输出
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 配置 RX 引脚 PA10 浮空输入
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 4. 将 PA9/PA10 复用功能映射到 USART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9,  GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    // 5. 配置 USART1 串口参数
    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate            = baudRate;
    USART_InitStructure.USART_WordLength          = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits            = USART_StopBits_1;//1位停止位
    USART_InitStructure.USART_Parity              = USART_Parity_No;//无校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//关闭流控
    USART_InitStructure.USART_Mode                = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    // 6. 配置中断优先级
    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 7. 使能接收中断
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    // 8. 使能 USART1
    USART_Cmd(USART1, ENABLE);

}

void USART1_IRQHandler()     //串口1中断服务函数，串口1接收到数据进入此函数
{
	uint8_t Res;             //用来暂时存放接收的数据
	static uint8_t RxState = 0;   //当前状态机状态
	static uint8_t pRxPacket =0;  //当前接受数据位置
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) //接收中断
	{
		Res=USART_ReceiveData(USART1);   //读取接收到的数据
		switch (RxState)
		{
			case 0:
				if (Res == 0x2C) //如果接收到的数据是二氧化碳传感器发送数据的第一位
					{
						Usart1_RxPacket[pRxPacket] = Res;	//将数据存入数组
						pRxPacket++;     //数组下标加一
						RxState = 1;     //状态机进入状态1
					}
				else
					{
						pRxPacket = 0;
						RxState = 0;
					}
					break;
			case 1:
					Usart1_RxPacket[pRxPacket] = Res;	//将数据存入数组
					pRxPacket++;
					if(pRxPacket >= 6)
					{
						pRxPacket = 0;
						RxState = 2;
					}
					break;
			case 2:
					if (Usart1_RxPacket[5] == (uint8_t)(Usart1_RxPacket[0] + Usart1_RxPacket[1]	//验证接收到的数据是否正确
						+ Usart1_RxPacket[2] + Usart1_RxPacket[3] + Usart1_RxPacket[4]))
					{
						
						RxState = 0;
						pRxPacket = 0;
						Usart1_RxFlag = 1;		//接收数据包标志位置1，成功接收一个数据包
					}
					else
					{
						pRxPacket = 0;
						RxState = 0;
					}
					break;
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);		//清除标志位
	}
}

void  CO2GetData(uint16_t *data)     //读取
{
	if (Usart1_RxFlag == 1)
	{
		Usart1_RxFlag = 0;
		*data = Usart1_RxPacket[1] * 256 + Usart1_RxPacket[2];
	}
}
