/**
	************************************************************
	************************************************************
	************************************************************
	*	文件名： 	main.c
	*
	*	作者： 		张继瑞
	*
	*	日期： 		2017-05-08
	*
	*	版本： 		V1.0
	*
	*	说明： 		接入onenet，上传数据和命令控制
	*
	*	修改记录：	
	************************************************************
	************************************************************
	************************************************************
**/

//单片机头文件
#include "stm32f10x.h"



//网络设备
#include "esp8266.h"

//硬件驱动
#include "usart.h"
#include "Delay.h"
#include "onenet.h"
#include "PWM_L.h"
#include "PWM_3.h"
#include "dht11.h"
#include "AD.h"
#include "LED.h"
#include "Stepper.h"
#include "PIND.h"
#include "Serial.h"
#include "OLED.h"

//C库
#include <string.h>

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.96\",1883\r\n"




/*
************************************************************
*	函数名称：	Hardware_Init
*
*	函数功能：	硬件初始化
*
*	入口参数：	无
*
*	返回参数：	无
*
*	说明：		初始化单片机功能以及外接设备
************************************************************
*/
void Hardware_Init(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组设置

	Delay_Init();									//systick初始化
	
	Usart1_Init(115200);							//串口1，打印信息用
	
	Usart2_Init(115200);							//串口2，驱动ESP8266用
	PWM_Init();									   //舵机初始化
	PWM3_Init();
	LED_Init();										//灯光初始化
	Stepper_GPIOInit();								//步进电机初始化
	Serial_Init();
	PINA7_Init();
	AD_Init();
//	OLED_Init();		 						
}


//大门舵机函数的驱动
void DDrive(u8 State_W)
{
	
	if(State_W)
	{
		
		TIM_SetCompare2(TIM2,50);
		
	}
	else{TIM_SetCompare2(TIM2,150);}

}


//窗户舵机函数的驱动
void DDrive_win(u8 State_W)
{
	
	if(State_W)
	{
		
		TIM_SetCompare1(TIM3,50);
		
	}
	else{TIM_SetCompare1(TIM3,150);}

}


//定义变量
u8 D1_State_W=0,Light_State=0;
u8 D2_State_W=0,Stepper_State,Stepper_num,Mode,Stepper_num1=1,Stepper_num2=1;
u8 temp,humi;
int light_v,gas;
uint8_t DHT_Buffer[5];




//语音识别函数
void YY_SB()
{
	if(Serial_RxFlag == 1)
	{
		if (strcmp(Serial_RxPacket, "台灯已打开") == 0){Light_State=1;}
		if (strcmp(Serial_RxPacket, "台灯已关闭") == 0){Light_State=0;}
		if (strcmp(Serial_RxPacket, "窗帘已打开") == 0){Stepper_State=1;Stepper_num=1;}
		if (strcmp(Serial_RxPacket, "窗帘已关闭") == 0){Stepper_State=0;Stepper_num=1;}
		if (strcmp(Serial_RxPacket, "大门已打开") == 0){D1_State_W=1;}
		if (strcmp(Serial_RxPacket, "大门已关闭") == 0){D1_State_W=0;}
		if (strcmp(Serial_RxPacket, "窗户已打开") == 0){D2_State_W=1;}
		if (strcmp(Serial_RxPacket, "窗户已关闭") == 0){D2_State_W=0;}
		
		Serial_RxFlag=0;
	}


}




/*
************************************************************
*	函数名称：	main
*
*	函数功能：	
*
*	入口参数：	无
*
*	返回参数：	0
*
*	说明：		
************************************************************
*/



int main(void)
{
	
	unsigned short timeCount = 0;	//发送间隔变量
	
	unsigned char *dataPtr = NULL;
	
	Hardware_Init();				//初始化外围硬件
	
	ESP8266_Init();					//初始化ESP8266


	UsartPrintf(USART_DEBUG, "Connect MQTTs Server...\r\n");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
		DelayXms(500);
	UsartPrintf(USART_DEBUG, "Connect MQTT Server Success\r\n");
//	
	while(OneNet_DevLink())			//接入OneNET
		DelayXms(500);

	OneNET_Subscribe();//订阅消息
	
	//OLED显示
//	OLED_ShowString(1,1,"GAS:  %");
//	OLED_ShowString(2,1,"LightSen:  %");
//	OLED_ShowString(3,1,"Temp:  ");
//	OLED_ShowString(4,1,"Humi:  %");
	
	
	while(1)
	{

		
		if(++timeCount >= 100)									//发送间隔5s    500
		{
			if(DHT_Get_Temp_Humi_Data(DHT_Buffer))
			{
				temp = DHT_Buffer[2];
				humi = DHT_Buffer[0];
				UsartPrintf(USART_DEBUG, "temp:%d,humi:%d",DHT_Buffer[2],DHT_Buffer[0]);
			}								//温湿度传感器初始化
			
			
			
			//气体数据AD
			gas = (int)((float)AD_GetValue(ADC_Channel_9)/4095*100);
			//光照值
			light_v = (int)((float)AD_GetValue(ADC_Channel_8)/4095*100);
			light_v = 100-light_v;
			
			
			
			OneNet_SendData();									//发送数据
			timeCount = 0;
			ESP8266_Clear();
			
			
			//OLED显示数据
//			OLED_ShowNum(1,5,gas,2);
//			OLED_ShowNum(2,10,light_v,2);
//			OLED_ShowNum(3,6,temp,2);
//			OLED_ShowNum(4,6,humi,2);
			
			
		}
		//把ESP8266接收到的数据通过串口给到stm32，最后把值给到dataPtr

		//解析数据之前把状态更新掉
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);   //解析json数据
		
		DDrive(D1_State_W);           //驱动舵机
		DDrive_win(D2_State_W);
		
		if(Light_State){LED0_On();}  //驱动电灯
		else{LED0_Off();}
		
		if(Mode==0)			//手动和语音模式
		{
			if(Stepper_State==1 && Stepper_num==1){Stepper_RotateByLoop(Forward, 2, 3);Stepper_num=0;}	//驱动窗帘	
			if(Stepper_State==0 && Stepper_num==1){Stepper_RotateByLoop(Reversal, 2, 3);Stepper_num=0;}
		
			
			
			
		}
		if(Mode==1)			//自动模式感受光照
		{
			if(Stepper_State==0 && light_v>=60 &&Stepper_num1==1){Stepper_RotateByLoop(Forward, 2, 3);Stepper_State=1;Stepper_num1=0;Stepper_num2=1;}	//驱动窗帘	
			if(Stepper_State==1 && light_v<40  &&Stepper_num2==1){Stepper_RotateByLoop(Reversal, 2, 3);Stepper_State=0;Stepper_num2=0;Stepper_num1=1;}
			
			
			//驱动窗户
			if(D2_State_W==1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)==0){D2_State_W=0;}
		}
		
		
		//判断气体浓度随后报警开始
		if(gas>=50){LED0_On12();FMQ_On();}
		
		else{LED0_Off12();FMQ_Off();}
		
		
		YY_SB();
		DelayMs(10);
	
	}

}
