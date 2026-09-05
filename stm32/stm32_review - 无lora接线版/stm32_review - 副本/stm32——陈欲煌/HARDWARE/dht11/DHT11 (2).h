#ifndef _DHT11__H_
#define _DHT11__H_
#include "sys.h"
 
 
//IO方向设置
//IO方向是通过位段设置的，调用GPIO模式寄存器，以下代码已经多次使用，如有不理解，可回头温习DS18B20的实验代码
#define DHT11_IO_IN() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=0<<9*2;}	//PG9输入模式
#define DHT11_IO_OUT() {GPIOG->MODER&=~(3<<(9*2));GPIOG->MODER|=1<<9*2;} 	//PG9输出模式 
 
//IO引脚设置
#define DHT11_DQ_OUT PGout(9)  //PG9输出
#define DHT11_DQ_IN PGin(9)    //PG9输入
 
 
void DHT11_Reset(void);
u8 DHT11_CheckExist(void);
u8 DHT11_Read_Bit(void);
u8 DHT11_Read_Byte(void);
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity);
u8 DHT11_Init(void);
 
#endif 
