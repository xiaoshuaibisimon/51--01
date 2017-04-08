#ifndef __DS12887_H__
#define __DS12887_H__
#include "sys.h"


/*  DS12887口地址  */ 
#define  DS_A     XBYTE[0x1C0A]//[0x100A]     //寄存器Ａ 
#define  DS_B     XBYTE[0x1C0B]//[0x100B]     //寄存器Ｂ 
#define  DS_C     XBYTE[0x1C0C]//[0x100C]     //寄存器Ｃ 
#define  Years    XBYTE[0x1C09]//[0x1009]     //年 
#define  Month    XBYTE[0x1C08]//[0x1008]     //月 
#define  Day      XBYTE[0x1C07]//[0x1007]     //日 
#define  Week     XBYTE[0x1C06]//[0x1006]     //星期 
#define  Hour     XBYTE[0x1C04]//[0x1004]     //时 
#define  Minute   XBYTE[0x1C02]//[0x1002]     //分 
#define  Second   XBYTE[0x1C00]//[0x1000]     //秒 

void DS_init();
void write_time();

#endif