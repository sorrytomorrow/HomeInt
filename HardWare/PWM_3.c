#include "stm32f10x.h"                  // Device header


void PWM3_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //����ʱ��
	
	//��ʼ��P0���ţ�TIM2�����PWM����ֻ��ͨ��P0���д���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //ʼ��ʱ��,����ʱ��  ѡ��A������
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_AF_PP;		//GPIOģʽ�������ģʽ�¸ߵ͵�ƽ����������(��©���ʱֻ���ɵ͵�ƽ����)
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_6;			//GPIO�˿�(ѡ��A0�˿�)�˿ڳ�ʼ��
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO�ٶ�
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV2;  //ָ��ʱ�ӷ�Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   //ʱ�Ӽ���ģʽ
	TIM_TimeBaseInitStructure.TIM_Period = 2000-1; 					//���ڣ��Զ��������ﵽָ��ֵ����һ�μ�������������  ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;        		 //PSCԤ��Ƶ��(����)��������ָ��ֵ���㣬ʹ�Զ����ؼ�һ
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;    //�߼�����������Ҫ�õ�
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
//	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);   //Ԥת�ؼĴ������������Ĵ�������ʱ�ᴥ������ʱ�䴥�����ж�ͬʱ��������һ�ϵ�����̴����ж�
//	//�ж�����
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //�����жϵ�NVIC
//	
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;					
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      //��ռ���ȼ�
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			  //��Ӧ���ȼ�	
//	NVIC_Init(&NVIC_InitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCStructInit(&TIM_OCInitStruct);           //���ṹ�帳��ʼֵ�������
	TIM_OCInitStruct.TIM_OCMode= TIM_OCMode_PWM1;                //����Ƚϵ�ģʽ(����pwm1ģʽ cnt<ccrʱ����ߵ�ƽ��cnt>=ccrʱ����͵�ƽ)
	TIM_OCInitStruct.TIM_OCNPolarity= TIM_OCNPolarity_High;			  //����Ƚϵļ���(���ʱ����·��һ·����ֱ�������ƽ��һ·�Ƿ�ת��ƽ)
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;			  //����Ƚϵ�ʼ��
	TIM_OCInitStruct.TIM_Pulse=  0;					//����ccr(ccr��������ռ�ձ�)(��ֵ��ARR��������)    PSC��ARR����Ƶ��(����)
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	
	TIM_Cmd(TIM3,ENABLE);       //����ʱ��

}