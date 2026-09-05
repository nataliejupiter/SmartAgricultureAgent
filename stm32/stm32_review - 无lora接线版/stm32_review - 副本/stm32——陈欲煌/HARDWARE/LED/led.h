#ifndef __LED_H
#define __LED_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	


//LED端口定义
#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1	

#define DS1302_SCK_PIN  GPIO_Pin_12
#define DS1302_SCK_GPIO_Port GPIOB



#define DS1302_CE_PIN GPIO_Pin_6
#define DS1302_CE_GPIO_Port GPIOA

#define DS1302_DATA_PIN GPIO_Pin_7
#define DS1302_DATA_GPIO_Port GPIOA
 
#define GG_PIN GPIO_Pin_1
#define GG_GPIO_Port GPIOA

#define DS1302_SCK(x) GPIO_WriteBit(DS1302_SCK_GPIO_Port,DS1302_SCK_PIN,(BitAction)x);
#define DS1302_CE(x) GPIO_WriteBit(DS1302_CE_GPIO_Port,DS1302_CE_PIN,(BitAction)x);
#define DS1302_DATA(x) GPIO_WriteBit(DS1302_DATA_GPIO_Port,DS1302_DATA_PIN,(BitAction)x);
#define DS1302_ReadDATA GPIO_ReadInputDataBit(DS1302_DATA_GPIO_Port,DS1302_DATA_PIN)

struct TIMEData
{
	u16 year;
	u8  month;
	u8  day;
	u8  hour;
	u8  minute;
	u8  second;
	u8  week;
};//创建TIMEData结构体方便存储时间日期数据
extern struct TIMEData TimeData;//全局变量

void ds1302_gpio_init(void);//CE,SCLK端口初始化
void ds1032_DATAOUT_init(void);//配置双向I/O端口为输出态
void ds1032_DATAINPUT_init(void);//配置双向I/O端口为输入态
void ds1302_write_onebyte(u8 data);//向ds1302发送一字节数据
void ds1302_wirte_rig(u8 address,u8 data);//向指定寄存器写一字节数据
u8 ds1302_read_rig(u8 address);//从指定寄存器读一字节数据
void Water_time(u8 minute,u8 hour,u8 cha,u8 guan);
void ds1032_init(u8 hour,u8 minute);

void LED_Init(void);//初始化		 				    
#endif
