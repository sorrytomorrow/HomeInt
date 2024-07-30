#include "stm32f10x.h"                  // Device header

void LightRest_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //ʼ��ʱ��,����ʱ��  ѡ��A������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_IPU;		//GPIOģʽ�������ģʽ
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_15;			//GPIO�˿�(ѡ��A0�˿�)�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO�ٶ�
	GPIO_Init(GPIOB,&GPIO_InitStructure); 

}

unsigned char LightRese_Read()
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
	
}