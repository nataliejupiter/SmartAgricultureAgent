#ifndef __HDC1080_H
#define __HDC1080_H
#include "sys.h"

//寄存器地址
#define HDC1080_I2C_ADDR   0x80   //HDC1080的IIC地址为1000000（7位地址）+ 读(1)或写(0)方向位
#define Temperature        0x00   //温度寄存器,复位值为0x0000 
#define Humidity           0x01   //湿度寄存器,复位值为0x0000 
#define Configuration      0x02   //配置寄存器,复位值为0x1000 
#define Manufacturer_ID    0xFE   //制造商ID寄存器,0x5449
#define Device_ID          0xFF   //设备ID寄存器,0x1050 

//寄存器值
#define Manufacturer_ID_value  0x5449   //制造商ID值
#define Device_ID_value        0x1050   //设备ID值
#define Config_heateroff       0x1000   //关闭Heater,同时采集温度和湿度(温度在前),温度分辨率为14位,湿度分辨率为14位
#define Config_heateron        0x3000   //开启Heater,同时采集温度和湿度(温度在前),温度分辨率为14位,湿度分辨率为14位

void HDC1080_Init(void);   //初始化HDC1080
void HDC1080_WriteReg(u8 WriteAddr,unsigned int Data);   //写入数据到寄存器内
u8 HDC1080_ReadReg(u8 ReadAddr,u8 *pBuffer,u16 length);   //读取寄存器内的数据
void Read_Temp_Humi_Reg(u8 *datax);   //读取温度和湿度寄存器数值
void Convert_HDC1080_TempHumidity(u16 *temp,u16 *humi);   //转化温度和湿度

#endif

