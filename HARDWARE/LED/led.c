#include "sys.h"   
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//LED驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/05
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//初始化PA8和PD2为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //使能PORTA时钟	   	 
	RCC->APB2ENR|=1<<4;    //使能PORTC时钟	
	RCC->APB2ENR|=1<<5;    //使能PORTD时钟	

	
		GPIOA->CRL&=0XFFFFFF0F; 
	  GPIOA->CRL|=0X00000030;//PA1 推挽输出   	 
    GPIOA->ODR|=1<<1;      //PA1 输出高
		
		GPIOA->CRL&=0XFFFFF0FF; 
	  GPIOA->CRL|=0X00000300;//PA2 推挽输出   	 
    GPIOA->ODR|=1<<2;      //PA2 输出高
		
		GPIOA->CRL&=0XFFFF0FFF; 
	  GPIOA->CRL|=0X00003000;//PA3 推挽输出   	 
    GPIOA->ODR|=1<<3;      //PA3 输出高
			
		GPIOA->CRL&=0XFFF0FFFF; 
	  GPIOA->CRL|=0X00030000;//PA4 推挽输出   	 
    GPIOA->ODR|=1<<4;      //PA4 输出高
			
		GPIOA->CRL&=0XFF0FFFFF; 
	  GPIOA->CRL|=0X00300000;//PA5 推挽输出   	 
    GPIOA->ODR|=1<<5;      //PA5 输出高
			
		GPIOA->CRL&=0XF0FFFFFF; 
	  GPIOA->CRL|=0X03000000;//PA6 推挽输出   	 
    GPIOA->ODR|=1<<6;      //PA6 输出高
					
		GPIOA->CRL&=0X0FFFFFFF; 
	  GPIOA->CRL|=0X30000000;//PA7 推挽输出   	 
    GPIOA->ODR|=1<<7;      //PA7 输出高
	
		GPIOA->CRH&=0XFFFFFFF0; 
	  GPIOA->CRH|=0X00000003;//PA8 推挽输出   	 
    GPIOA->ODR|=1<<8;      //PA8 输出高
		
		GPIOA->CRH&=0XFFFFFF0F; 
	  GPIOA->CRH|=0X00000030;//PA9 推挽输出   	 
    GPIOA->ODR|=1<<9;      //PA9 输出高
	
		GPIOA->CRH&=0XFFFFF0FF; 
	  GPIOA->CRH|=0X00000300;//PA10 推挽输出   	 
    GPIOA->ODR|=1<<10;      //PA10 输出高
			
		GPIOA->CRH&=0XFFFF0FFF; 
	  GPIOA->CRH|=0X00003000;//PA11 推挽输出   	 
    GPIOA->ODR|=1<<11;      //PA11 输出高
			
		GPIOA->CRH&=0XFFF0FFFF; 
	  GPIOA->CRH|=0X00030000;//PA12 推挽输出   	 
    GPIOA->ODR|=1<<12;      //PA12 输出高
			
	  GPIOD->CRL&=0XFFFFF0FF;
	  GPIOD->CRL|=0X00000700;//PD2推挽输出
	  GPIOD->ODR|=1<<2;      //PD2输出高 
				
		GPIOC->CRH&=0XFFFF0FFF; 
	  GPIOC->CRH|=0X00003000;//PC11 推挽输出   	 
    GPIOC->ODR|=1<<11;      //PC11 输出高
			
		GPIOC->CRH&=0XFFF0FFFF; 
	  GPIOC->CRH|=0X00030000;//PC12 推挽输出   	 
    GPIOC->ODR|=1<<12;      //PC12 输出高
		


}







