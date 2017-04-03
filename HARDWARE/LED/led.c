#include "sys.h"   
#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK Mini STM32������
//LED��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/05
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//��ʼ��PA8��PD2Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;    //ʹ��PORTAʱ��	   	 
	RCC->APB2ENR|=1<<4;    //ʹ��PORTCʱ��	
	RCC->APB2ENR|=1<<5;    //ʹ��PORTDʱ��	

	
		GPIOA->CRL&=0XFFFFFF0F; 
	  GPIOA->CRL|=0X00000030;//PA1 �������   	 
    GPIOA->ODR|=1<<1;      //PA1 �����
		
		GPIOA->CRL&=0XFFFFF0FF; 
	  GPIOA->CRL|=0X00000300;//PA2 �������   	 
    GPIOA->ODR|=1<<2;      //PA2 �����
		
		GPIOA->CRL&=0XFFFF0FFF; 
	  GPIOA->CRL|=0X00003000;//PA3 �������   	 
    GPIOA->ODR|=1<<3;      //PA3 �����
			
		GPIOA->CRL&=0XFFF0FFFF; 
	  GPIOA->CRL|=0X00030000;//PA4 �������   	 
    GPIOA->ODR|=1<<4;      //PA4 �����
			
		GPIOA->CRL&=0XFF0FFFFF; 
	  GPIOA->CRL|=0X00300000;//PA5 �������   	 
    GPIOA->ODR|=1<<5;      //PA5 �����
			
		GPIOA->CRL&=0XF0FFFFFF; 
	  GPIOA->CRL|=0X03000000;//PA6 �������   	 
    GPIOA->ODR|=1<<6;      //PA6 �����
					
		GPIOA->CRL&=0X0FFFFFFF; 
	  GPIOA->CRL|=0X30000000;//PA7 �������   	 
    GPIOA->ODR|=1<<7;      //PA7 �����
	
		GPIOA->CRH&=0XFFFFFFF0; 
	  GPIOA->CRH|=0X00000003;//PA8 �������   	 
    GPIOA->ODR|=1<<8;      //PA8 �����
		
		GPIOA->CRH&=0XFFFFFF0F; 
	  GPIOA->CRH|=0X00000030;//PA9 �������   	 
    GPIOA->ODR|=1<<9;      //PA9 �����
	
		GPIOA->CRH&=0XFFFFF0FF; 
	  GPIOA->CRH|=0X00000300;//PA10 �������   	 
    GPIOA->ODR|=1<<10;      //PA10 �����
			
		GPIOA->CRH&=0XFFFF0FFF; 
	  GPIOA->CRH|=0X00003000;//PA11 �������   	 
    GPIOA->ODR|=1<<11;      //PA11 �����
			
		GPIOA->CRH&=0XFFF0FFFF; 
	  GPIOA->CRH|=0X00030000;//PA12 �������   	 
    GPIOA->ODR|=1<<12;      //PA12 �����
			
	  GPIOD->CRL&=0XFFFFF0FF;
	  GPIOD->CRL|=0X00000700;//PD2�������
	  GPIOD->ODR|=1<<2;      //PD2����� 
				
		GPIOC->CRH&=0XFFFF0FFF; 
	  GPIOC->CRH|=0X00003000;//PC11 �������   	 
    GPIOC->ODR|=1<<11;      //PC11 �����
			
		GPIOC->CRH&=0XFFF0FFFF; 
	  GPIOC->CRH|=0X00030000;//PC12 �������   	 
    GPIOC->ODR|=1<<12;      //PC12 �����
		


}







