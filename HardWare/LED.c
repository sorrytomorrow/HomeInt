#include "stm32f10x.h"                  // Device header

/**
  * @brief 对端口(LED)进行初始化操作
  * @param 无
  * @retval 无
  */
void LED_Init()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);   //始能时钟,开启时钟  选用A口外设
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=	GPIO_Mode_Out_PP;		//GPIO模式推挽输出模式下高低电平都可以驱动(开漏输出时只能由低电平驱动)
	GPIO_InitStructure.GPIO_Pin=	GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_0;			//GPIO端口(选用A0端口)端口初始化
	GPIO_InitStructure.GPIO_Speed=	GPIO_Speed_50MHz;		//GPIO速度
	GPIO_Init(GPIOA,&GPIO_InitStructure); 
	GPIO_SetBits(GPIOA,GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_0);
}

/**
  * @brief LED端口的跳变
  * @param 无
  * @retval 无
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

