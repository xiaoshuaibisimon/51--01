#ifndef __LCD12864_H__
#define __LCD12864_H__
#include "sys.h"


/*  液晶12864口地址  */
#define  wr_com   XBYTE[0xCC00]//[0xC000]     //写命令 
#define  wr_data  XBYTE[0xCD00]//[0xC100]     //写数据 
#define  rd_com   XBYTE[0xCE00]//[0xC200]     //读命令 
#define  rd_data  XBYTE[0xCF00]//[0xC300]     //读数据

#define  MY_LCD   1

#define SCALE_LINE_START_X 9
#define SCALE_LINE_INCSIZE 12
#define SCALE_LINE_WIDTH 6
#define SCALE_LINE_PRECISION 5

sbit RS=P2^0; //这个是LCD的数据命令选择端

sbit RW=P2^1; //这个是LCD的写入或是读出选择端

//sbit PSB=P3^2; //这个是LCD串行还是并行选择端

//sbit RST=P3^4; //这个是LCD的复位端口

sbit LCDE=P2^7; // 这个是LCD的使能端



void lcd_init(void);                                    // lcd初始化 
void write_cmd(BYTE cmd);                     // lcd写命令 
void write_string(unsigned char *s);                    // 写字符串 
void write_data(BYTE dat) ;                    // 写数据 
void seti_wl(BYTE line,column) ;
void set_display_place(BYTE line,column);
void write_string_lcd(BYTE line,column,unsigned char *string);

void crti(unsigned long dat);
void crt_r(float x,BYTE N);

void lcd_init_draw(void);

BYTE read_data(void);
void DrawDots(BYTE x,BYTE y);//打点函数   //x，y为128*64 点阵的坐标
void DrawDots2(BYTE x,BYTE y,BYTE color);
void ShowXY(void);
void ShowScaleLine(BYTE x,BYTE width,WORD var,WORD base,WORD precision);
void UpdateScaleLine();
void UpdateScaleLine3();

#ifdef MY_LCD
void write_data_lcd(BYTE line,column,dat);
void clear_lcd(void);
#endif

#endif