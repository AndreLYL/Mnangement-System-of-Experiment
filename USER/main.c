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




#define usart2_baund  57600//����2�����ʣ�����ָ��ģ�鲨���ʸ���


int main(void)
{		 

  Stm32_Clock_Init(9);	//ϵͳʱ������
	delay_init(72);			  //��ʱ��ʼ��
	uart_init(72,115200); //����1��ʼ��������֧��USMART  	  
	LCD_Init();						//��ʼ��Һ�� 
	KEY_Init();						//������ʼ��	  	
	DS18B20_Init();	      //DS18B20��ʼ��	
	RTC_Init();
// 	RTC_Set(2017,4,22,16,32,00);//����ʱ�䣬ֻ������һ�ξ�Ҫ���δ˺���
	InitRc522();	
	InitAlldata();
	usmart_dev.init(72);	//usmart��ʼ��	
 	usart2_init(36,usart2_baund);	//��ʼ������2,������ָ��ģ��ͨѶ
	PS_StaGPIO_Init();	  //��ʼ��FR��״̬����	
	tp_dev.init();				//��������ʼ��
 	mem_init();						//��ʼ���ڴ��	    
 	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[1],"1:",1); //����FLASH.
	POINT_COLOR=BLACK;
	while(font_init()) 			//����ֿ�
	{	    
		LCD_ShowString(60,50,240,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(60,50,240,66,WHITE);//�����ʾ
		delay_ms(200);		
	}
	
////**************����������****************//
	
//	TOUCH_DISP_Procent();
//	while(1);
	

	/*����ָ��ʶ��ʵ�����*/
	LCD_Clear(WHITE);
	POINT_COLOR=BLACK;
	Show_Str(10,40,240,24,"ʵ�����ۺϹ���ϵͳ",24,1);	
 	POINT_COLOR=BLUE;
	Show_Str_Mid(0,84,"Connect with AS608....",16,240);	
	while(PS_HandShake(&AS608Addr))//��AS608ģ������
	{
		Show_Str_Mid(0,100,"Cannot connect with AS608!",16,240);
		delay_ms(1000);
		Show_Str_Mid(0,116,"Try to connect again....",16,240);	
		delay_ms(1000);	  
	}
	Show_Str_Mid(0,132,"Connect success!",16,240);//ͨѶ�ɹ�
	delay_ms(1000);
	LCD_Fill(0,64,240,320,WHITE);
	Show_Str(50,132,240,16,"�����ָ����֤...",16,1);	


	while(1)
	{
		if(PS_Sta)	 //���PS_Sta״̬���������ָ����
		{
			press_FR();//ˢָ��			
		}	
		if(FR_Flag==1)
			break;
	}

	while(1)
	{
			Main_Management();
	}
}



