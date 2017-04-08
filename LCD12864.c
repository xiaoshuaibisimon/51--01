
#include "LCD12864.h"


/************************************************************************
Function name:       write_cmd 
Descriptions:        ��lcd����ָ�� 
************************************************************************/
void write_cmd(BYTE cmd)
{   
	BYTE dl;
	do {
		dl=rd_com;
		} while((dl&0x80)!=0);	//��æ 
    wr_com= cmd;
    Delay(1);
}


/**********************************************************************
Function name:       write_data 
Descriptions:        д������ 
**********************************************************************/
void write_data(BYTE dat)	
{
	BYTE dl;
	do {
		dl=rd_com;
		} while((dl&0x80)!=0);	//��æ 
    wr_data= dat;  
    Delay(1);
}  

/***********************************************************************
Function name:       write_string 
Descriptions:        д���ַ��� 
***********************************************************************/
void write_string(BYTE *s)												 
{
    while(*s != '\0')            //'\0'Ϊ�ַ���������־ 
    {
        write_data(*s);
        s++;
    }
}

/**********************************************************************
Function name:       set_display_place
Descriptions:        �����ַ�����ʾλ�� 
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
Function name:       ���ַ���д��ָ����λ�� 
Descriptions:        ���ַ�����ʾ��lcd���ض�λ�� 
*******************************************************************/
void write_string_lcd(BYTE line,column,unsigned char *string)
{
    set_display_place(line,column);
    write_string(string);
    Delay(1);
}

/***************************************************
************Һ��ģ���ʼ��******************************
****************************************************/
void lcd_init(void)				  
{
  write_cmd(0x30);//�������ã�һ����8λ���ݣ�����ָ� 
  write_cmd(0x30);//�������ã�һ����8λ���ݣ�����ָ� 
  write_cmd(0x0C);//0000,1100 ������ʾ���α�off���α�λ��off
  write_cmd(0x01);//0000,0001 ��DDRAM 
  write_cmd(0x06);//02
}

/*****************����������ʾλ��********************/
/****��ֵ��ʾ0��65535,columnΪ������ʼλ��:0,1,2...****/
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
************��ʾ����������***************************
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
************��������ʾ******************************
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
Function name:       ���ַ�д��ָ����λ�� 
Descriptions:        ���ַ�����ʾ��lcd���ض�λ�� 
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
��ͼ����������LCD������ָ��0X01���������ڻ�ͼ�У�����ֻ���Լ�д�����ӳ���
*/

void clear_lcd(void)
{    

    BYTE i,j;
    write_cmd(0x34);
    for(i=0;i<32;i++)             //��ΪLCD��������32������д��ʮ����
    {
        write_cmd(0x80+i);         //��д��������Y��ֵ
        write_cmd(0x80);         //��д�������X��ֵ
        for(j=0;j<32;j++)         //��������16λ��ÿλд�������ֽڵĵ����ݣ�Ҳ��д��32��
        {                         //��Ϊ��д�������ֽ�֮���������Զ���1�����ԾͲ����ٴ�д���ַ�ˡ�
            write_data(0x00);    
        }
    }
    write_cmd(0x36);
    write_cmd(0x30);
}
#endif






void lcd_init_draw(void)
{
	//write_cmd(0x34);//дָ���������ָ�����ͼ��
    //write_cmd(0x36);//8λ���ݴ��䣬��չָ���������ͼ�� 
#if 1    
	     
    write_cmd(0x3E);//8λ���ݴ��䣬��չָ���������ͼ��             
    write_cmd(0x01);//���� 
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
		} while((dl&0x80)!=0);	//��æ 
    res = rd_data;  
    Delay(1);
	return res;
}

/*

д��һ������ӳ��򡣾��岽���ǣ������X�ᡢY��ĵ�ַ��X���еĵڼ�λ��
Ȼ������õ�ַ���ڵ�ֵ����Ϊһ��д���µĵ��ʱ�򣬻Ḳ�ǵ�16�����������㣬
����Ҫͬʱ��ʾ16�����е��������ʱ��ͻ��ͻ�������Ƚ���ʾ�еĵ��������
Ȼ���ڻ���Ҫ�����ĵ㣬�����Ϳ���ͬʱ������ע���ȡ���ݵ�ʱ���ȡ�ĵ�һ�����ݲ�Ҫ��
�ӵڶ����ݿ�ʼȡ��Ҳ����˵Ҫ��ȡ���Σ�ֻȡ�������ε�ֵ��
���о��Ƕ�ȡ����֮ǰҪ��д����Ҫ��ȡ���ݵĵ�ַ����ȡ����֮���д�����ݻ�Ҫ����д���ַ��
�������������ݵ�ַ��������Y�ᣬ������X�ᣬ�������ݡ�

*/


void DrawDots(BYTE x,BYTE y)//��㺯��   //x��yΪ128*64 ���������
{

	WORD bt=0,read=0;
    BYTE x_adr,y_adr,h_bit,l_bit;

	y_adr=0x80+y%32;//����Y��ĵ�ַ��ӦΪ��������64�������ж�32���࣬��Y����31ʱ��Y���������°����ġ�

	if(y>31) //����X��ĵ�ַ��Y����31ʱX�ĵ�ַ���°�������0X88��ʼ��С��31ʱX�ĵ�ַ�����ϰ�������0X80��ʼ
        x_adr=0x88+x/16;        
    else
        x_adr=0x80+x/16;

	bt=0x8000>>(x%16); //������㵽�������ĸ���

	write_cmd(0x34);
    write_cmd(0x36);
    write_cmd(y_adr);     //��ȡ���ݵ�ʱ��Ҫ��д����ȡ���ݵĵ�ַ
    write_cmd(x_adr);

	read_data();         //��ȡ�ĵ�һ���ֽڲ�Ҫ

	read=read_data();     //�ӵڶ����ֽڿ�ʼ���ա�
    read<<=8;
    read|=read_data();
    bt=bt|read;
    h_bit=bt>>8;
    l_bit=bt;

	write_cmd(y_adr);     //д����ʱ������д���ַ����Ϊ��ַ�Ѿ��ı䡣
    write_cmd(x_adr);
    write_data(h_bit);
    write_data(l_bit);

	write_cmd(0x36); //����ʾ
    write_cmd(0x30);     //ת�ػ���ָ�   
}


void DrawDots2(BYTE x,BYTE y,BYTE color)//��㺯��   //x��yΪ128*64 ���������
{
     BYTE row,xlabel,xlabel_bit; 
     BYTE Read_H=0,Read_L=0;  
     write_cmd(0x34);       //����ָ�� 
     write_cmd(0x36);       //��ͼָ�� 
     xlabel=x>>4;            //ȷ��ˮƽ�����ַ
     xlabel_bit=x & 0x0F; // ϸ��ˮƽ�����еĵڼ�λ
     
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
     write_cmd(xlabel+0x80);   //ˮƽ�����ַ+��ַ=��ʾ��ˮƽ��ַ   
     if(xlabel_bit<8) 
     {
          switch(color)
         {
             case 0:Read_H &=(~(0x01<<(7-xlabel_bit))); break; //�䰵 ��������
             case 1:Read_H |=(0x01<<(7-xlabel_bit)); break; //����  �����ü�
             case 2:Read_H ^=(0x01<<(7-xlabel_bit)); break; //��ת
             default:break;
          } 
         write_data(Read_H);
         write_data(Read_L); 
     } 
     else 
     {
          switch(color)
          {
               case 0:Read_L &=(~(0x01<<(15-xlabel_bit))); break; //�䰵    �������� 
               case 1:Read_L |=(0x01<<(15-xlabel_bit)); break; //����  �����ü�
               case 2:Read_L ^=(0x01<<(15-xlabel_bit)); break; //��ת 
               default:break;
          } 
          write_data(Read_H);
          write_data(Read_L);
     } 
     write_cmd(0x30);//�ָ�����ģʽ  
}
void ShowXY(void)
{
	BYTE i = 0,	x = 0,y = 0;
	
    for(i=0;i<62;i++) //����Y��
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