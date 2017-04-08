#include "DS18B20.h"

/**********************************************************
*DS18B20 初始化 
*函数名称:DS1820_WriteData() 
*说明：本初始化程序可以不要，因为18B20 在出厂时就被配置为12 位精度了 
**********************************************************/
void DS18B20_Init()
{
	DS1820_Reset();
	DS1820_WriteData(0xCC); // 跳过ROM 
	DS1820_WriteData(0x4E); // 写暂存器 
	DS1820_WriteData(0x20); // 往暂存器的第三字节中写上限值 
	DS1820_WriteData(0x00); // 往暂存器的第四字节中写下限值 
	DS1820_WriteData(0x7F); // 将配置寄存器配置为12 位精度 
	DS1820_Reset();
}
/**********************************************************
*DS1820 复位及存在检测(通过存在脉冲可以判断DS1820 是否损坏) 
*函数名称:DS1820_Reset() 
*说明:函数返回一个位标量(0 或1)flag=0 存在,反之flag=1 不存在 
**********************************************************/
bit DS1820_Reset()
{
	bit flag;
	DS1820_DQ = 0; //拉低总线 
	DelayXus(480); //延时480 微秒,产生复位脉冲 
	DS1820_DQ = 1; //释放总线 
	DelayXus(80); //延时80 微秒对总线采样 
	flag = DS1820_DQ; //对数据脚采样 
	DelayXus(400); //延时400 微秒等待总线恢复 
	return (flag); //根据flag 的值可知DS1820 是否存在或损坏 ，可加声音告警提示DS1820 故障 
}
/**********************************************************
*写数据到DS1820
*函数名称:DS1820_WriteData()
**********************************************************/
void DS1820_WriteData(BYTE wData)
{
	BYTE i;
	for (i=8;i>0;i--)
	{
		DS1820_DQ = 0; //拉低总线,产生写信号 
		DelayXus(4); //延时4us 
		DS1820_DQ = wData&0x01; //发送1 位 
		DelayXus(60); //延时60us,写时序至少要60us 
		DS1820_DQ = 1; //释放总线,等待总线恢复 
		wData>>=1; //准备下一位数据的传送 
	}
}
/**********************************************************
*从DS1820 中读出数据
*函数名称:DS1820_ReadData()
**********************************************************/
BYTE DS1820_ReadData()
{
	BYTE i,TmepData;
	for (i=8;i>0;i--)
	{
		TmepData>>=1;
		DS1820_DQ = 0; //拉低总线,产生读信号 
		DelayXus(4); //延时4us 
		DS1820_DQ = 1; //释放总线,准备读数据 
		DelayXus(8); //延时8 微秒读数据 
		if (DS1820_DQ == 1)
		{TmepData |= 0x80;}
		DelayXus(60); //延时60us 
		DS1820_DQ = 1; //拉高总线,准备下一位数据的读取. 
	}
	return (TmepData);//返回读到的数据 
}


char temperature[2]; //存放温度数据
/*********************************************************
*读取温度程序
**********************************************************/
void read_wendu()
{
    BYTE i;
	DS1820_Reset(); //复位
	DS1820_WriteData(0xcc); //跳过ROM 命令
	DS1820_WriteData(0x44); //温度转换命令
	DS1820_Reset(); //复位
	DS1820_WriteData(0xcc); //跳过ROM 命令
	DS1820_WriteData(0xbe); //读DS1820 温度暂存器命令
	for (i=0;i<2;i++)
	{
		temperature[i]=DS1820_ReadData(); //采集温度
	}
	DS1820_Reset(); //复位,结束读数据
}

extern float wen_val;
extern BYTE ah,al;
void get_wendu(void)
{
   read_wendu();
   ah=temperature[1]<<4;
   ah&=0xf0;
   al=temperature[0]>>4;
   al&=0x0f;
   ah=ah|al;
   al=temperature[0]&0x0f;
   if ((ah&0x80)!=0)
   {
		if (al==0)
		{
		  ah=~ah;ah=ah+1;
		}
		else
		{	
		  ah=~ah;al=~al;al=al+1;al&=0x0f;
		}
		wen_val=ah*(-1.0)+al*(-0.0625);
   }
   else 
   {
        wen_val=ah*1.0+al*0.0625;
   }
}
 
