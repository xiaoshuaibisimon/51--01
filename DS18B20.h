#ifndef __DS18B20_H__
#define __DS18B20_H__
#include "sys.h"


  

extern char temperature[2]; //����¶�����


sbit DS1820_DQ= P1^7; //����������
sbit bzz1=P2^3 ;	 //P2����I/O����
sbit bzz2=P2^2 ;

void DS18B20_Init() ; //DS18B20 ��ʼ�� 
bit  DS1820_Reset(); //DS1820 ��λ 
void DS1820_WriteData(BYTE wData); //д���ݵ�DS1820 
BYTE DS1820_ReadData(); //������ 
void read_wendu();
void get_wendu(void);

#endif
