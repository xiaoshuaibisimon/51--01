#include "timer.h"

extern BYTE timer_key;
extern BYTE scale_line_status;
void TimerInit(void)
{
	TMOD = 0x01; //16位定时器
    TL0  = 0x3C; //50ms定时
    TH0  = 0xB0;

    timer_key = 100;//100*50=5000ms--定时5s--但是画柱状图太慢了--导致感觉定时不足五秒--那是你的眼睛欺骗了你

    ET0 = 1; //允许T0中断                                                      
    EA  = 1; //开放中断
    TR0 = 1;
}

void Timer_Routine(void) interrupt 1
{
    TL0  = 0x3C;
    TH0  = 0xB0;

    timer_key--;//每一次50ms减减

    if(0 == timer_key){//定时满5s了终于
       
       timer_key = 100;
	   scale_line_status = 1;
    }        
}