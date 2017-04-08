#include "DS18B20.h"
#include "LCD12864.h"
#include "DS12887.h"
#include "timer.h"
#include <intrins.h>

float wen_val;
BYTE ah,al;

BYTE timer_key= 0;
BYTE scale_line_status = 0;
WORD g_base = 0;
WORD new_temprature[BUF_LEN] = {0};
WORD old_temprature[BUF_LEN] = {0};

/*********************************************************
*显示温度程序
**********************************************************/
void crt_wendu(BYTE line,column)
{
	   read_wendu();
	   ah=temperature[1]<<4;
	   ah&=0xf0;
	   al=temperature[0]>>4;
	   al&=0x0f;
	   ah=ah|al;
	   al=temperature[0]&0x0f;
	   if ((ah&0x80)!=0)
	   {
			if (al==0)
			{
			  ah=~ah;ah=ah+1;
			}
			else
			{	
			  ah=~ah;al=~al;al=al+1;al&=0x0f;
			}
			wen_val=ah*(-1.0)+al*(-0.0625);
	   }
	   else 
	   {
	        wen_val=ah*1.0+al*0.0625;
	   }
	   seti_wl(line,column);
	   crt_r(wen_val,1);

	   write_string("  ℃");
	   
	   //write_data(0xA1);
	   //write_data(0xE3);
	   
	   //write_data(0x20);
}

/***************************************************
************  显示时间  *****************************
****************************************************/
void crt_time(BYTE line) 
{
	BYTE dhi,dli;
	set_display_place(line,1);
	dhi=0x32;
	dli=0x30;	
	write_data(dhi);
	write_data(dli);
	dli=Years;//年
	dhi=dli & 0xf0;
    dhi>>=4;
	dhi+=0x30;
	dli &=0x0f;
	dli +=0x30;
	write_data(dhi);
	write_data(dli);
	//dli=0x2d;
	//write_data(dli);
	write_string("-");

	dli=Month;
	dhi=dli & 0xf0;
    dhi>>=4;
	dhi+=0x30;
	dli &=0x0f;
	dli +=0x30;
	write_data(dhi);
	write_data(dli);
	write_string("-");

	dli=Day;
	dhi=dli & 0xf0;
    dhi>>=4;
	dhi+=0x30;
	dli &=0x0f;
	dli +=0x30;
	write_data(dhi);
	write_data(dli);
	//write_string("日");

    set_display_place(line+1,0);
	dli=Hour;
	dhi=dli & 0xf0;
    dhi>>=4;
	dhi+=0x30;
	dli &=0x0f;
	dli +=0x30;
	write_data(dhi);
	write_data(dli);
	dli=0x3a;
	write_data(dli);
	dli=Minute;
	dhi=dli & 0xf0;
    dhi>>=4;
	dhi+=0x30;
	dli &=0x0f;
	dli +=0x30;
	write_data(dhi);
	write_data(dli);
	dli=0x3a;
	write_data(dli);
	dli=Second;
	dhi=dli & 0xf0;
    dhi>>=4;
	dhi+=0x30;
	dli &=0x0f;
	dli +=0x30;
	write_data(dhi);
	write_data(dli);

	write_string_lcd(2,5, "星期");
	dli=Week;
	dli	&= 0x07;
	switch (dli)
	{
		case 7: write_string("日");break;
		case 6: write_string("六");break;
		case 5: write_string("五");break;
		case 4: write_string("四");break;
		case 3: write_data(0xC8);write_data(0xFD);break;//"三"
		case 2: write_string("二");break;
		case 1: write_string("一");
	}
}



/*第二个画面显示时间和当前温度*/

void ShowTime_Temprature(void)
{
	if ((DS_C & 0x10) != 0)//显示时间 
	   {
	   	   crt_time(1);	
		   bzz1=~bzz1;
		   bzz2=~bzz1;
	   }
	   write_string_lcd(3,0, "当前温度: ");
	   crt_wendu(4,8);
	   Delay2(1);
}


/*开机启动的画面*/
void ShowBIOS()
{
	write_string_lcd(1,2," HELLO");
	write_string_lcd(2,2,"欢迎进入");
	write_string_lcd(3,0,"实时温度采集系统");
	write_string_lcd(4,3,"By: 葛思邑");
}


/*键盘扫描程序*/
BYTE KeyScan()
{  
	BYTE num_key=0;//按键号 
    BYTE temp=0;//读取P1口线数据 
    static BYTE temp_code=0;//用于保存按键值 
    static BYTE temp_circle=0xFE;//保存P1线上的循环扫描值 
   
    static BYTE key_flag=0;//按键有效标识 


    P1=temp_circle;//0xFX
    temp=P1;//读取P1口线数据 
    if(temp!=temp_circle)//有按键动作 
    { 
            Delay(5);
            if(P1!=temp_circle)//确实有按键按下
            { 
                    key_flag=1;//按键有效标识置1 
                    temp_code=temp;//保存按键值 
            } 
    } 
    else//松手OR无按键动作,此时应该改变扫描线 
    { 
            if(key_flag==1)//按键有效判断 
            { 
                    key_flag=0; 
                    switch(temp_code)//读取按键号 
                    { 
                            //P1^0线 
                            case 0xEE: num_key=1; 
                                       break; 
                            case 0xDE: num_key=2; 
                                       break; 
                            case 0xBE: num_key=3; 
                                       break; 
                            case 0x7E: num_key=4; 
                                       break; 
                            //P1^1线 
                            case 0xED: num_key=5; 
                                       break; 
                            case 0xDD: num_key=6; 
                                       break; 
                            case 0xBD: num_key=7; 
                                       break; 
                            case 0x7D: num_key=8; 
                                       break; 
                            //P1^2线 
                            case 0xEB: num_key=9; 
                                       break; 
                            case 0xDB: num_key=10; 
                                       break; 
                            case 0xBB: num_key=11; 
                                       break; 
                            case 0x7B: num_key=12; 
                                       break; 
                            //P1^3线 
                            case 0xE7: num_key=13; 
                                       break; 
                            case 0xD7: num_key=14; 
                                       break; 
                            case 0xB7: num_key=15; 
                                       break; 
                            case 0x77: num_key=16; 
                                       break; 
                    } 
            } 
            temp_circle=_crol_(temp_circle,1);//改变扫描线 
            if(temp_circle==0xEF) 
            { 
                    temp_circle=0xFE; 
            } 
    } 
    return(num_key);//返回按键号 
}

/*更新历史数据--最新的历史数据*/
void UpdateNewTemprature()
{
	BYTE i = 0;

	for(i = 0;i < BUF_LEN-1;i++)
	{
	 	 new_temprature[i] =  new_temprature[i+1];
	}
	get_wendu();

   	new_temprature[BUF_LEN-1]  = (WORD)(wen_val*100);
}

/*更新历史数据--上一次画完柱状图以后对应的历史数据--用来进行增量计算*/
void UpdateOldTemprature()
{
	BYTE i = 0, j = 0;

	for(i = 0;i < BUF_LEN;i++)
	{
	 	 old_temprature[i] =  new_temprature[i];
	}
}


/*主函数*/
void main()
{
	
	BYTE key_num = 0;
	BYTE status = 1;
	
	BYTE show_scale_line_flag = 0;//表明K3按下去的标志
	BYTE first_time_scale = 0;//本次开机以后第一次启动第三个画面的标志--用来清屏	
	SP=0x60;
	lcd_init();	//LCD初始化
	//TimerInit();
	DS_init();//实时时钟初始化
	//write_time();   //DS12C887时间设置，只需要调用一次就应该注释掉--实时时钟芯片的特性
	
	DS18B20_Init();	//温度传感器初始化
	get_wendu();//获取温度--温度值在全局变量
	g_base = (WORD)((wen_val-1)*100);//获取基准值
		 

	while(1)			   
	{
		  key_num =KeyScan();
		  if(key_num != 0)
		  {	 
		  		if(key_num == 3)   //切换到第三个画面
				{
					lcd_init();
					scale_line_status = 1;
					if(first_time_scale == 0)//只在第一次切换到第三个画面的时候清屏--清屏太慢了
					{
						clear_lcd(); 
					}
					lcd_init_draw();
					if(first_time_scale == 0)//只在第一次切换到第三个画面的时候画坐标
						ShowXY();
					first_time_scale = 1;	
					show_scale_line_flag = 1;
					TimerInit();  //启动定时器
				}
				else if(key_num == 1 ||key_num == 2){ //切换到第一/第二个画面，不需要定时器
					 ET0 = 0; //不允许T0中断
					 TR0 = 0;  //关闭定时器
		  			lcd_init();
				}
				status = key_num; //更新显示的状态机
		  }
		  if(scale_line_status == 1) //定时器定时时间到了
		  {
				UpdateNewTemprature();
				scale_line_status = 2;//该更新柱状图了
		  }
		  switch(status) //处理状态机
		  {
		  		case 1:
					ShowBIOS();//显示开机画面
					break;
				case 2:	 //显示温度时间画面
					ShowTime_Temprature();
					break;
				case 3://显示柱状图
					if(show_scale_line_flag == 1 || scale_line_status == 2){//当按键K3按下或者在已经按下按键的情况下，定时时间到了--更新柱状图
						
						UpdateScaleLine();//更新/画柱状图
						scale_line_status = 3; //不要再更新了--否则一直画图会闪烁--等待下一次定时时间到再更新
						UpdateOldTemprature(); //更新旧的历史数据--用来做下一次的增量计算
						show_scale_line_flag = 0; //按键已经按下了，我也处理了---不要再更新柱状图了--否则会闪烁--等待下一次按键按下再更新
					}
					
					break;
				default:
					break;
		  }   
	}
}