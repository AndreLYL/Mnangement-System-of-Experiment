#include "usart2.h"

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	USART2->DR = (u8) ch;      
	return ch;
}
#endif 

#if EN_USART2_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART2_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART2_RX_STA=0;       //����״̬���	  
  
void USART2_IRQHandler(void)
{
	u8 res;	
#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	OSIntEnter();    
#endif
	if(USART2->SR&(1<<5))//���յ�����
	{	 
		res=USART2->DR; 
		if((USART2_RX_STA&0x8000)==0)//����δ���
		{
			if(USART2_RX_STA&0x4000)//���յ���0x0d
			{
				if(res!=0x0a)USART2_RX_STA=0;//���մ���,���¿�ʼ
				else USART2_RX_STA|=0x8000;	//��������� 
			}else //��û�յ�0X0D
			{	
				if(res==0x0d)USART2_RX_STA|=0x4000;
				else
				{
					USART2_RX_BUF[USART2_RX_STA&0X3FFF]=res;
					USART2_RX_STA++;
					if(USART2_RX_STA>(USART_REC_LEN-1))USART2_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
				}		 
			}
		}  		 									     
	}
#ifdef OS_CRITICAL_METHOD 	//���OS_CRITICAL_METHOD������,˵��ʹ��ucosII��.
	OSIntExit();  											 
#endif
} 
#endif										 


//��ʼ��IO ����2
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������
//CHECK OK
//091209
void uart2_init(u32 pclk1,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk1*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB1ENR|=1<<17;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRL&=0XFFFF00FF;//IO״̬����
	GPIOA->CRL|=0X00008B00;//IO״̬����
		  
	RCC->APB1RSTR|=1<<17;   //��λ����1
	RCC->APB1RSTR&=~(1<<17);//ֹͣ��λ	   	   
	//����������
 	USART2->BRR=mantissa; // ����������	 
	USART2->CR1|=0X200C;  //1λֹͣ,��У��λ.
#if EN_USART2_RX		  //���ʹ���˽���
	//ʹ�ܽ����ж�
	USART2->CR1|=1<<8;    //PE�ж�ʹ��
	USART2->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
	MY_NVIC_Init(3,3,USART2_IRQn,2);//��2��������ȼ� 
#endif
}



long StuID;
char Stuname;
float Score,Tscore,Score;


struct student
{
	long studentID;				//ѧ��ѧ��
	char studentname[10];		//ѧ������
	float dailyscore1;			//Ԥϰ�ɼ�
	float testscore2;			//ʵ��ɼ�
	float score;				//�ܳɼ�
};

struct student stu[30];			//����һ���ṹ������
u8 number=0;

void TxdByte(unsigned int ch)//���ڷ�����Ϣ,ͨ����ѯ��ʽ����һ���ַ�
{
	
	USART2->SR&=0XFFFFFFBF;//�����һ�·����жϱ�־λ��������һ���ֽڶ�ʧ�����⡣							////
	USART2->DR=ch;																							////
	while((USART2->SR&0X40)==0);//�ȴ����ͽ���																////	
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

u8 Grade_Output(void)							//ͨ���������ڵ�printf�����佫���ݴ��ص���
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


