#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
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

//LED端口定义
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


void LED_Init(void);	//初始化		 				    
#endif


















