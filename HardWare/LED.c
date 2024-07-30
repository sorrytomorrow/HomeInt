#include "stm32f10x.h"                  // Device header

/**
  * @brief �Զ˿�(LED)���г�ʼ������
  * @param ��
  * @retval ��
  */
void LED_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʼ��ʱ��,����ʱ��  ѡ��A������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_Out_PP;		//GPIOģʽ�������ģʽ�¸ߵ͵�ƽ����������(��©���ʱֻ���ɵ͵�ƽ����)
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_0;			//GPIO�˿�(ѡ��A0�˿�)�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO�ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	GPIO_SetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_0);
}

/**
  * @brief LED�˿ڵ�����
  * @param ��
  * @retval ��
  */
//void LED0_Turn()
//{
//	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_0)==0)
//	{
//		GPIO_SetBits(GPIOA,GPIO_Pin_0);
//	}
//	else
//	{
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//	}
//	

//}
//void LED1_Turn()
//{
//	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1)==0)
//	{
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
//	}
//	else
//	{
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//	}

//}
//void LED2_Turn()
//{
//	if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2)==0)
//	{
//		GPIO_SetBits(GPIOA,GPIO_Pin_2);
//	}
//	else
//	{
//		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
//	}

//}

void LED0_On()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);

}

void LED0_Off()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_11);

}


void LED0_On12()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);

}

void LED0_Off12()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_12);

}


void FMQ_On()
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_0);

}

void FMQ_Off()
{
	GPIO_SetBits(GPIOA,GPIO_Pin_0);

}

