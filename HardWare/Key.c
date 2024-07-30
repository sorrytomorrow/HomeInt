#include "stm32f10x.h"                  // Device header
#include "Delay.h"

/**
  * @brief Key的初始化操作
  * @param 无
  * @retval 无
  */
void Key_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);   //始能时钟,开启时钟  选用A口外设
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_IPU;		//GPIO模式上拉输入模式
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_0|GPIO_Pin_11;			//GPIO端口(选用A0端口)端口初始化
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO速度
	GPIO_Init(GPIOB,&GPIO_InitStructure); 
}

/**
  * @brief 检测按键的值
  * @param 无
  * @retval 返回检测按键的值
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