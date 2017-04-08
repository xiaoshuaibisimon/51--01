#ifndef __LCD12864_H__
#define __LCD12864_H__
#include "sys.h"


/*  Һ��12864�ڵ�ַ  */
#define  wr_com   XBYTE[0xCC00]//[0xC000]     //д���� 
#define  wr_data  XBYTE[0xCD00]//[0xC100]     //д���� 
#define  rd_com   XBYTE[0xCE00]//[0xC200]     //������ 
#define  rd_data  XBYTE[0xCF00]//[0xC300]     //������

#define  MY_LCD   1

#define SCALE_LINE_START_X 9
#define SCALE_LINE_INCSIZE 12
#define SCALE_LINE_WIDTH 6
#define SCALE_LINE_PRECISION 5

sbit RS=P2^0; //�����LCD����������ѡ���

sbit RW=P2^1; //�����LCD��д����Ƕ���ѡ���

//sbit PSB=P3^2; //�����LCD���л��ǲ���ѡ���

//sbit RST=P3^4; //�����LCD�ĸ�λ�˿�

sbit LCDE=P2^7; // �����LCD��ʹ�ܶ�



void lcd_init(void);                                    // lcd��ʼ�� 
void write_cmd(BYTE cmd);                     // lcdд���� 
void write_string(unsigned char *s);                    // д�ַ��� 
void write_data(BYTE dat) ;                    // д���� 
void seti_wl(BYTE line,column) ;
void set_display_place(BYTE line,column);
void write_string_lcd(BYTE line,column,unsigned char *string);

void crti(unsigned long dat);
void crt_r(float x,BYTE N);

void lcd_init_draw(void);

BYTE read_data(void);
void DrawDots(BYTE x,BYTE y);//��㺯��   //x��yΪ128*64 ���������
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