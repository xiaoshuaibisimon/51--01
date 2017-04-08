#include "timer.h"

extern BYTE timer_key;
extern BYTE scale_line_status;
void TimerInit(void)
{
	TMOD = 0x01; //16位定时器
    TL0  = 0x3C; //50ms定时
    TH0  = 0xB0;

    timer_key = 400;

    ET0 = 1; //允许T0中断                                                      
    EA  = 1; //开放中断
    TR0 = 1;
}

void Timer_Routine(void) interrupt 1
{
    TL0  = 0x3C;
    TH0  = 0xB0;

    timer_key--;

    if(0 == timer_key){
       
       timer_key = 400;
	   scale_line_status = 1;
    }        
}