#ifndef __AS608_ADD_H
#define __AS608_ADD_H
#include <stdio.h>
#include "stm32f10x.h" 
#include "AS608.h"
#include <string.h>
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
#include "my_gui.h"

void FR_Management(void);
void Add_FR(void);	//录指纹
void Del_FR(void);	//删除指纹
void press_FR(void);//刷指纹
void ShowErrMessage(u8 ensure);//显示确认码错误信息
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//加载虚拟键盘
u8  AS608_get_keynum(u16 x,u16 y);//获取键盘数
u16 GET_NUM(void);//获取数值  


extern u8 FR_Flag;
extern u8** kbd_tbl;
extern u16 ValidN;
extern SysPara AS608Para;

#endif

