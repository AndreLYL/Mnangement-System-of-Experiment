#ifndef __MY_GUI_H__
#define __MY_GUI_H__
#include "sys.h"
#include "AS608_add.h"



void verification(void);
void GUI_MENU(void);
void GUI_PersonInformation(void);
void TOUCH_DISP_GUI_PersonInformation(void);
void Input_complish(void);
u8 TOUCH_MENU(void);
void TOUCH_DISP_MENU(void);
void Show_CardID(u8 x,u8 y);
void Show_Information(void);
void GUI_GradeInput_1(void);
void GUI_GradeInput_0(void);
void TOUCH_DISP_GradeInput_1(void);
void TOUCH_Grade_Change(void);
void Show_Change_Information(void);
void GUI_Grade_Change(void);
void GUI_Management(void);
void Main_Management(void);				//Ö÷Ñ­»·³ÌÐò
void Root_Add(void);
void GUI_Grade_Chart(void);
u8 Grade_TOUCH_MENU(void);
u8 TOUCH_GradeInput_1(void);
void GUI_Procent(void);
void TOUCH_DISP_Procent(void);

#endif
