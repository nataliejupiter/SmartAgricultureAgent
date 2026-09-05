#ifndef __JW01_H_
#define __JW01_H_

extern uint8_t Usart1_RxPacket[6];				
extern uint8_t Usart1_RxFlag;

void JW01_Init(uint32_t baudRate);
void USART1_IRQHandler();
void  CO2GetData(uint16_t *data);
#endif