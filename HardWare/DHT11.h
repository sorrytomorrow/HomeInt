#ifndef __DHT11_H
#define __DHT11_H

#include "stm32f10x.h"                  // Device header

#include "stdio.h"
#include "delay1.h"

#define DHT_GPIO_PORT		GPIOA
#define DHT_GPIO_PIN		GPIO_Pin_4
#define DHT_RCC_PORT		RCC_APB2Periph_GPIOA

uint8_t DHT_Get_Temp_Humi_Data(uint8_t buffer[]);

#endif
