#ifndef __AS608_ADD_H
#define __AS608_ADD_H
#include <stdio.h>
#include "stm32f10x.h" 
#include "AS608.h"

void FR_Management(void);
void Add_FR(void);	//¼ָ��
void Del_FR(void);	//ɾ��ָ��
void press_FR(void);//ˢָ��
void ShowErrMessage(u8 ensure);//��ʾȷ���������Ϣ
void AS608_load_keyboard(u16 x,u16 y,u8 **kbtbl);//�����������
u8  AS608_get_keynum(u16 x,u16 y);//��ȡ������
u16 GET_NUM(void);//��ȡ��ֵ  


extern u8 FR_Flag;
extern u8** kbd_tbl;
extern u16 ValidN;
extern SysPara AS608Para;

#endif

