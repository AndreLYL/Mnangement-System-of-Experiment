#include "my_gui.h"
#include "lcd.h"
#include "text.h"
#include "touch.h"
#include "delay.h"
#include "ds18b20.h"
#include "rtc.h"
#include "rc522.h"
#include "rc522_add.h"
#include "piclib.h"	
#include "usart.h"

int input[5]={0,0,0,0,0};
u8 length=0;
u8 EX_number;					//实验编号
u8 card_status=0;
int Grade1=0,Grade2=0;
u8 Daily_Procent=20,Test_Procent=80;
u8 major[2]={1,2};




struct Student
{
	u8 studentID[4];				//学生学号
	char studentname[10];		//学生姓名
	int dailyscore1;			//预习成绩
	int testscore2;			//实验成绩
	int score;				//总成绩
};

struct Student Stu[30]={{0,0,0,0},0,0,0};			//声明一个结构体数组
u8 Stu_number=0;
u8 Change_number=0;
u8 Change_flag=0;

//白名单
u8 Root_ID[30][4];
u8 Root_number=0;
u8 Root_flag;




//*********************************************************************//
//************************实验管理*************************************//
//*********************************************************************//
void GUI_Experiment(void)
{
		POINT_COLOR=BLACK; 
		LCD_DrawLine(0, 39, 239, 39);			//横     
		LCD_DrawLine(0, 85, 239, 85);			//横
		LCD_DrawLine(0, 79+60, 239, 79+60);		//横
		LCD_DrawLine(0, 79+120, 239, 79+120);	//横
		LCD_DrawLine(0, 79+180, 239, 79+180);	//横
		LCD_DrawLine(59, 79+60, 59, 319);			//竖
		LCD_DrawLine(119, 0, 119, 319);			//竖
		LCD_DrawLine(179, 79+60, 179, 319);		//竖
		POINT_COLOR=BLACK;  
		Show_Str(20,10,240,16,"专业班级",16,0);
		Show_Str(20,10+40+6,240,16,"实验编号",16,0);
		Show_Str(20,10+40+60-5,240,16,"退出程序",16,0);
		Show_Str(120+45,10+40+60-5,240,16,"确定",16,0);
		Show_Str(180+10+5,10+40+60+60-5,240,16,"重输",16,0);

		POINT_COLOR=BLACK;  
		LCD_ShowNum(26,162,0,1,16);
		LCD_ShowNum(86,162,1,1,16);
		LCD_ShowNum(146,162,2,1,16);

		LCD_ShowNum(26,222,3,1,16);
		LCD_ShowNum(86,222,4,1,16);
		LCD_ShowNum(146,222,5,1,16);
		LCD_ShowNum(206,222,6,1,16);

		LCD_ShowNum(26,282,7,1,16);
		LCD_ShowNum(86,282,8,1,16);
		LCD_ShowNum(146,282,9,1,16);
		LCD_ShowChar(206,282,'.',16,0);
}


void TOUCH_DISP_Experiment(void)  //实验编号键值处理
{
	u8 key;
	u8 num=0;
	u8 ii=0;
	u8 queding_Flag=0;

	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;

	LCD_Clear(0xC7FF);//清屏
	GUI_Experiment();
	while(1)
	{
		key=TOUCH_GradeInput_1();	 //获取触摸键值y
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_Experiment();  				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		Main_Management(); 	       //退出程序
								break;

			case 2:		
								queding_Flag++;
								if(queding_Flag==1) 
									 num=0;
								if(queding_Flag==2) 
								{		
									major[0] = input[0];
									major[1] = input[1];
									EX_number = input[2]*10+input[3];					
									LCD_Clear(0xC7FF);//清屏
									TOUCH_DISP_Procent();
								}
								break;

			case 3:		if(ii>=4)	break;    //输入数值不超过4位数  //输入0
						else
						{
							num++;
							input[ii]=0;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'0',16,0);		 //0 
							break;
						}

			case 4:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=1;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'1',16,0);		 //1
							break;
						}

			case 5:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=2;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'2',16,0);		 //2
							break;
						}

			case 6:		num=0;
						ii=0;
						input[0]=0;
						input[1]=0;
						input[2]=0;
						input[3]=0;
						input[4]=0;
						length=0;	
						queding_Flag=0;
						LCD_Fill(150,10,200,30,0xC7FF);			   		 //重输
						LCD_Fill(150,56,200,86,0xC7FF);			   		 //重输
						break;

			case 7:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=3;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'3',16,0);		 //3
							break;
						}

			case 8:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=4;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'4',16,0);		 //4
							break;
						}

			case 9:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=5;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'5',16,0);		 //5
							break;
						}

			case 10:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=6;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'6',16,0);		 //6
							break;
						}

			case 11:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=7;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'7',16,0);		 //7
							break;
						}

			case 12:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=8;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'8',16,0);		 //8
							break;
						}

			case 13:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=9;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'9',16,0);		 //9
							break;
						}

			case 14:    break;//小数点无效

			default:	break;
		}



	}
}



//*********************************************************************//
//************************成绩比例*************************************//
//*********************************************************************//
void GUI_Procent(void)
{
		POINT_COLOR=BLACK; 
		LCD_DrawLine(0, 39, 239, 39);			//横     
		LCD_DrawLine(0, 85, 239, 85);			//横
		LCD_DrawLine(0, 79+60, 239, 79+60);		//横
		LCD_DrawLine(0, 79+120, 239, 79+120);	//横
		LCD_DrawLine(0, 79+180, 239, 79+180);	//横
		LCD_DrawLine(59, 79+60, 59, 319);			//竖
		LCD_DrawLine(119, 0, 119, 319);			//竖
		LCD_DrawLine(179, 79+60, 179, 319);		//竖
		POINT_COLOR=BLACK;  
		Show_Str(10,10,240,16,"平时成绩比例",16,0);
		Show_Str(10,10+40+6,240,16,"实验成绩比例",16,0);
		Show_Str(20,10+40+60-5,240,16,"退出程序",16,0);
		Show_Str(120+45,10+40+60-5,240,16,"确定",16,0);
		Show_Str(180+10+5,10+40+60+60-5,240,16,"重输",16,0);

		POINT_COLOR=BLACK;  
		LCD_ShowNum(26,162,0,1,16);
		LCD_ShowNum(86,162,1,1,16);
		LCD_ShowNum(146,162,2,1,16);

		LCD_ShowNum(26,222,3,1,16);
		LCD_ShowNum(86,222,4,1,16);
		LCD_ShowNum(146,222,5,1,16);
		LCD_ShowNum(206,222,6,1,16);

		LCD_ShowNum(26,282,7,1,16);
		LCD_ShowNum(86,282,8,1,16);
		LCD_ShowNum(146,282,9,1,16);
		LCD_ShowChar(206,282,'.',16,0);
}


void TOUCH_DISP_Procent(void)  //实验编号键值处理
{
	u8 key;
	u8 num=0;
	u8 ii=0,i=0;
	u8 queding_Flag=0;

	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;

	LCD_Clear(0xC7FF);//清屏
	GUI_Procent();
	while(1)
	{
		key=TOUCH_GradeInput_1();	 //获取触摸键值y
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_Procent();  				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		Main_Management(); 	       //退出程序
								break;

			case 2:		
								queding_Flag++;
								if(queding_Flag==1) 
									 num=0;
								if(queding_Flag==2) 
								{		
									Daily_Procent = input[0]*10+input[1];
									Test_Procent = input[2]*10+input[3];					
									LCD_Clear(0xC7FF);//清屏
									Main_Management();
								}
								break;

			case 3:		if(ii>=4)	break;    //输入数值不超过4位数  //输入0
						else
						{
							num++;
							input[ii]=0;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'0',16,0);		 //0 
							break;
						}

			case 4:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=1;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'1',16,0);		 //1
							break;
						}

			case 5:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=2;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'2',16,0);		 //2
							break;
						}

			case 6:		num=0;
						ii=0;
						input[0]=0;
						input[1]=0;
						input[2]=0;
						input[3]=0;
						input[4]=0;
						length=0;	
						queding_Flag=0;
						LCD_Fill(150,10,200,30,0xC7FF);			   		 //重输
						LCD_Fill(150,56,200,86,0xC7FF);			   		 //重输
						break;

			case 7:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=3;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'3',16,0);		 //3
							break;
						}

			case 8:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=4;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'4',16,0);		 //4
							break;
						}

			case 9:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=5;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'5',16,0);		 //5
							break;
						}

			case 10:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=6;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'6',16,0);		 //6
							break;
						}

			case 11:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=7;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'7',16,0);		 //7
							break;
						}

			case 12:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=8;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'8',16,0);		 //8
							break;
						}

			case 13:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=9;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'9',16,0);		 //9
							break;
						}

			case 14:    break;//小数点无效

			default:	break;
		}


//		delay_ms(10);//每过10ms查询一次触摸屏

	}
}










void GUI_MENU(void)         //主菜单
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);										//横
	LCD_DrawLine(0, 39+70+20, 239, 39+70+20);				//横
	LCD_DrawLine(0, 39+70+70+40, 239, 39+70+70+40); //横
	LCD_DrawLine(119, 39, 119, 319);								//竖
	
	POINT_COLOR=BLUE; 
	Show_Str(100,10,240,16,"菜单栏",16,1);
	Show_Str(39+5-15,75,240,16,"成绩录入",16,0);
	Show_Str(39+120+5-15,75,240,16,"成绩修改",16,0);
	Show_Str(39+5-15,75+90,240,16,"成绩提交",16,0);
	Show_Str(39+30+120-40,75+90,240,16,"成绩查看",16,0);
	
	POINT_COLOR=BLACK; 
	Show_Str(5+10,39+70+70+40+11,240,16,"今天的温度",16,1);
	Show_Str(5+10+120,39+70+70+40+11,240,16,"日期和时间",16,1);
	
}





u8 TOUCH_MENU(void)
{

		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
			if(tp_dev.x[0]>0&&tp_dev.x[0]<119&&tp_dev.y[0]>39&&tp_dev.y[0]<129)
			{
				while(PEN==0)
				{
					LCD_Fill(0,39,119,129,BLACK);
				}
				LCD_Fill(0,39,119,129,0xC7FF);
				return 1;
			}
			else if(tp_dev.x[0]>119&&tp_dev.x[0]<239&&tp_dev.y[0]>39&&tp_dev.y[0]<129)
			{
				while(PEN==0)
				{
					LCD_Fill(119,39,239,129,BLACK);
				}
				LCD_Fill(119,39,239,129,0xC7FF);
				return 2;
			}
			else if(tp_dev.x[0]>0&&tp_dev.x[0]<119&&tp_dev.y[0]>129&&tp_dev.y[0]<219)
			{
				while(PEN==0)
				{
					LCD_Fill(0,129,119,219,BLACK);
				}
				LCD_Fill(0,129,119,219,0xC7FF);
				return 3;
			}
			else if(tp_dev.x[0]>119&&tp_dev.x[0]<239&&tp_dev.y[0]>129&&tp_dev.y[0]<219)
			{
				while(PEN==0)
				{
					LCD_Fill(119,129,239,219,BLACK);
				}
				LCD_Fill(119,129,239,219,0xC7FF);
				return 4;
			}
						
			else return 0;
		}else delay_ms(10);	
		return 0;
}

u8 Grade_TOUCH_MENU(void)
{

		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
			if(tp_dev.x[0]>0&&tp_dev.x[0]<119&&tp_dev.y[0]>39&&tp_dev.y[0]<129)
			{
				while(PEN==0)
				{
					LCD_Fill(0,39,119,129,BLACK);
				}
				LCD_Fill(0,39,119,129,0xC7FF);
				return 1;
			}
			else if(tp_dev.x[0]>119&&tp_dev.x[0]<239&&tp_dev.y[0]>39&&tp_dev.y[0]<129)
			{
				while(PEN==0)
				{
					LCD_Fill(119,39,239,129,BLACK);
				}
				LCD_Fill(119,39,239,129,0xC7FF);
				return 2;
			}
			else if(tp_dev.x[0]>0&&tp_dev.x[0]<119&&tp_dev.y[0]>129&&tp_dev.y[0]<219)
			{
				while(PEN==0)
				{
					LCD_Fill(0,129,119,219,BLACK);
				}
				LCD_Fill(0,129,119,219,0xC7FF);
				return 3;
			}
			else if(tp_dev.x[0]>119&&tp_dev.x[0]<239&&tp_dev.y[0]>129&&tp_dev.y[0]<219)
			{
				while(PEN==0)
				{
					LCD_Fill(119,129,239,219,BLACK);
				}
				LCD_Fill(119,129,239,219,0xC7FF);
				return 4;
			}
			else if(tp_dev.x[0]>0&&tp_dev.x[0]<239&&tp_dev.y[0]>219&&tp_dev.y[0]<319)
			{
				while(PEN==0)
				{
					;
				}
				return 5;
			}
						
			else return 0;
		}else delay_ms(10);	
		return 0;
}


void TOUCH_DISP_MENU(void)				//主循环程序
{
	u8 key;
	u8 t=0;	
	short temp; 
	
	card_status=0;//状态清零

// 	Touch_Init();	 //初始化 
	LCD_Clear(0xC7FF);//清屏

	GUI_MENU();         //菜单栏显示触摸界面
	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60+65+10,130+70+40+20,200,16,16,"    -  -  ");	   
	LCD_ShowString(60+65+15,162+70+40+20,200,16,16,"  :  :  ");		    

	
	//显示温度
	POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(10,250+20,200,16,16, "      . C");	 

	
	while(1)
	{
									    
		
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(60+65+10,130+70+40+20,calendar.w_year,4,16);									  
			LCD_ShowNum(100+65+10,130+70+40+20,calendar.w_month,2,16);									  
			LCD_ShowNum(124+65+10,130+70+40+20,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Saturday ");
					break;  			
			}
			LCD_ShowNum(60+65+15,162+70+40+20,calendar.hour,2,16);									  
			LCD_ShowNum(84+65+15,162+70+40+20,calendar.min,2,16);									  
			LCD_ShowNum(108+65+15,162+70+40+20,calendar.sec,2,16);
		
		}
		
		
		//更新温度
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140-110,250+20,'-',16,0);//显示负号	
		}						 
		LCD_ShowNum(148-110,250+20,temp/10,2,16);//显示温度值	  
		LCD_ShowNum(172-110,250+20,temp%10,1,16);//显示温度值
				

		key=Grade_TOUCH_MENU(); //获取触摸键值
		switch(key)			       //相应键值的处理
		{
			case 0:		GUI_MENU();  				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		GUI_GradeInput_0(); 	  //成绩录入
								break;

			case 2:		GUI_Grade_Change(); 		   		//成绩修改
								break;

			case 3:		Input_complish();   		 		//成绩提交
								break;

			case 4:		GUI_Grade_Chart();          //生成报表
								break;

			case 5:		Main_Management();          //生成报表
					      break;



			default:	break;
		}
		
		delay_ms(10);//每过10ms查询一次触摸屏

	 }
}





void GUI_PersonInformation(void)
{
	
	LCD_DrawLine(2, 2, 238, 2);		
	LCD_DrawLine(2, 2, 2, 318);
	LCD_DrawLine(120, 40, 238, 40);
	LCD_DrawLine(120, 80, 238, 80);
	LCD_DrawLine(120, 120, 238, 120);
	LCD_DrawLine(238, 2, 238, 318);		
	LCD_DrawLine(2, 318, 238, 318);
	LCD_DrawLine(2, 160, 238, 160);		
	LCD_DrawLine(120, 2, 120, 160);	
	LCD_DrawLine(2, 200, 238, 200);		
	LCD_DrawLine(2, 240, 238, 240);
	LCD_DrawLine(2, 280, 238, 280);
	LCD_DrawLine(120,160, 120, 318);
//	
	Show_Str(28,172,240,16,"平时成绩",16,1);
	Show_Str(28,212,240,16,"实验成绩",16,1);
	Show_Str(28,252,240,16,"最终成绩",16,1);
	Show_Str(44,292,240,16,"确定",16,1);
	Show_Str(163,292,240,16,"取消",16,1);
	Show_CardID(132,128);
	if(Change_flag==0)
		Show_Information();
	else
	{
		Show_Change_Information();
	}
}

void Show_Information(void)
{
	char a[5],b[5],c[5];
	Show_Str(150,20,240,16,"乔布斯",16,1); 
	Show_Str(145,55,240,16,"信控学院",16,1);
	Show_Str(130,90,240,16,"自动化1302班",16,1);
	sprintf((char*)a,"%d",Stu[Stu_number].dailyscore1);
	sprintf((char*)b,"%d",Stu[Stu_number].testscore2);
	sprintf((char*)c,"%d",Stu[Stu_number].score);
	Show_Str(150,172,240,16,a,16,1);
	Show_Str(150,212,240,16,b,16,1);
	Show_Str(150,252,240,16,c,16,1);
}

void Show_Change_Information(void)
{
	char a[5],b[5],c[5];
	Show_Str(150,20,240,16,"乔布斯",16,1); 
	Show_Str(145,55,240,16,"信控学院",16,1);
	Show_Str(130,90,240,16,"自动化1302班",16,1);
	sprintf((char*)a,"%d",Stu[Change_number].dailyscore1);
	sprintf((char*)b,"%d",Stu[Change_number].testscore2);
	sprintf((char*)c,"%d",Stu[Change_number].score);
	Show_Str(150,172,240,16,a,16,1);
	Show_Str(150,212,240,16,b,16,1);
	Show_Str(150,252,240,16,c,16,1);
}
void Show_CardID(u8 x,u8 y)
{
	u8 	ii=0;
	Read_cardID();
	for(ii=0;ii<4;ii++)//显示卡号（如：将卡号0x34 0xb2 0x30 0xeb 显示成 052 178 030 235）
	{
		if(cardID[ii] >= 100)
			LCD_ShowNum(x+ii*8*3,y,cardID[ii],3,16);//显示ID（3位10进制数）
		else if((cardID[ii] >= 10) && (cardID[ii] < 100))
		{
			if(ii == 0)
			{
				LCD_ShowNum(x+(ii+1)*8,y,cardID[ii],2,16);
			}else LCD_ShowNum(x+ii*8*3+8,y,cardID[ii],2,16);
			LCD_ShowNum(x+ii*8*3,y,0,1,16);		
		}	
		else if(cardID[ii] < 10)
		{
			if(ii == 0)
			{
				LCD_ShowNum(x+(ii+2)*8,y,cardID[ii],1,16);
			}else LCD_ShowNum(x+ii*8*3+8*2,y,cardID[ii],1,16);			
			LCD_ShowNum(x+ii*8*3,y,00,2,16);
		}
	}

}

u8 TOUCH_GUI_PersonInformation(void)
{
	tp_dev.scan(0); 		 
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]>3&&tp_dev.x[0]<119&&tp_dev.y[0]>281&&tp_dev.y[0]<317)
		{
			while(PEN==0)
			{
				LCD_Fill(3,281,119,317,BLACK);
			}
			LCD_Fill(3,281,119,317,0xC7FF);
			return 1;
		}
		else if(tp_dev.x[0]>121&&tp_dev.x[0]<237&&tp_dev.y[0]>281&&tp_dev.y[0]<317)
		{
			while(PEN==0)
			{
				LCD_Fill(121,281,237,317,BLACK);
			}
			LCD_Fill(121,281,237,317,0xC7FF);
			return 2;
		}
					
		else return 0;
	}else delay_ms(10);	
	return 0;
}








void TOUCH_DISP_GUI_PersonInformation()
{
	u8 key;
//	u8 *pname;	

	
		while(1)
		{
			key=TOUCH_GUI_PersonInformation();
			switch(key)
			{
				case 0:	GUI_PersonInformation();
								break;
				case 1:	Stu_number++;
								flag_com=0;
								Change_number=0;
								Change_flag=0;
					      TOUCH_DISP_MENU();
								break;
				case 2: flag_com=0;
								Change_number=0;
								Change_flag=0;
								TOUCH_DISP_MENU();
								break;
								
				default:	break;
			
			
			}
			delay_ms(10);//每过10ms查询一次触摸屏
		}


}


void Input_complish(void)
{
		u8 x;
		LCD_Clear(0xC7FF);//清屏
		printf("实验编号：00%d\r\n",EX_number);
		switch(major[0])
		{
			case 1:
				printf("专业: 测控");
				break;
			case 2:
				printf("专业：电气及其自动化");
				break;
			case 3:
				printf("专业：自动化");
				break;
			case 4:
				printf("专业：电子信息工程");
				break;
		}
	  switch(major[1])
		{
			case 1:
				printf("1301班\r\n");
				break;
			case 2:
				printf("1302班\r\n");
				break;
			case 3:
				printf("1303班\r\n");
				break;
			case 4:
				printf("1304班\r\n");
				break;
			case 5:
				printf("1305班\r\n");
				break;			
			case 6:
				printf("1306班\r\n");
				break;
		}
		printf("成绩信息：\r\n");
		for(x=0;x<30;x++)																										//串口提交成绩信息
		{
			printf("%d\t%d%d%d%d\t%d\t%d\t%d\r\n",x+1,Stu[x].studentID[0],Stu[x].studentID[1],Stu[x].studentID[2],Stu[x].studentID[3],
			Stu[x].dailyscore1,Stu[x].testscore2,Stu[x].score);
		}
		
		LCD_DrawRectangle(40, 152, 200, 168);		   				//画矩形
		for(x=0;x<50;x++)
		{
			LCD_Fill(40+1,152+1,41+(int)(3.2*x),168-1,GREEN);	 
			delay_ms(10);
		}
		Show_Str(80,172,240,16,"成绩已提交！",16,1);
		delay_ms(1000);
		TOUCH_DISP_MENU();
}

void GUI_GradeInput_0(void)
{
	LCD_Clear(0xC7FF);//清屏
	Show_Str(85,120,240,16,"请刷卡",16,1);
	Show_Str(35,150,240,16,"触摸任一点返回主菜单",16,1);
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>0&&tp_dev.y[0]<320)
			{
				while(PEN==0)
				{
					TOUCH_DISP_MENU();
				}
			}
					
		}else delay_ms(10);	
		if(flag_com==0)
		{
			Read_cardID();
		}
		else
		{
			  LCD_Clear(0xC7FF);//清屏
			  TOUCH_DISP_GradeInput_1();
		}
	}
	
}


/***************************************/
//*************成绩录入*****************/
/***************************************/

void GUI_GradeInput_1(void)
{
		POINT_COLOR=BLACK; 
		LCD_DrawLine(0, 39, 239, 39);			//横     
		LCD_DrawLine(0, 85, 239, 85);			//横
		LCD_DrawLine(0, 79+60, 239, 79+60);		//横
		LCD_DrawLine(0, 79+120, 239, 79+120);	//横
		LCD_DrawLine(0, 79+180, 239, 79+180);	//横
		LCD_DrawLine(59, 79+60, 59, 319);			//竖
		LCD_DrawLine(119, 0, 119, 319);			//竖
		LCD_DrawLine(179, 79+60, 179, 319);		//竖
		POINT_COLOR=BLACK;  
		Show_Str(20,10,240,16,"平时成绩",16,0);
		Show_Str(20,10+40+6,240,16,"实验成绩",16,0);
		Show_Str(20,10+40+60-5,240,16,"退出程序",16,0);
		Show_Str(120+45,10+40+60-5,240,16,"确定",16,0);
		Show_Str(180+10+5,10+40+60+60-5,240,16,"重输",16,0);

		POINT_COLOR=BLACK;  
		LCD_ShowNum(26,162,0,1,16);
		LCD_ShowNum(86,162,1,1,16);
		LCD_ShowNum(146,162,2,1,16);

		LCD_ShowNum(26,222,3,1,16);
		LCD_ShowNum(86,222,4,1,16);
		LCD_ShowNum(146,222,5,1,16);
		LCD_ShowNum(206,222,6,1,16);

		LCD_ShowNum(26,282,7,1,16);
		LCD_ShowNum(86,282,8,1,16);
		LCD_ShowNum(146,282,9,1,16);
		LCD_ShowChar(206,282,'.',16,0);

}


u8 TOUCH_GradeInput_1(void)
{

		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
			if(tp_dev.x[0]>0&&tp_dev.x[0]<119&&tp_dev.y[0]>85&&tp_dev.y[0]<139)
			{
				while(PEN==0)
				{
					LCD_Fill(0,85,119,139,BLACK);
				}
				LCD_Fill(0,85,119,139,0xC7FF);
				return 1;
			}
			else if(tp_dev.x[0]>119&&tp_dev.x[0]<239&&tp_dev.y[0]>85&&tp_dev.y[0]<139)
			{
				while(PEN==0)
				{
					LCD_Fill(119,85,239,139,BLACK);
				}
				LCD_Fill(119,85,239,139,0xC7FF);
				return 2;
			}
			else if(tp_dev.x[0]>0&&tp_dev.x[0]<59&&tp_dev.y[0]>139&&tp_dev.y[0]<199)
			{
				while(PEN==0)
				{
					LCD_Fill(0,139,59,199,BLACK);
				}
				LCD_Fill(0,139,59,199,0xC7FF);
				return 3;
			}
					else if(tp_dev.x[0]>59&&tp_dev.x[0]<119&&tp_dev.y[0]>139&&tp_dev.y[0]<199)
			{
				while(PEN==0)
				{
					LCD_Fill(59,139,119,199,BLACK);
				}
				LCD_Fill(59,139,119,199,0xC7FF);
				return 4;
			}
						else if(tp_dev.x[0]>119&&tp_dev.x[0]<179&&tp_dev.y[0]>139&&tp_dev.y[0]<199)
			{
				while(PEN==0)
				{
					LCD_Fill(119,139,179,199,BLACK);
				}
				LCD_Fill(119,139,179,199,0xC7FF);
				return 5;
			}
						else if(tp_dev.x[0]>179&&tp_dev.x[0]<239&&tp_dev.y[0]>139&&tp_dev.y[0]<199)
			{
				while(PEN==0)
				{
					LCD_Fill(179,139,239,199,BLACK);
				}
				LCD_Fill(179,139,239,199,0xC7FF);
				return 6;
			}
		
						else if(tp_dev.x[0]>0&&tp_dev.x[0]<59&&tp_dev.y[0]>199&&tp_dev.y[0]<259)
			{
				while(PEN==0)
				{
					LCD_Fill(0,199,59,259,BLACK);
				}
				LCD_Fill(0,199,59,259,0xC7FF);
				return 7;
			}
		
						else if(tp_dev.x[0]>59&&tp_dev.x[0]<119&&tp_dev.y[0]>199&&tp_dev.y[0]<259)
			{
				while(PEN==0)
				{
					LCD_Fill(59,199,119,259,BLACK);
				}
				LCD_Fill(59,199,119,259,0xC7FF);
				return 8;
			}
		
						else if(tp_dev.x[0]>119&&tp_dev.x[0]<179&&tp_dev.y[0]>199&&tp_dev.y[0]<259)
			{
				while(PEN==0)
				{
					LCD_Fill(119,199,179,259,BLACK);
				}
				LCD_Fill(119,199,179,259,0xC7FF);
				return 9;
			}
		
						else if(tp_dev.x[0]>179&&tp_dev.x[0]<239&&tp_dev.y[0]>199&&tp_dev.y[0]<259)
			{
				while(PEN==0)
				{
					LCD_Fill(179,199,239,259,BLACK);
				}
				LCD_Fill(179,199,239,259,0xC7FF);
				return 10;
			}
		else if(tp_dev.x[0]>0&&tp_dev.x[0]<59&&tp_dev.y[0]>259&&tp_dev.y[0]<319)
			{
				while(PEN==0)
				{
					LCD_Fill(0,259,59,319,BLACK);
				}
				LCD_Fill(0,259,59,319,0xC7FF);
				return 11;
			}
		else if(tp_dev.x[0]>59&&tp_dev.x[0]<119&&tp_dev.y[0]>259&&tp_dev.y[0]<319)
			{
				while(PEN==0)
				{
					LCD_Fill(59,259,119,319,BLACK);
				}
				LCD_Fill(59,259,119,319,0xC7FF);
				return 12;
			}
		else if(tp_dev.x[0]>119&&tp_dev.x[0]<179&&tp_dev.y[0]>259&&tp_dev.y[0]<319)
			{
				while(PEN==0)
				{
					LCD_Fill(119,259,179,319,BLACK);
				}
				LCD_Fill(119,259,179,319,0xC7FF);
				return 13;
			}
			else if(tp_dev.x[0]>179&&tp_dev.x[0]<239&&tp_dev.y[0]>259&&tp_dev.y[0]<319)
			{
				while(PEN==0)
				{
					LCD_Fill(179,259,239,319,BLACK);
				}
				LCD_Fill(179,259,239,319,0xC7FF);
				return 14;
			}
			else return 0;
		}else delay_ms(10);	
		return 0;
}


void TOUCH_DISP_GradeInput_1(void)  //实验编号键值处理
{
	u8 key;
	u8 num=0;
	u8 ii=0,i=0;
	u8 queding_Flag=0;

	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;

	LCD_Clear(0xC7FF);//清屏
	GUI_GradeInput_1();
	while(1)
	{
		key=TOUCH_GradeInput_1();	 //获取触摸键值y
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_GradeInput_1();  				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_DISP_MENU(); 	       //退出程序
								break;

			case 2:		
								queding_Flag++;
								if(queding_Flag==1) 
									 num=0;
								if(queding_Flag==2) 
								{		
									Stu[Stu_number].dailyscore1 = input[0]*10+input[1];
									Stu[Stu_number].testscore2 = input[2]*10+input[3];
									Stu[Stu_number].score = Stu[Stu_number].dailyscore1*Daily_Procent/100 +Stu[Stu_number].testscore2*Test_Procent/100;	
									for(i=0;i<4;i++)
										Stu[Stu_number].studentID[i] = cardID[i];
									LCD_Clear(0xC7FF);//清屏
									TOUCH_DISP_GUI_PersonInformation();
								}
								break;

			case 3:		if(ii>=4)	break;    //输入数值不超过4位数  //输入0
						else
						{
							num++;
							input[ii]=0;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'0',16,0);		 //0 
							break;
						}

			case 4:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=1;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'1',16,0);		 //1
							break;
						}

			case 5:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=2;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'2',16,0);		 //2
							break;
						}

			case 6:		num=0;
						ii=0;
						input[0]=0;
						input[1]=0;
						input[2]=0;
						input[3]=0;
						input[4]=0;
						length=0;	
						queding_Flag=0;
						LCD_Fill(150,10,200,30,0xC7FF);			   		 //重输
						LCD_Fill(150,56,200,86,0xC7FF);			   		 //重输
						break;

			case 7:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=3;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'3',16,0);		 //3
							break;
						}

			case 8:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=4;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'4',16,0);		 //4
							break;
						}

			case 9:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=5;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'5',16,0);		 //5
							break;
						}

			case 10:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=6;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'6',16,0);		 //6
							break;
						}

			case 11:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=7;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'7',16,0);		 //7
							break;
						}

			case 12:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=8;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'8',16,0);		 //8
							break;
						}

			case 13:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=9;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'9',16,0);		 //9
							break;
						}

			case 14:    break;//小数点无效

			default:	break;
		}


//		delay_ms(10);//每过10ms查询一次触摸屏

	}
}


/***********************************************************/
//***************成绩修改**********************************/
/**********************************************************/

void GUI_Grade_Change(void)
{
	u8 i=0;
	LCD_Clear(0xC7FF);//清屏
	Show_Str(85,120,240,16,"请刷卡",16,1);
	Show_Str(35,150,240,16,"触摸任一点返回主菜单",16,1);
	while(1)
	{
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>0&&tp_dev.y[0]<320)
			{
				while(PEN==0)
				{
					TOUCH_DISP_MENU();
				}
			}
					
		}else delay_ms(10);	
		if(flag_com==0)
		{
			Read_cardID();
		}
		else
		{
			for(i=0;i<30;i++)
			{
				if((cardID[0]==Stu[i].studentID[0])&&(cardID[1]==Stu[i].studentID[1])&&(cardID[2]==Stu[i].studentID[2])&&(cardID[3]==Stu[i].studentID[3]))
				{
						Change_number=i;
						Change_flag=1;
						TOUCH_Grade_Change();

				}
			}
		  LCD_Clear(0xC7FF);//清屏
			Show_Str(50,150,240,16,"未找到该信息！",16,1);	
			flag_com=0;
			delay_ms(1000);
			TOUCH_DISP_MENU();

			
		}
	}
	
}




void TOUCH_Grade_Change(void)  //实验编号键值处理
{
	u8 key;
	u8 num=0;
	u8 ii=0,i=0;
	u8 queding_Flag=0;

	length=0;
	input[0]=0;input[1]=0;input[2]=0;input[3]=0;input[4]=0;

	LCD_Clear(0xC7FF);//清屏
	GUI_GradeInput_1();
	while(1)
	{
		key=TOUCH_GradeInput_1();	 //获取触摸键值y
		
		switch(key)			     				 //相应键值的处理
		{
			case 0:		GUI_GradeInput_1();  				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_DISP_MENU(); 	       //退出程序
								break;

			case 2:		
								queding_Flag++;
								if(queding_Flag==1) 
									 num=0;
								if(queding_Flag==2) 
								{		
									Stu[Change_number].dailyscore1 = input[0]*10+input[1];
									Stu[Change_number].testscore2 = input[2]*10+input[3];
									Stu[Change_number].score = Stu[Change_number].dailyscore1/5 +Stu[Change_number].testscore2*4/5;	
									for(i=0;i<4;i++)
										Stu[Change_number].studentID[i] = cardID[i];
									LCD_Clear(0xC7FF);//清屏
									TOUCH_DISP_GUI_PersonInformation();
								}
								break;

			case 3:		if(ii>=4)	break;    //输入数值不超过4位数  //输入0
						else
						{
							num++;
							input[ii]=0;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'0',16,0);		 //0 
							break;
						}

			case 4:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=1;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'1',16,0);		 //1
							break;
						}

			case 5:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=2;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'2',16,0);		 //2
							break;
						}

			case 6:		num=0;
						ii=0;
						input[0]=0;
						input[1]=0;
						input[2]=0;
						input[3]=0;
						input[4]=0;
						length=0;	
						queding_Flag=0;
						LCD_Fill(150,10,200,30,0xC7FF);			   		 //重输
						LCD_Fill(150,56,200,86,0xC7FF);			   		 //重输
						break;

			case 7:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=3;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'3',16,0);		 //3
							break;
						}

			case 8:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=4;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'4',16,0);		 //4
							break;
						}

			case 9:		if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=5;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'5',16,0);		 //5
							break;
						}

			case 10:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=6;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'6',16,0);		 //6
							break;
						}

			case 11:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=7;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'7',16,0);		 //7
							break;
						}

			case 12:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=8;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'8',16,0);		 //8
							break;
						}

			case 13:	if(ii>=4)	break;//输入数值不超过4位数
						else
						{
							num++;
							input[ii]=9;
							ii++;
							LCD_ShowChar(150+8*num,10+queding_Flag*46,'9',16,0);		 //9
							break;
						}

			case 14:    break;//小数点无效

			default:	break;
		}


	}
}


//****************************************************************
//****************管理系统****************************************
//****************************************************************

void GUI_Management(void)         //主GUI
{
	POINT_COLOR=BLACK; 
	LCD_DrawLine(0, 39, 239, 39);										//横
	LCD_DrawLine(0, 39+70+20, 239, 39+70+20);				//横
	LCD_DrawLine(0, 39+70+70+40, 239, 39+70+70+40); //横
	LCD_DrawLine(119, 39, 119, 319);								//竖
	
	POINT_COLOR=BLUE; 
	Show_Str(100,10,240,16,"菜单栏",16,1);
	Show_Str(39+5-15,75,240,16,"实验管理",16,0);
	Show_Str(39+120+5-15,75,240,16,"成绩管理",16,0);
	Show_Str(39+5-15,75+90,240,16,"权限管理",16,0);
	Show_Str(39+30+120-40,75+90,240,16,"指纹管理",16,0);
	
	POINT_COLOR=BLACK; 
	Show_Str(5+10,39+70+70+40+11,240,16,"今天的温度",16,1);
	Show_Str(5+10+120,39+70+70+40+11,240,16,"日期和时间",16,1);	
}



void Main_Management(void)				//主循环程序
{
	u8 key;
	u8 t=0;	
	short temp; 
	card_status=0;//状态清零

	LCD_Clear(0xC7FF);//清屏

	GUI_Management();         //菜单栏显示触摸界面
	
	//显示时间
	POINT_COLOR=BLUE;//设置字体为蓝色
	LCD_ShowString(60+65+10,130+70+40+20,200,16,16,"    -  -  ");	   
	LCD_ShowString(60+65+15,162+70+40+20,200,16,16,"  :  :  ");		    
	
	//显示温度
	POINT_COLOR=BLUE;//设置字体为蓝色	   
	LCD_ShowString(10,250+20,200,16,16, "      . C");	 

	while(1)
	{		
		if(t!=calendar.sec)
		{
			t=calendar.sec;
			LCD_ShowNum(60+65+10,130+70+40+20,calendar.w_year,4,16);									  
			LCD_ShowNum(100+65+10,130+70+40+20,calendar.w_month,2,16);									  
			LCD_ShowNum(124+65+10,130+70+40+20,calendar.w_date,2,16);	 
			switch(calendar.week)
			{
				case 0:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Sunday   ");
					break;
				case 1:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Monday   ");
					break;
				case 2:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Tuesday  ");
					break;
				case 3:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Wednesday");
					break;
				case 4:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Thursday ");
					break;
				case 5:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Friday   ");
					break;
				case 6:
					LCD_ShowString(60+65+20,146+70+40+20,200,16,16,"Saturday ");
					break;  			
			}
			LCD_ShowNum(60+65+15,162+70+40+20,calendar.hour,2,16);									  
			LCD_ShowNum(84+65+15,162+70+40+20,calendar.min,2,16);									  
			LCD_ShowNum(108+65+15,162+70+40+20,calendar.sec,2,16);
		}		
		//更新温度
		temp=DS18B20_Get_Temp();
		if(temp<0)
		{
			temp=-temp;
			LCD_ShowChar(140-110,250+20,'-',16,0);//显示负号	
		}						 
		LCD_ShowNum(148-110,250+20,temp/10,2,16);//显示温度值	  
		LCD_ShowNum(172-110,250+20,temp%10,1,16);//显示温度值
		
		
		
		key=TOUCH_MENU(); //获取触摸键值
		switch(key)			       //相应键值的处理
		{
			case 0:		GUI_Management();   				 //没有触摸按键按下，一直显示操作界面
								break;

			case 1:		TOUCH_DISP_Experiment(); 	  //实验管理
								break;

			case 2:		TOUCH_DISP_MENU();		//成绩管理菜单
								break;

			case 3:		Root_Add();          //权限管理
								break;

			case 4:		LCD_Clear(0xC7FF);
								FR_Management(); 		 		//指纹管理
								break;


			default:	break;
		}
		
		delay_ms(10);//每过10ms查询一次触摸屏

	 }
}


void Root_Add(void)
{
	u8 i;
	LCD_Clear(0xC7FF);//清屏
	Show_Str(85,120,240,16,"请刷卡",16,1);
	Show_Str(35,150,240,16,"触摸任一点返回主菜单",16,1);
	while(1)
	{ 
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
			if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>0&&tp_dev.y[0]<320)
			{
				while(PEN==0)
				{
					Main_Management();
				}
			}
					
		}else delay_ms(10);	
		if(flag_com==0)
		{
			Read_cardID();
		}
		else
		{
			LCD_Clear(0xC7FF);//清屏
			for(i=0;i<4;i++)
				Root_ID[Root_number][i] = cardID[i];
			Root_number++;
			Show_Str(35,150,240,16,"卡号已经添加到白名单!",16,1);
			flag_com=0;
			delay_ms(1000);
			delay_ms(1000);
			Main_Management();
	
		}
	}
}


void GUI_Grade_Chart(void)
{
		u8 i;
		u8 Page_flag=0;
	  LCD_Clear(0xC7FF);//清屏
		POINT_COLOR=BLACK; 
		Show_Str(12,5,240,16,"编号",16,1);
	  Show_Str(100,5,240,16,"卡号",16,1);
		Show_Str(195,5,240,16,"成绩",16,1);
	
		Show_Str(5,302,240,16,"上一页",16,1);
	  Show_Str(90,302,240,16,"返回菜单",16,1);
		Show_Str(190,302,240,16,"下一页",16,1);

		LCD_DrawLine(0, 24, 239, 24);			//横  
    LCD_DrawLine(0, 49, 239, 49);			//横 
    LCD_DrawLine(0, 74, 239, 74);			//横 
    LCD_DrawLine(0, 99, 239, 99);			//横 
    LCD_DrawLine(0, 124, 239, 124);			//横 
    LCD_DrawLine(0, 149, 239, 149);			//横 
    LCD_DrawLine(0, 174, 239, 174);			//横 
    LCD_DrawLine(0, 199, 239, 199);			//横 
    LCD_DrawLine(0, 224, 239, 224);			//横 	
	  LCD_DrawLine(0, 249, 239, 249);			//横 
    LCD_DrawLine(0, 274, 239, 274);			//横 
    LCD_DrawLine(0, 299, 239, 299);			//横 
		LCD_DrawLine(59, 0, 59, 319);			//竖
	  LCD_DrawLine(179, 0, 179, 319);			//竖
		while(1)
		{ 
			tp_dev.scan(0); 		 
			if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
			{	
				if(tp_dev.x[0]>0&&tp_dev.x[0]<240&&tp_dev.y[0]>0&&tp_dev.y[0]<320)
				{
					while(PEN==0)
					{
						Main_Management();
					}
				}
				
			}else delay_ms(10);	
			for(i=0;i<11;i++)
			{
				LCD_ShowNum(20,29+i*25,i+1,2,16);
				LCD_ShowNum(70,29+i*25,Stu[i].studentID[0],3,16);
				LCD_ShowNum(94,29+i*25,Stu[i].studentID[1],3,16);
				LCD_ShowNum(118,29+i*25,Stu[i].studentID[2],3,16);
				LCD_ShowNum(142,29+i*25,Stu[i].studentID[3],3,16);
				LCD_ShowNum(205,29+i*25,Stu[i].score,2,16);

			
			}
		}

}


