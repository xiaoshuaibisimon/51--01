#ifndef __DS12887_H__
#define __DS12887_H__
#include "sys.h"


/*  DS12887�ڵ�ַ  */ 
#define  DS_A     XBYTE[0x1C0A]//[0x100A]     //�Ĵ����� 
#define  DS_B     XBYTE[0x1C0B]//[0x100B]     //�Ĵ����� 
#define  DS_C     XBYTE[0x1C0C]//[0x100C]     //�Ĵ����� 
#define  Years    XBYTE[0x1C09]//[0x1009]     //�� 
#define  Month    XBYTE[0x1C08]//[0x1008]     //�� 
#define  Day      XBYTE[0x1C07]//[0x1007]     //�� 
#define  Week     XBYTE[0x1C06]//[0x1006]     //���� 
#define  Hour     XBYTE[0x1C04]//[0x1004]     //ʱ 
#define  Minute   XBYTE[0x1C02]//[0x1002]     //�� 
#define  Second   XBYTE[0x1C00]//[0x1000]     //�� 

void DS_init();
void write_time();

#endif