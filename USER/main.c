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
#include "led.h"
#include "timer.h"

u8 flag=0;

#define usart2_baund  57600//串口2波特率，根据指纹模块波特率更改


int main(void)
{		 
	u8 i;
  Stm32_Clock_Init(9);	//系统时钟设置
	delay_init(72);			  //延时初始化
	uart_init(72,115200); //串口1初始化，用于支持USMART  	  
	LCD_Init();						//初始化液晶 
	KEY_Init();						//按键初始化	  	
//	DS18B20_Init();	      //DS18B20初始化	
//	RTC_Init();
// 	RTC_Set(2017,4,22,16,32,00);//设置时间，只需设置一次就要屏蔽此函数
	InitRc522();	
	InitAlldata();
	LED_Init();
//	TIM3_Int_Init(5000,7199);



	while(1)
	{		
		Read_cardID();
		if(cardID[0]==0xE5&&cardID[1]==0x21&&cardID[2]==0x1B&&cardID[3]==0x46)
		{			
				LED0=0;
		}
		else 
				LED0=1;
		cardID[0]=0;
		cardID[1]=0;
		cardID[2]=0;
		cardID[3]=0;
		delay_ms(1000);

	}
}

