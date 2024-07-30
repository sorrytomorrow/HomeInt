#include "stm32f10x.h"                  // Device header

void LightRest_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //始能时钟,开启时钟  选用A口外设
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_IPU;		//GPIO模式上拉输出模式
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_15;			//GPIO端口(选用A0端口)端口初始化
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO速度
	GPIO_Init(GPIOB,&GPIO_InitStructure); 

}

unsigned char LightRese_Read()
{
	return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15);
	
}