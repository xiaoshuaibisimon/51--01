#ifndef __SYS_H__
#define __SYS_H__

#include "reg51.h"
#include"absacc.h" 
#include"math.h"

typedef unsigned char BYTE;
typedef unsigned int  WORD;
#define BUF_LEN  10


void DelayXus(WORD n);

void Delay(WORD n);
void Delay2(WORD n);

#endif