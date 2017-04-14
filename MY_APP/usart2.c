#include "usart2.h"

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 

#if EN_USART2_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART2_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART2_RX_STA=0;       //接收状态标记	  
  
void USART2_IRQHandler(void)
{
	u8 res;	
#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	OSIntEnter();    
#endif
	if(USART2->SR&(1<<5))//接收到数据
	{	 
		res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART2_RX_STA&0x4000)//接收到了0x0d
			{
				if(res!=0x0a)USART2_RX_STA=0;//接收错误,重新开始
				else USART2_RX_STA|=0x8000;	//接收完成了 
			}else //还没收到0X0D
			{	
				if(res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}  		 									     
	}
#ifdef OS_CRITICAL_METHOD 	//如果OS_CRITICAL_METHOD定义了,说明使用ucosII了.
	OSIntExit();  											 
#endif
} 
#endif										 


//初始化IO 串口2
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率
//CHECK OK
//091209
void uart2_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB1ENR|=1<<17;  //使能串口时钟 
	GPIOA->CRL&=0XFFFF00FF;//IO状态设置
	GPIOA->CRL|=0X00008B00;//IO状态设置
		  
	RCC->APB1RSTR|=1<<17;   //复位串口1
	RCC->APB1RSTR&=~(1<<17);//停止复位	   	   
	//波特率设置
 	USART2->BRR=mantissa; // 波特率设置	 
	USART2->CR1|=0X200C;  //1位停止,无校验位.
#if EN_USART2_RX		  //如果使能了接收
	//使能接收中断
	USART2->CR1|=1<<8;    //PE中断使能
	USART2->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);//组2，最低优先级 
#endif
}



long StuID;
char Stuname;
float Score,Tscore,Score;


struct student
{
	long studentID;				//学生学号
	char studentname[10];		//学生姓名
	float dailyscore1;			//预习成绩
	float testscore2;			//实验成绩
	float score;				//总成绩
};

struct student stu[30];			//声明一个结构体数组
u8 number=0;

void TxdByte(unsigned int ch)//串口发送信息,通过查询方式发送一个字符
{
	
	USART2->SR&=0XFFFFFFBF;//先清除一下发送中断标志位，会解决第一个字节丢失的问题。							////
	USART2->DR=ch;																							////
	while((USART2->SR&0X40)==0);//等待发送结束																////	
}

unsigned char Txd_Data(unsigned char p[])
{
	unsigned char i,temp;
	unsigned int lenth;
	lenth=strlen((*p));
	for(i=0;i<lenth;i++)
	{
		temp=*p;
		TxdByte(temp);
		p++;
	}
	return 1;
}


void Grade_Temp(long StuID,char Stuname,float Dscore,float Tscore,float Score)
{
	stu[number].studentID=StuID;
	stu[number].studentname[0]=Stuname;
	stu[number].dailyscore1=Dscore;
	stu[number].testscore2=Tscore;
	stu[number].score=Score;
}

u8 Grade_Output(void)							//通过蓝牙串口的printf输出语句将数据传回电脑
{
	u8 flag=0,i;
	for(i=0;i<30;i++);
	{
		flag=0;
		
		printf("%d\r\n",stu[i].studentID);
		printf("%s\r\n",stu[i].studentname);
		printf("%f\r\n",stu[i].dailyscore1);
		printf("%f\r\n",stu[i].testscore2);
		printf("%f\r\n",stu[i].score);
		delay_us(10);
		flag=1;
	}
	if((i==(number+1))&&(flag==1)) return 1;
	else 		  return 0;
}


