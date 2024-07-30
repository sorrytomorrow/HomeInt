#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * @brief Key�ĳ�ʼ������
  * @param ��
  * @retval ��
  */
void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʼ��ʱ��,����ʱ��  ѡ��A������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_IPU;		//GPIOģʽ��������ģʽ
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_0|GPIO_Pin_11;			//GPIO�˿�(ѡ��A0�˿�)�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO�ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
}

/**
  * @brief ��ⰴ����ֵ
  * @param ��
  * @retval ���ؼ�ⰴ����ֵ
  */
unsigned char Key_GetNum()
{
	unsigned char KeyNum=0;
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0)
	{	
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==0);
		Delay_ms(20);
		KeyNum=1;
	}
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11)==0);
		Delay_ms(20);
		KeyNum=2;
	}
	return KeyNum;
}