#include "sys.h"

void Delay(WORD n)
{
    WORD x;
	while(n--)
	{
	    x=500;
		while(x--);
	}
}

void Delay2(WORD n)
{
    WORD x;
	while(n--)
	{
	    x=5000;
		while(x--);
	}
}

/*********************************************************
*��ʱn΢�����
**********************************************************/
void DelayXus(WORD n)
{
    while(--n);
}