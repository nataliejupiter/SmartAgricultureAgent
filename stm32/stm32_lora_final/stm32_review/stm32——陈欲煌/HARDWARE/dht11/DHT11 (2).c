#include "stm32f4xx.h"            
#include "DHT11.h"
#include "delay.h"
 
 
//复位DHT11
void DHT11_Reset(void)
{
	//复位DHT11的时序：主机拉低总线，延时至少18ms，然后主机拉高总线，延时20-40us，等待从机应答
	DHT11_IO_OUT(); //复位时序是主机来完成的，所以首先设置主机IO引脚输出模式
	DHT11_DQ_OUT=0;  //主机拉低总线
	delay_ms(20);   //延时至少18ms
	DHT11_DQ_OUT=1;  //主机拉高总线
	delay_us(30);    //延时20-40us
}
//等待DHT11的应答信号
//返回1：未检测到DHT11的存在
//返回0：存在
u8 DHT11_CheckExist(void)
{
	//应答信号的时序是：主机发送应答信号后，从机DHT11会拉低信号线，保持40-50us。此时，若读取主机总线为低电平，这说明DHT11发送了应答信号
	//DHT11发送应答信号之后，再把总线拉高，保持40-50us，准备发送数据，每一位bit数据都是以低电平开始的。
	u8 Existence=0;
	DHT11_IO_IN();  //主机IO引脚设置为输入模式，等待从机的应答信号输入
	while(DHT11_DQ_IN&&Existence<100) //从机DHT11会拉低信号线，保持40-80us，等待应答  按位&&操作必须两个条件都为真才是真
	{
		//DHT11_DQ_IN为真，就一直在这里循环，表示始终没有接收到从机DHT11的应答信号；因为总线拉低，读取高电平是始终没有响应的
		//DHT11_DQ_IN是从机DHT11发送主机MCU的信号，应答信号时，从机会拉低信号线，因此，如果主机收到的是高电平，那么意味着没有发送应答信号
		//Existence<100表示：设置一个缓冲时间去等待从机发送应答，这里设置的就是100us
		Existence++;
		delay_us(1);
	}
	if(Existence>=100)
	{
		return 1; //主机给从机的缓冲时间是100us，主机等了从机100us还是没有接收到应答信号，那么返回信息，未检测到DHT11的存在
	}
	else         //在给定的100us内接收到了应答信号，将缓冲计时变量Existence清0，为后续总线拉高后延迟做准备
		Existence=0;
	while(!DHT11_DQ_IN&&Existence<100) //拉低后再次拉高，准备发送数据，延迟40-80us
	{
		//!DHT11_DQ_IN表示主机接收到了应答信号，也就是主机接收到了低电平，延迟100us
		Existence++;
		delay_us(1);
	}
	if(Existence>=100)
	{
		return 1;
	}
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit(void)
{
	//DHT11读取一位的时序：不管读的那一位是高电平1还是低电平0，首先从机DHT11都需要拉低总线
	//数据0：从机拉低总线，延时12-14us，然后从机释放总线，延时26-28us
	//数据1：从机拉低总线，延时12-14us，然后从机释放总线，延时116-118us
	u8 data=0;
	while(DHT11_DQ_IN&&data<100)//等待变为低电平
		//主机从DHT11读取一位，从机要拉低总线，在没有拉低之前，主机收到的DHT11_DQ_IN一定是高电平1,而通过观察低电平的时序可以发现，不管是逻辑1还是0，低电平延时12-14us
	//所以设置的100us是远远大于低电平延时时间的，所以data<100这个条件在此while循环中一定为真，跳出循环的条件一定是DHT11_DQ_IN=0，也就是等待变为低电平
	{
		data++;
		delay_us(1);
	}
	data=0; //离开while循环时主机一定收到了低电平，此时DHT11_DQ_IN=0；设置data=0是为后续等待高电平做准备
	while(!DHT11_DQ_IN&&data<100) //等待变为高电平
	{
		//从上面的循环出来时，DHT11_DQ_IN=0，取反就为真
		//条件data<100：低电平0的整个发送时序延时时间(包括低电平延时12-14us，高电平延时26-28us)也远远小于100us，所以data<100在该循环中也是始终为真的
		//				高电平1的整个发送时间是大于100us的(低电平延时12-14us，高电平延时116-118us)
		//经分析，离开循环的条件是DHT11_DQ_IN变为高电平=1，取反等于0，为假。在低电平0的12-14us过去以后，高电平信号就会来临
		data++;
		delay_us(1);
	}
	//delay_us(40) 没有这个延迟40us是无法判断是数据1还是数据0的
	delay_us(40);//从上一个while循环出来以后，时序停留在刚刚变为高电平的瞬间，这个时候延时40us，数据0会跳过高电平，数据1会停留在高电平
	if(DHT11_DQ_IN) //这个时候根据主机读到的是1还是0设置返回值
		return 1;
	else
		return 0;
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte(void)
{
	u8 i,data;
	data=0;
	for(i=0;i<8;i++)
	{
		data=data<<1;  //DHT11读取的字节是高位先行的，所以每循环一次都要将上次读取的那一位左移，右侧最低位补0，每次都将新读取的那一位数据和0进行|或运算。
		data=data|DHT11_Read_Bit();
	}
	return data;
}
//从DHT11读取一位数据
//temperature：温度值(范围：0~50℃)
//humidity：湿度值(范围：20%~90%)
//返回值：0 正常；1 读取失败
u8 DHT11_Read_Data(u8 *temperature,u8 *humidity)
{
	//DHT11的数据格式是：5个字节，40位数据，前两位是湿度的整数和小数部分，第三、第四位是温度的整数和小数部分，最后一位是校验位
	u8 Buf[5]; //定义一个数组来存放收到的5个字节的数组
	u8 i;
	DHT11_Reset();
	if(DHT11_CheckExist()==0)  //应答信号返回值为0，表示检测到了DHT11应答信号
	{
		for(i=0;i<5;i++) //调用读字节函数将读取到的5个字节存放到Buf数组中
		{
			Buf[i]=DHT11_Read_Byte();
		}
		if((Buf[0]+Buf[1]+Buf[2]+Buf[3])==Buf[4]) //检验成功
		{
			*humidity=Buf[0];   //这里只显示了温湿度的整数部分
			*temperature=Buf[2];
		}
	}
	else
		return 1;  //DHT11_CheckExist()==1 表示没有检测到DHT11的应答信号，报错
	return 0; //返回正常情况
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1：不存在
//返回0：存在
u8 DHT11_Init(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG,ENABLE);  //使能GPIOG时钟
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;  //默认设置为输出模式
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOG,&GPIO_InitStructure);
	
	DHT11_Reset();
	return DHT11_CheckExist(); //初始化返回检测DHT11是否成功，0：成功 1：收不到应答信号，报错
}
 
 
 