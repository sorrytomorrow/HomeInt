/**
	************************************************************
	************************************************************
	************************************************************
	*	�ļ����� 	main.c
	*
	*	���ߣ� 		�ż���
	*
	*	���ڣ� 		2017-05-08
	*
	*	�汾�� 		V1.0
	*
	*	˵���� 		����onenet���ϴ����ݺ��������
	*
	*	�޸ļ�¼��	
	************************************************************
	************************************************************
	************************************************************
**/

//��Ƭ��ͷ�ļ�
#include "stm32f10x.h"



//�����豸
#include "esp8266.h"

//Ӳ������
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

//C��
#include <string.h>

#define ESP8266_ONENET_INFO		"AT+CIPSTART=\"TCP\",\"183.230.40.96\",1883\r\n"




/*
************************************************************
*	�������ƣ�	Hardware_Init
*
*	�������ܣ�	Ӳ����ʼ��
*
*	��ڲ�����	��
*
*	���ز�����	��
*
*	˵����		��ʼ����Ƭ�������Լ�����豸
************************************************************
*/
void Hardware_Init(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�жϿ�������������

	Delay_Init();									//systick��ʼ��
	
	Usart1_Init(115200);							//����1����ӡ��Ϣ��
	
	Usart2_Init(115200);							//����2������ESP8266��
	PWM_Init();									   //�����ʼ��
	PWM3_Init();
	LED_Init();										//�ƹ��ʼ��
	Stepper_GPIOInit();								//���������ʼ��
	Serial_Init();
	PINA7_Init();
	AD_Init();
//	OLED_Init();		 						
}


//���Ŷ������������
void DDrive(u8 State_W)
{
	
	if(State_W)
	{
		
		TIM_SetCompare2(TIM2,50);
		
	}
	else{TIM_SetCompare2(TIM2,150);}

}


//�����������������
void DDrive_win(u8 State_W)
{
	
	if(State_W)
	{
		
		TIM_SetCompare1(TIM3,50);
		
	}
	else{TIM_SetCompare1(TIM3,150);}

}


//�������
u8 D1_State_W=0,Light_State=0;
u8 D2_State_W=0,Stepper_State,Stepper_num,Mode,Stepper_num1=1,Stepper_num2=1;
u8 temp,humi;
int light_v,gas;
uint8_t DHT_Buffer[5];




//����ʶ����
void YY_SB()
{
	if(Serial_RxFlag == 1)
	{
		if (strcmp(Serial_RxPacket, "̨���Ѵ�") == 0){Light_State=1;}
		if (strcmp(Serial_RxPacket, "̨���ѹر�") == 0){Light_State=0;}
		if (strcmp(Serial_RxPacket, "�����Ѵ�") == 0){Stepper_State=1;Stepper_num=1;}
		if (strcmp(Serial_RxPacket, "�����ѹر�") == 0){Stepper_State=0;Stepper_num=1;}
		if (strcmp(Serial_RxPacket, "�����Ѵ�") == 0){D1_State_W=1;}
		if (strcmp(Serial_RxPacket, "�����ѹر�") == 0){D1_State_W=0;}
		if (strcmp(Serial_RxPacket, "�����Ѵ�") == 0){D2_State_W=1;}
		if (strcmp(Serial_RxPacket, "�����ѹر�") == 0){D2_State_W=0;}
		
		Serial_RxFlag=0;
	}


}




/*
************************************************************
*	�������ƣ�	main
*
*	�������ܣ�	
*
*	��ڲ�����	��
*
*	���ز�����	0
*
*	˵����		
************************************************************
*/



int main(void)
{
	
	unsigned short timeCount = 0;	//���ͼ������
	
	unsigned char *dataPtr = NULL;
	
	Hardware_Init();				//��ʼ����ΧӲ��
	
	ESP8266_Init();					//��ʼ��ESP8266


	UsartPrintf(USART_DEBUG, "Connect MQTTs Server...\r\n");
	while(ESP8266_SendCmd(ESP8266_ONENET_INFO, "CONNECT"))
		DelayXms(500);
	UsartPrintf(USART_DEBUG, "Connect MQTT Server Success\r\n");
//	
	while(OneNet_DevLink())			//����OneNET
		DelayXms(500);

	OneNET_Subscribe();//������Ϣ
	
	//OLED��ʾ
//	OLED_ShowString(1,1,"GAS:  %");
//	OLED_ShowString(2,1,"LightSen:  %");
//	OLED_ShowString(3,1,"Temp:  ");
//	OLED_ShowString(4,1,"Humi:  %");
	
	
	while(1)
	{

		
		if(++timeCount >= 100)									//���ͼ��5s    500
		{
			if(DHT_Get_Temp_Humi_Data(DHT_Buffer))
			{
				temp = DHT_Buffer[2];
				humi = DHT_Buffer[0];
				UsartPrintf(USART_DEBUG, "temp:%d,humi:%d",DHT_Buffer[2],DHT_Buffer[0]);
			}								//��ʪ�ȴ�������ʼ��
			
			
			
			//��������AD
			gas = (int)((float)AD_GetValue(ADC_Channel_9)/4095*100);
			//����ֵ
			light_v = (int)((float)AD_GetValue(ADC_Channel_8)/4095*100);
			light_v = 100-light_v;
			
			
			
			OneNet_SendData();									//��������
			timeCount = 0;
			ESP8266_Clear();
			
			
			//OLED��ʾ����
//			OLED_ShowNum(1,5,gas,2);
//			OLED_ShowNum(2,10,light_v,2);
//			OLED_ShowNum(3,6,temp,2);
//			OLED_ShowNum(4,6,humi,2);
			
			
		}
		//��ESP8266���յ�������ͨ�����ڸ���stm32������ֵ����dataPtr

		//��������֮ǰ��״̬���µ�
		
		dataPtr = ESP8266_GetIPD(0);
		if(dataPtr != NULL)
			OneNet_RevPro(dataPtr);   //����json����
		
		DDrive(D1_State_W);           //�������
		DDrive_win(D2_State_W);
		
		if(Light_State){LED0_On();}  //�������
		else{LED0_Off();}
		
		if(Mode==0)			//�ֶ�������ģʽ
		{
			if(Stepper_State==1 && Stepper_num==1){Stepper_RotateByLoop(Forward, 2, 3);Stepper_num=0;}	//��������	
			if(Stepper_State==0 && Stepper_num==1){Stepper_RotateByLoop(Reversal, 2, 3);Stepper_num=0;}
		
			
			
			
		}
		if(Mode==1)			//�Զ�ģʽ���ܹ���
		{
			if(Stepper_State==0 && light_v>=60 &&Stepper_num1==1){Stepper_RotateByLoop(Forward, 2, 3);Stepper_State=1;Stepper_num1=0;Stepper_num2=1;}	//��������	
			if(Stepper_State==1 && light_v<40  &&Stepper_num2==1){Stepper_RotateByLoop(Reversal, 2, 3);Stepper_State=0;Stepper_num2=0;Stepper_num1=1;}
			
			
			//��������
			if(D2_State_W==1 && GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7)==0){D2_State_W=0;}
		}
		
		
		//�ж�����Ũ����󱨾���ʼ
		if(gas>=50){LED0_On12();FMQ_On();}
		
		else{LED0_Off12();FMQ_Off();}
		
		
		YY_SB();
		DelayMs(10);
	
	}

}
