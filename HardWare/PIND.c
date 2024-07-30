#include "stm32f10x.h"                  // Device header



void PINA7_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //始能时钟,开启时钟  选用A口外设
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_IPU;		//GPIO模式推挽输出模式下高低电平都可以驱动(开漏输出时只能由低电平驱动)
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_7;			//GPIO端口(选用A0端口)端口初始化
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO速度
	GPIO_Init(GPIOA,&GPIO_InitStructure);


}