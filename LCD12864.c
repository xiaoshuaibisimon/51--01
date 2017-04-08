
#include "LCD12864.h"


/************************************************************************
Function name:       write_cmd 
Descriptions:        向lcd输入指令 
************************************************************************/
void write_cmd(BYTE cmd)
{   
	BYTE dl;
	do {
		dl=rd_com;
		} while((dl&0x80)!=0);	//判忙 
    wr_com= cmd;
    Delay(1);
}


/**********************************************************************
Function name:       write_data 
Descriptions:        写入数据 
**********************************************************************/
void write_data(BYTE dat)	
{
	BYTE dl;
	do {
		dl=rd_com;
		} while((dl&0x80)!=0);	//判忙 
    wr_data= dat;  
    Delay(1);
}  

/***********************************************************************
Function name:       write_string 
Descriptions:        写入字符串 
***********************************************************************/
void write_string(BYTE *s)												 
{
    while(*s != '\0')            //'\0'为字符串结束标志 
    {
        write_data(*s);
        s++;
    }
}

/**********************************************************************
Function name:       set_display_place
Descriptions:        设置字符的显示位置 
**********************************************************************/
void set_display_place(BYTE line,column)
{
    BYTE address;
    if(line == 1)
    {
        address = 0x80 + column;
    }
    else if(line == 2)
    {
        address = 0x90 + column;
    }
    else if(line == 3)
    {
        address = 0x88 + column;
    }
    else if(line == 4)
    {
        address = 0x98 + column;
    }
    write_cmd(address);         
}

/*******************************************************************
Function name:       将字符串写到指定的位置 
Descriptions:        将字符串显示在lcd的特定位置 
*******************************************************************/
void write_string_lcd(BYTE line,column,unsigned char *string)
{
    set_display_place(line,column);
    write_string(string);
    Delay(1);
}

/***************************************************
************液晶模块初始化******************************
****************************************************/
void lcd_init(void)				  
{
  write_cmd(0x30);//功能设置，一次送8位数据，基本指令集 
  write_cmd(0x30);//功能设置，一次送8位数据，基本指令集 
  write_cmd(0x0C);//0000,1100 整体显示，游标off，游标位置off
  write_cmd(0x01);//0000,0001 清DDRAM 
  write_cmd(0x06);//02
}

/*****************设置数据显示位置********************/
/****数值显示0—65535,column为数字起始位置:0,1,2...****/
void seti_wl(BYTE line,column) 
{
	BYTE dli;
	dli=column%2;
	column/=2;
	set_display_place(line,column);
	if (dli==1)
	{
		dli=0x20;
		write_data(dli);	
	}
}

/***************************************************
************显示长整型数据***************************
****************************************************/
void crti(unsigned long dat) 
{
	BYTE dhi,dli,ddi,dei;
	unsigned long datah;
	unsigned long datal;
	datah=dat;
	dhi=0;
	if (datah>=10)
	{
		do
		{		
			datah/=10;
			dhi++;
		}while(datah>=10);
		datah=dat;
		ddi=dhi;
		for (dli=0;dli<dhi;dli++)
		{
			datal=1;
			for (dei=0;dei<ddi;dei++)
			{
				datal*=10;
			}
			datah=dat/datal;
			dat=dat%datal;
			datah+=0x30;
			write_data(datah);
			ddi--;
		}
		dat+=0x30;
		write_data(dat);
	}
	else
	{
		dat=dat+0x30;
		write_data(dat);
	}
}
 
/***************************************************
************浮点数显示******************************
****************************************************/
void crt_r(float x,unsigned char N)
{
	 BYTE dli;
     unsigned int  dath;
	 unsigned int  datl;
	 unsigned int  dat;
	 
	 if (x<0.0)
	 {
	 	dat=0x2d;
		write_data(dat);
		Delay(1);
		x=fabs(x);
	 }
     dath=(int)x;	
     crti(dath);
     if (N>0)
     {
          dat=0x2e;
          write_data(dat);
		  Delay(1);
		  dat=1;
          for (dli=0;dli<N;dli++)
		  {
		  	dat*=10;
		  }
		  dath=(int)(x*dat)-dath*dat;
		  for (dli=1;dli<N;dli++)
		  {
			dat /= 10;
		  	datl=dath/dat;
			datl += 0x30;
			write_data(datl);
			dath %= dat;
		  }
		  crti(dath);
     }	
}






#ifdef MY_LCD


/******************************************************************
Function name:       将字符写到指定的位置 
Descriptions:        将字符串显示在lcd的特定位置 
*******************************************************************/
void write_data_lcd(BYTE line,column,dat)
{
    set_display_place(line,column);
    write_data(dat);
    Delay(1);
}

static void lcd_delay(WORD x)
{

    WORD y;

    for(;x>0;x--)

        for(y=110;y>0;y--);

}

/*
画图清屏，由于LCD的清屏指令0X01不能作用在绘图中，所有只能自己写清屏子程序
*/

void clear_lcd(void)
{    

    BYTE i,j;
    write_cmd(0x34);
    for(i=0;i<32;i++)             //因为LCD有纵坐标32格所以写三十二次
    {
        write_cmd(0x80+i);         //先写入纵坐标Y的值
        write_cmd(0x80);         //再写入横坐标X的值
        for(j=0;j<32;j++)         //横坐标有16位，每位写入两个字节的的数据，也就写入32次
        {                         //因为当写入两个字节之后横坐标会自动加1，所以就不用再次写入地址了。
            write_data(0x00);    
        }
    }
    write_cmd(0x36);
    write_cmd(0x30);
}
#endif






void lcd_init_draw(void)
{
	//write_cmd(0x34);//写指令函数，扩充指令集，绘图关
    //write_cmd(0x36);//8位数据传输，扩展指令操作，绘图开 
#if 1    
	     
    write_cmd(0x3E);//8位数据传输，扩展指令操作，绘图开             
    write_cmd(0x01);//清屏 
#else
	write_cmd(0x34);
    write_cmd(0x36);
   
#endif
}

BYTE read_data(void)
{
	BYTE dl;
	BYTE res;
	do {
		dl=rd_com;
		} while((dl&0x80)!=0);	//判忙 
    res = rd_data;  
    Delay(1);
	return res;
}

/*

写入一个点的子程序。具体步骤是：计算出X轴、Y轴的地址、X轴中的第几位，
然后读出该地址现在的值，因为一般写入新的点的时候，会覆盖掉16个点中其他点，
当你要同时显示16个点中的两个点的时候就会冲突，所以先将显示中的点读出来，
然后在或上要点亮的点，这样就可以同时点亮。注意读取数据的时候读取的第一个数据不要，
从第二数据开始取，也就是说要读取三次，只取后面两次的值。
还有就是读取数据之前要先写入你要读取数据的地址，读取数据之后的写入数据还要从新写入地址。
最后就是输入数据地址，先输入Y轴，再输入X轴，输入数据。

*/


void DrawDots(BYTE x,BYTE y)//打点函数   //x，y为128*64 点阵的坐标
{

	WORD bt=0,read=0;
    BYTE x_adr,y_adr,h_bit,l_bit;

	y_adr=0x80+y%32;//计算Y轴的地址，应为纵坐标有64个，所有对32求余，当Y大于31时，Y的坐标是下半屏的。

	if(y>31) //计算X轴的地址当Y大于31时X的地址在下半屏，从0X88开始，小于31时X的地址是在上半屏，从0X80开始
        x_adr=0x88+x/16;        
    else
        x_adr=0x80+x/16;

	bt=0x8000>>(x%16); //求这个点到底是在哪个点

	write_cmd(0x34);
    write_cmd(0x36);
    write_cmd(y_adr);     //读取数据的时候要先写入所取数据的地址
    write_cmd(x_adr);

	read_data();         //读取的第一个字节不要

	read=read_data();     //从第二个字节开始接收。
    read<<=8;
    read|=read_data();
    bt=bt|read;
    h_bit=bt>>8;
    l_bit=bt;

	write_cmd(y_adr);     //写入点的时候，重新写入地址，因为地址已经改变。
    write_cmd(x_adr);
    write_data(h_bit);
    write_data(l_bit);

	write_cmd(0x36); //开显示
    write_cmd(0x30);     //转回基本指令集   
}


void DrawDots2(BYTE x,BYTE y,BYTE color)//打点函数   //x，y为128*64 点阵的坐标
{
     BYTE row,xlabel,xlabel_bit; 
     BYTE Read_H=0,Read_L=0;  
     write_cmd(0x34);       //扩充指令 
     write_cmd(0x36);       //绘图指令 
     xlabel=x>>4;            //确定水平坐标地址
     xlabel_bit=x & 0x0F; // 细分水平坐标中的第几位
     
	 if(y<32) 
	 	row=y;
     else{
	    row=y-32;
		xlabel+=8;      
	 } 
     write_cmd(row+0x80);
     write_cmd(xlabel+0x80);
     read_data();
     Read_H=read_data();
     Read_L=read_data();   
     write_cmd(row+0x80);
     write_cmd(xlabel+0x80);   //水平坐标地址+基址=显示的水平地址   
     if(xlabel_bit<8) 
     {
          switch(color)
         {
             case 0:Read_H &=(~(0x01<<(7-xlabel_bit))); break; //变暗 ，看不见
             case 1:Read_H |=(0x01<<(7-xlabel_bit)); break; //变亮  ，看得见
             case 2:Read_H ^=(0x01<<(7-xlabel_bit)); break; //反转
             default:break;
          } 
         write_data(Read_H);
         write_data(Read_L); 
     } 
     else 
     {
          switch(color)
          {
               case 0:Read_L &=(~(0x01<<(15-xlabel_bit))); break; //变暗    ，看不见 
               case 1:Read_L |=(0x01<<(15-xlabel_bit)); break; //变亮  ，看得见
               case 2:Read_L ^=(0x01<<(15-xlabel_bit)); break; //反转 
               default:break;
          } 
          write_data(Read_H);
          write_data(Read_L);
     } 
     write_cmd(0x30);//恢复正常模式  
}
void ShowXY(void)
{
	BYTE i = 0,	x = 0,y = 0;
	
    for(i=0;i<62;i++) //画出Y轴
    {
        DrawDots(2,i);
    }

    for(i=2;i<128;i++)
    {
        x=i;
        //y=32-x%32;
        DrawDots(x,61);
    }
	for(i = 0;i < 2;i++)
	{
	 	 DrawDots(126-i,60-i);
		 DrawDots(3+i,1+i);

		 DrawDots(126-i,62+i);
		 DrawDots(1-i,1+i);
	}
}
extern WORD new_temprature[BUF_LEN];
extern WORD old_temprature[BUF_LEN];

void ShowScaleLine(BYTE x,BYTE width,WORD var,WORD base,WORD precision)
{
   BYTE i = 0,j = 0;
   BYTE height = (var - base)/precision;
   for(j = 0; j < height;j++)
   {
	   for(i = 0;i < width;i++)
	   {
			DrawDots(x+i,60-j);
	   }
   }
}

void GetOldXY(BYTE *x,BYTE *y,BYTE index,WORD base,WORD precision)
{
	if(old_temprature[index] == 0)
	{
		*y = 60;
	}else{
		*y = 61- ((old_temprature[index] - base)/precision);
	}
	*x = SCALE_LINE_START_X + (index * SCALE_LINE_INCSIZE);	
}

void HandleScaleLine(BYTE x,BYTE y,BYTE action,WORD delta,WORD precision)
{
	 BYTE i = 0,j = 0;
	 BYTE height = delta/precision;
	 if(action == 0)
	 {
	 	return ;		
	 }
	 else if(action == 1)
	 {
		 for(i = 0;i < height;i++)
		 {
			 for(j = 0;j < SCALE_LINE_WIDTH;j++)
			 {
				 DrawDots2(x+j,y-i,1);
			 }
		 }
	 }
	 else if(action == 2)
	 {
		 for(i = 0;i < height;i++)
		 {
			 for(j = 0;j < SCALE_LINE_WIDTH;j++)
			 {
				 DrawDots2(x+j,y+i,0);
			 }
		 }
	 }
}
extern WORD g_base;
void UpdateScaleLine()
{

	BYTE i = 0,j = 0;
	BYTE x = 0,y = 0;
	BYTE action = 0;
	WORD delta = 0;
	for(i = 0;i < BUF_LEN;i++)
	{
		if(new_temprature[i] > old_temprature[i])
		{
			delta =  new_temprature[i] - old_temprature[i];
			action = 1;
		}
		else if(new_temprature[i] < old_temprature[i])
		{
			delta =  old_temprature[i] - new_temprature[i];
			action = 2;
		}
		else
		{
			delta = 0; 
			action = 0;
			continue;
		}

		GetOldXY(&x,&y,i,g_base,SCALE_LINE_PRECISION);
		HandleScaleLine(x,y,action,delta,SCALE_LINE_PRECISION);
	}

}


void UpdateScaleLine2()
{
	BYTE i = 0;

	clear_lcd();
	ShowXY();
	for(i = 0;i < BUF_LEN;i++)
	{	 
		 ShowScaleLine(SCALE_LINE_START_X + (i * SCALE_LINE_INCSIZE),SCALE_LINE_WIDTH,new_temprature[i],g_base,SCALE_LINE_PRECISION);
	}

}

void UpdateScaleLine3()
{

	BYTE i = 0,j = 0,k=0;
	BYTE x = 0,y = 0;
	BYTE action = 0;
	WORD delta = 0;
	BYTE new_h = 0;
	BYTE old_h = 0;

	for(i = 0;i < BUF_LEN;i++)
	{
		if(new_temprature[i] == 0)
			continue;
		if(new_temprature[i] > g_base)
			new_h = (new_temprature[i] - g_base)/SCALE_LINE_PRECISION;
		else
			new_h = 0;

		if(new_h > 61)
			new_h = 61;

		if(old_temprature[i] > g_base)
			old_h = (old_temprature[i] - g_base)/SCALE_LINE_PRECISION;
		else 
			old_h = 0;

		if(old_h > 61)
			old_h = 61;
		
		if(new_h == old_h)
			continue;
		else if(new_h > old_h)
		{
			x = SCALE_LINE_START_X + (i * SCALE_LINE_INCSIZE);
			y = 61 - old_h;
			for(k = 0;k < (new_h - old_h);k++)
			 {
				 for(j = 0;j < SCALE_LINE_WIDTH;j++)
				 {
					 DrawDots2(x+j,y-1-k,1);
				 }
			 }
			
		}
		else if (new_h < old_h)
		{
			x = SCALE_LINE_START_X + (i * SCALE_LINE_INCSIZE);
			y = 61 - old_h;
			for(k = 0;k < (old_h - new_h);k++)
			 {
				 for(j = 0;j < SCALE_LINE_WIDTH;j++)
				 {
					 DrawDots2(x+j,y+k,0);
				 }
			 }
		}
	}

}