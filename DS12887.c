#include "DS12887.h"

/***************************************************
************DS12887初始化程序************************
****************************************************/
void DS_init()
{
    DS_A=0x20;
	DS_B=0x12;
} 

/*往实时时钟芯片写入当前时间--从此以后再也不用调用该函数
实时时钟芯片会在此基础上，愉快的计时--妈妈再也不用担心我的万年历了*/
void write_time() 
{
  	DS_A=0x2f;          //寄存器Ａ
	DS_B|=0x90; 
  	Years=0x17;         //年 
  	Month=0x04;         //月 
  	Day=0x08;           //日 
  	Week=0x06;          //星期 
  	Hour=0x11;          //时 
  	Minute=0x02;        //分 
  	Second=0x00;        //秒 
  	DS_B &=0x7f;        //寄存器Ａ 
}
