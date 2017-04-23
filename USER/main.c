#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "touch.h"	  
#include "malloc.h" 
#include "usmart.h"  
#include "MMC_SD.h"   
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	
#include "usart2.h"
#include "AS608.h"
#include "timer.h"
#include "AS608_add.h"
#include "my_gui.h"
#include "rc522_add.h"
#include "rc522.h"
#include "AS608_add.h"
#include "RTC.h"
#include "ds18b20.h"




#define usart2_baund  57600//串口2波特率，根据指纹模块波特率更改


int main(void)
{		 

  Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);			  //延时初始化
	uart_init(72,115200); //串口1初始化，用于支持USMART  	  
	LCD_Init();						//初始化液晶 
	KEY_Init();						//按键初始化	  	
	DS18B20_Init();	      //DS18B20初始化	
	RTC_Init();
// 	RTC_Set(2017,4,22,16,32,00);//设置时间，只需设置一次就要屏蔽此函数
	InitRc522();	
	InitAlldata();
	usmart_dev.init(72);	//usmart初始化	
 	usart2_init(36,usart2_baund);	//初始化串口2,用于与指纹模块通讯
	PS_StaGPIO_Init();	  //初始化FR读状态引脚	
	tp_dev.init();				//触摸屏初始化
 	mem_init();						//初始化内存池	    
 	exfuns_init();				//为fatfs相关变量申请内存  
 	f_mount(fs[1],"1:",1); //挂载FLASH.
	POINT_COLOR=BLACK;
	while(font_init()) 			//检查字库
	{	    
		LCD_ShowString(60,50,240,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(60,50,240,66,WHITE);//清除显示
		delay_ms(200);		
	}
	
////**************函数调试区****************//
	
//	TOUCH_DISP_Procent();
//	while(1);
	

	/*加载指纹识别实验界面*/
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	Show_Str(10,40,240,24,"实验室综合管理系统",24,1);	
 	POINT_COLOR=BLUE;
	Show_Str_Mid(0,84,"Connect with AS608....",16,240);	
	while(PS_HandShake(&AS608Addr))//与AS608模块握手
	{
		Show_Str_Mid(0,100,"Cannot connect with AS608!",16,240);
		delay_ms(1000);
		Show_Str_Mid(0,116,"Try to connect again....",16,240);	
		delay_ms(1000);	  
	}
	Show_Str_Mid(0,132,"Connect success!",16,240);//通讯成功
	delay_ms(1000);
	LCD_Fill(0,64,240,320,WHITE);
	Show_Str(50,132,240,16,"请进行指纹验证...",16,1);	


	while(1)
	{
		if(PS_Sta)	 //检测PS_Sta状态，如果有手指按下
		{
			press_FR();//刷指纹			
		}	
		if(FR_Flag==1)
			break;
	}

	while(1)
	{
			Main_Management();
	}
}



