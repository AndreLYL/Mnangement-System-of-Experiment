#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
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

//LED�˿ڶ���
#define UD1 PAout(2)	
#define INC1 PAout(3)	
#define UD2 PAout(9)	
#define INC2 PAout(10)
#define UD3 PAout(11)	
#define INC3 PAout(12)
#define K4 PAout(8)	
#define K1 PDout(2)
#define K2 PCout(11)	
#define K3 PCout(12)


#define LED0 PAout(8)// PA8
#define LED1 PDout(2)// PD2	


void LED_Init(void);	//��ʼ��		 				    
#endif


















