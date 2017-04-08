#include "timer.h"

extern BYTE timer_key;
extern BYTE scale_line_status;
void TimerInit(void)
{
	TMOD = 0x01; //16λ��ʱ��
    TL0  = 0x3C; //50ms��ʱ
    TH0  = 0xB0;

    timer_key = 100;//100*50=5000ms--��ʱ5s--���ǻ���״ͼ̫����--���¸о���ʱ��������--��������۾���ƭ����

    ET0 = 1; //����T0�ж�                                                      
    EA  = 1; //�����ж�
    TR0 = 1;
}

void Timer_Routine(void) interrupt 1
{
    TL0  = 0x3C;
    TH0  = 0xB0;

    timer_key--;//ÿһ��50ms����

    if(0 == timer_key){//��ʱ��5s������
       
       timer_key = 100;
	   scale_line_status = 1;
    }        
}