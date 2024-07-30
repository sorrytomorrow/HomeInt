#include "stm32f10x.h"                  // Device header


void PWM3_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  //开启时钟
	
	//初始化P0引脚，TIM2输出的PWM波形只能通过P0进行传输
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //始能时钟,开启时钟  选用A口外设
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_AF_PP;		//GPIO模式推挽输出模式下高低电平都可以驱动(开漏输出时只能由低电平驱动)
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_6;			//GPIO端口(选用A0端口)端口初始化
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	
	TIM_InternalClockConfig(TIM3);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV2;  //指定时钟分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   //时钟计数模式
	TIM_TimeBaseInitStructure.TIM_Period = 2000-1; 					//周期，自动重载器达到指定值就行一次计数，并且清零  ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 720-1;        		 //PSC预分频器(计数)，计数到指定值清零，使自动重载加一
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;    //高级计数器不需要用到
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	
//	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);   //预转载寄存器和重载器寄存器更新时会触发更新时间触发与中断同时触发所以一上电会立刻触发中断
//	//中断配置
//	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);    //更新中断到NVIC
//	
//	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;					
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;      //抢占优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;			  //响应优先级	
//	NVIC_Init(&NVIC_InitStructure);
	
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	TIM_OCStructInit(&TIM_OCInitStruct);           //给结构体赋初始值避免出错
	TIM_OCInitStruct.TIM_OCMode= TIM_OCMode_PWM1;                //输出比较的模式(采用pwm1模式 cnt<ccr时输出高电平，cnt>=ccr时输出低电平)
	TIM_OCInitStruct.TIM_OCNPolarity= TIM_OCNPolarity_High;			  //输出比较的极性(输出时分两路，一路可以直接输出电平，一路是翻转电平)
	TIM_OCInitStruct.TIM_OutputState= TIM_OutputState_Enable;			  //输出比较的始能
	TIM_OCInitStruct.TIM_Pulse=  0;					//设置ccr(ccr用来设置占空比)(峰值是ARR来决定的)    PSC和ARR决定频率(周期)
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);
	
	TIM_Cmd(TIM3,ENABLE);       //开启时钟

}