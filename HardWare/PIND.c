#include "stm32f10x.h"                  // Device header



void PINA7_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʼ��ʱ��,����ʱ��  ѡ��A������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_IPU;		//GPIOģʽ�������ģʽ�¸ߵ͵�ƽ����������(��©���ʱֻ���ɵ͵�ƽ����)
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_7;			//GPIO�˿�(ѡ��A0�˿�)�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO�ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure);


}