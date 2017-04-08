#ifndef __DS18B20_H__
#define __DS18B20_H__
#include "sys.h"


  

extern char temperature[2]; //存放温度数据


sbit DS1820_DQ= P1^7; //单总线引脚
sbit bzz1=P2^3 ;	 //P2兼做I/O口用
sbit bzz2=P2^2 ;

void DS18B20_Init() ; //DS18B20 初始化 
bit  DS1820_Reset(); //DS1820 复位 
void DS1820_WriteData(BYTE wData); //写数据到DS1820 
BYTE DS1820_ReadData(); //读数据 
void read_wendu();
void get_wendu(void);

#endif
