#include "led.h" 
#include "delay.h"
#include "hdc1080.h"
#include "lcd.h"
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

//初始化PF9和PF10为输出口.并使能这两个口的时钟		    
//LED IO初始化

u8 clock[5];


void LED_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOF时钟

  //GPIOF9,F10初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10设置高，灯灭
}

void ds1302_gpio_init()//CE,SCLK端口初始化
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟

	GPIO_InitStructure.GPIO_Pin = DS1302_CE_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//下拉
	GPIO_Init(DS1302_CE_GPIO_Port, &GPIO_InitStructure);//初始化
	GPIO_ResetBits(DS1302_CE_GPIO_Port,DS1302_CE_PIN);
	
	GPIO_InitStructure.GPIO_Pin = DS1302_SCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(DS1302_SCK_GPIO_Port, &GPIO_InitStructure);//初始化
	GPIO_ResetBits(DS1302_SCK_GPIO_Port,DS1302_SCK_PIN);
	
	GPIO_InitStructure.GPIO_Pin = GG_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GG_GPIO_Port, &GPIO_InitStructure);//初始化
	GPIO_ResetBits(GG_GPIO_Port,GG_PIN);
}

void ds1032_DATAOUT_init()//配置双向I/O端口为输出态
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
	 
	GPIO_InitStructure.GPIO_Pin = DS1302_DATA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(DS1302_DATA_GPIO_Port, &GPIO_InitStructure);//初始化
	GPIO_ResetBits(DS1302_DATA_GPIO_Port,DS1302_DATA_PIN);
}

void ds1032_DATAINPUT_init()//配置双向I/O端口为输入态
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOB时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOC时钟
	
	GPIO_InitStructure.GPIO_Pin = DS1302_DATA_PIN; //KEY0 对应引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(DS1302_DATA_GPIO_Port, &GPIO_InitStructure);//初始化GPIOE4
}

void ds1302_write_onebyte(u8 data)//向DS1302发送一字节数据
{
	ds1032_DATAOUT_init();
	u8 count=0;
	DS1302_SCK(0);
	for(count=0;count<8;count++)
	{	DS1302_SCK(0);
		if(data&0x01)
		{DS1302_DATA(1);}
		else{DS1302_DATA(0);}//先准备好数据再发送
		DS1302_SCK(1);//拉高时钟线，发送数据
		data>>=1;
	}
}

void ds1302_wirte_rig(u8 address,u8 data)//向指定寄存器地址发送数据
{
	u8 temp1=address;
	u8 temp2=data;
	DS1302_CE(0);DS1302_SCK(0);delay_us(1);
	DS1302_CE(1);delay_us(2);
	ds1302_write_onebyte(temp1);
	ds1302_write_onebyte(temp2);
	DS1302_CE(0);DS1302_SCK(0);delay_us(2);
}


u8 ds1302_read_rig(u8 address)//从指定地址读取一字节数据
{
	u8 temp3=address;
	u8 count=0;
	u8 return_data=0x00;
	DS1302_CE(0);DS1302_SCK(0);delay_us(3);
	DS1302_CE(1);delay_us(3);
	ds1302_write_onebyte(temp3);//写入要读的地址
	ds1032_DATAINPUT_init();//配置I/O口为输入
	delay_us(2);
	for(count=0;count<8;count++)
		{
			delay_us(2);//使电平持续一段时间
			DS1302_SCK(1);delay_us(4);//使高电平持续一段时间
			DS1302_SCK(0);delay_us(14);//延时14us后再去读取电压，更加准确
			if(DS1302_ReadDATA)
			{
				return_data=return_data|(0x01<<count);
			}
		
		}
	delay_us(2);
	DS1302_CE(0);DS1302_DATA(0);
	return return_data;
}



void Water_time(u8 minute,u8 hour,u8 cha,u8 guan)
{
	clock[2]=18;
	if(minute-clock[1]==cha)
	{
		clock[1]=(clock[1]+cha)%60;
		GPIO_SetBits(GG_GPIO_Port,GG_PIN);
	}
	if(minute-clock[1]==guan)
	{
		GPIO_ResetBits(GG_GPIO_Port,GG_PIN);
	}

	
	
}
void ds1032_init(u8 hour,u8 minute)
{
	ds1302_wirte_rig(0x8e,0x00);//关闭写保护
	ds1302_wirte_rig(0x80,0x40);//seconds37秒
	ds1302_wirte_rig(0x82,minute);//minutes58分
	ds1302_wirte_rig(0x84,hour);//hours23时
	ds1302_wirte_rig(0x86,0x30);//date30日
	ds1302_wirte_rig(0x88,0x09);//months9月
	ds1302_wirte_rig(0x8a,0x07);//days星期日
	ds1302_wirte_rig(0x8c,0x20);//year2020年
	ds1302_wirte_rig(0x8e,0x80);//关闭写保护
}
