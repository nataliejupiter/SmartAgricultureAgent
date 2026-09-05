#include "hdc1080.h"
#include "myiic.h"
#include "usart.h"
#include "delay.h"
#include "math.h"
/*********************************************************************************
  * @ 函数名  ： HDC1080_Init
  * @ 功能说明： 初始化HDC1080
  * @ 参数    ： 无
  * @ 返回值  ： 无
  ********************************************************************************/
void HDC1080_Init(void)
{
    uint8_t temp[2];
    unsigned int manufac_id,dev_id,Config_Reg ;
    
    IIC_Init();   //IIC初始化
    
    HDC1080_ReadReg(Manufacturer_ID,temp,2);
    manufac_id=(unsigned int)(temp[0]<<8);
    manufac_id+=temp[1];
    printf("HDC1080 Manufacturer_ID = 0x%x\r\n",manufac_id);   /*打印制造商ID */
    
    HDC1080_ReadReg(Device_ID,temp,2);
    dev_id=(unsigned int)(temp[0]<<8);
    dev_id+=temp[1];
    printf("HDC1080 Device_ID = 0x%x\r\n",dev_id);   /*打印设备ID*/
    if((manufac_id != Manufacturer_ID_value)||(dev_id != Device_ID_value))
    {
        printf("!!!HDC1080 ERROR,Please Check!!!\n");   /*打印设备连接成功*/
    }
    else 
    {
        printf("HDC1080 Online!!!\r\n");
    }
    
    Config_Reg=Config_heateroff;   //关闭Heater,同时采集温度和湿度(温度在前),温度分辨率为14位,湿度分辨率为14位
    printf("config = 0x%x\r\n",Config_Reg);
    HDC1080_WriteReg(Configuration,Config_Reg);  
    
    HDC1080_ReadReg(Configuration,temp,2);
    Config_Reg=(unsigned int)(temp[0]<<8);
    Config_Reg+=temp[1];
    if(Config_Reg == Config_heateroff)   /*检查是否写入成功*/
    {
        printf("Configuration_register setting is successful.\r\n");   
    }
    else 
    {
        printf("Configuration_register setting is failed.\r\n");   
    }
    
}

/*********************************************************************************
  * @ 函数名  ： HDC1080_WriteReg
  * @ 功能说明： 写数据到寄存器内
  * @ 参数    ： 
    *              WriteAddr:内部寄存器地址
    *                             Data:将要写入的数据
  * @ 返回值  ： 无
  ********************************************************************************/
void HDC1080_WriteReg(u8 WriteAddr,unsigned int Data)
{
    unsigned char data[2];
    data[0] = (uint8_t)((Data& 0xFF00) >> 8);
    data[1] = (uint8_t)(Data & 0x00FF);
    IIC_Start();   //起始信号
    IIC_Send_Byte(HDC1080_I2C_ADDR);   //发送HDC1080设备地址+写信号
    IIC_Wait_Ack();
    IIC_Send_Byte(WriteAddr);   //内部寄存器地址
    IIC_Wait_Ack();
    IIC_Send_Byte(data[0]);   //写入内部寄存器数据
    IIC_Wait_Ack();
    IIC_Send_Byte(data[1]);   //写入内部寄存器数据
    IIC_Wait_Ack();
    IIC_Stop();   //停止信号
    
}

/*********************************************************************************
  * @ 函数名  ： HDC1080_ReadReg
  * @ 功能说明： 读取寄存器内的数据
  * @ 参数    ： 
    *              ReadAddr:内部寄存器地址
  *              pBuffer:数据数组首地址
    *              length:要读出数据的个数
  * @ 返回值  ： 无
  ********************************************************************************/
u8 HDC1080_ReadReg(u8 ReadAddr,u8 *pBuffer,u16 length)
{
                                                                                   
  IIC_Start();   //起始信号
    IIC_Send_Byte(HDC1080_I2C_ADDR);   //发送HDC1080设备地址+写信号
    IIC_Wait_Ack();  
    IIC_Send_Byte(ReadAddr);   //内部寄存器地址
    IIC_Wait_Ack();
    IIC_Start();   //起始信号
    IIC_Send_Byte(HDC1080_I2C_ADDR+1);   //发送HDC1080设备地址+读信号
    IIC_Wait_Ack(); 
    while(length)
    {
        *pBuffer++=IIC_Read_Byte(1);   //读出寄存器数据
        length--;
    }
    IIC_NAck();   //发送nACK
  IIC_Stop();   //停止信号        
    return 0;
    
}

/*********************************************************************************
  * @ 函数名  ： Read_Temp_Humi_Reg
  * @ 功能说明： 读取温度和湿度寄存器数值
  * @ 参数    ： 
    *              data:温度和湿度寄存器数值
  * @ 返回值  ： 无
  ********************************************************************************/
void Read_Temp_Humi_Reg(u8 *data)
{
    data[0]=0;
    data[1]=0;
    data[2]=0;
    data[3]=0;
    IIC_Start();   //起始信号
    IIC_Send_Byte(HDC1080_I2C_ADDR);   //发送HDC1080设备地址+写信号
    IIC_Wait_Ack();  
    IIC_Send_Byte(Temperature);   //触发测量
    IIC_Wait_Ack();
    delay_ms(20);   /* Temp转换时间 + Humi转换时间 = 20ms */
    IIC_Start();   //起始信号
    IIC_Send_Byte(HDC1080_I2C_ADDR+1);   //发送HDC1080设备地址+读信号
    IIC_Wait_Ack(); 
    data[0]=IIC_Read_Byte(1);   /* 读取温度寄存器数值 */
    data[1]=IIC_Read_Byte(1);
    data[2]=IIC_Read_Byte(1);   /* 读取湿度寄存器数值 */
    data[3]=IIC_Read_Byte(1);
    IIC_Stop();   //停止信号  
    
}

/*********************************************************************************
  * @ 函数名  ： Convert_HDC1080_TempHumidity
  * @ 功能说明： 转化温度和湿度
  * @ 参数    ： 
    *              data:温度和湿度寄存器数值
  * @ 返回值  ： 无
  ********************************************************************************/
void Convert_HDC1080_TempHumidity(u16 *temp,u16 *humi)
{
    //100 times of the actural value
    u8 data[4];
    Read_Temp_Humi_Reg(data);   //采集温湿度
    
    *temp=(unsigned int)(data[0]<<8);   /* 温度转换 */
    *temp+=data[1];
	// printf("Temperature High Byte: 0x%02X\r\n", data[0]);  // 高八位
   // printf("Temperature Low Byte: 0x%02X\r\n", data[1]);   // 低八位
    *temp=(*temp*16500)>>16;
    *temp-=4000;
    *temp/=100;
    printf("Temp = %dC\r\n",temp);

    *humi=(unsigned int)(data[2]<<8);   /* 湿度转换 */
    *humi+=data[3];
    *humi=(*humi*100)>>16;
    //printf("humidity = %d%%RH\r\n",humi);
    
}

