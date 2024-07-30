#include "stm32f10x.h"                  // Device header
#include "Delay2.h"
#include "Stepper.h"


uint8_t STEP;	// 用于存储电机正在走过的整步编号

/**
  * @brief  步进电机输出端GPIO初始化函数
  * @param  无
  * @retval 无
  */
void Stepper_GPIOInit(void)
{
	RCC_APB2PeriphClockCmd(Stepper_CLK, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	// 推挽输出
	GPIO_InitStruct.GPIO_Pin = Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Stepper_Output_GPIO, &GPIO_InitStruct);
	
	GPIO_ResetBits(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD);
}

/**
  * @brief  电机停转函数
  * @param  无
  * @retval 无
  */
void Stepper_Stop(void)
{
	GPIO_ResetBits(Stepper_Output_GPIO, Stepper_LA | Stepper_LB | Stepper_LC | Stepper_LD);
}

/**
  * @brief  4拍单相整步驱动函数
  * @param  StepNum 	整步编号，0~3对应A~D
  * @param	Delay_Time_xms 		每步旋转后延时时间x ms，用于控制步进电机速度（一般需大于等于2）
  * @retval 无
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
	Delay_ms(Delay_Time_xms);	// 延时，控制电机速度
	Stepper_Stop();				// 断电，防止电机过热
}

/**
  * @brief  步进电机按步旋转
  * @param  direction		电机旋转方向，可以是Forward（正传）或者Reversal（反转）
  * @param	step			电机转过的步数
  * @param	Delay_Time_xms	每步旋转后延时时间x ms，用于控制步进电机速度（一般需大于等于2）
  * @retval 无
  */
void Stepper_RotateByStep(RotDirection direction, uint32_t step, uint16_t Delay_Time_xms)
{
	for (uint32_t i = 0; i < step; i ++)
	{
		if (direction == Forward)	// 电机正传
		{
			STEP ++;
			if (STEP > 3)
			{
				STEP = 0;
			}
		}
		else if (direction == Reversal)	// 电机反转
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
  * @brief  步进电机按整数圈旋转
  * @param  direction		电机旋转方向，可以是Forward（正传）或者Reversal（反转）
  * @param  Loop			电机旋转的圈数
  * @param  Delay_Time_xms	每步旋转后延时时间x ms，用于控制步进电机速度（一般需大于等于2）
  * @retval 
  */
void Stepper_RotateByLoop(RotDirection direction, uint32_t Loop, uint16_t Delay_Time_xms)
{
	Stepper_RotateByStep(direction, Loop * 2048, Delay_Time_xms);
}

