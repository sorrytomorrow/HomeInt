#include "stm32f10x.h"                  // Device header
#include "Delay2.h"
#include "Stepper.h"


uint8_t STEP;	// ���ڴ洢��������߹����������

/**
  * @brief  ������������GPIO��ʼ������
  * @param  ��
  * @retval ��
  */
void Stepper_GPIOInit(void)
{
	RCC_APB2PeriphClockCmd(Stepper_CLK, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// �������
	GPIO_InitStruct.GPIO_Pin = Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Stepper_Output_GPIO, &GPIO_InitStruct);
	
	GPIO_ResetBits(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD);
}

/**
  * @brief  ���ͣת����
  * @param  ��
  * @retval ��
  */
void Stepper_Stop(void)
{
	GPIO_ResetBits(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD);
}

/**
  * @brief  4�ĵ���������������
  * @param  StepNum 	������ţ�0~3��ӦA~D
  * @param	Delay_Time_xms 		ÿ����ת����ʱʱ��x ms�����ڿ��Ʋ�������ٶȣ�һ������ڵ���2��
  * @retval ��
  */
void Stepper_SingleStep(uint8_t StepNum, uint16_t Delay_Time_xms)
{
	switch(StepNum)
	{
		case 0:		// A
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LA, Bit_SET);
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LB | Stepper_LC | Stepper_LD, Bit_RESET);
		break;
		case 1:		// B
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LB, Bit_SET);	
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LA | Stepper_LC | Stepper_LD, Bit_RESET);
		break;			
		case 2:		// C
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LC, Bit_SET);	
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LD, Bit_RESET);
		break;
		case 3:		// D
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LD, Bit_SET);
			GPIO_WriteBit(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC, Bit_RESET);
		break;
		default: break;
	}
	Delay_ms(Delay_Time_xms);	// ��ʱ�����Ƶ���ٶ�
	Stepper_Stop();				// �ϵ磬��ֹ�������
}

/**
  * @brief  �������������ת
  * @param  direction		�����ת���򣬿�����Forward������������Reversal����ת��
  * @param	step			���ת���Ĳ���
  * @param	Delay_Time_xms	ÿ����ת����ʱʱ��x ms�����ڿ��Ʋ�������ٶȣ�һ������ڵ���2��
  * @retval ��
  */
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms)
{
	for (uint32_t i = 0; i < step; i ++)
	{
		if (direction == Forward)	// �������
		{
			STEP ++;
			if (STEP > 3)
			{
				STEP = 0;
			}
		}
		else if (direction == Reversal)	// �����ת
		{
			if (STEP < 1)
			{
				STEP = 4;
			}
			STEP --;
		}
		Stepper_SingleStep(STEP, Delay_Time_xms);
	}
}

/**
  * @brief  �������������Ȧ��ת
  * @param  direction		�����ת���򣬿�����Forward������������Reversal����ת��
  * @param  Loop			�����ת��Ȧ��
  * @param  Delay_Time_xms	ÿ����ת����ʱʱ��x ms�����ڿ��Ʋ�������ٶȣ�һ������ڵ���2��
  * @retval 
  */
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms)
{
	Stepper_RotateByStep(direction, Loop * 2048, Delay_Time_xms);
}

