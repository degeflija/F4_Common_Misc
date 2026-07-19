/*
 * i2c.h
 *
 *  Created on: 03.12.2020
 *      Author: Maximilian Betz
 */
/**
  * ############################################################################
  * @file     I2C.h
  * @brief    New Vario
  * @author   Max Baetz / Horst Rupp
  * @brief    This routine TODO
  * ############################################################################
  */
//
// Includes
//

#include "Generic_Common.h"
#include "main.h"
#include "my_assert.h"
#include "FreeRTOS_wrapper.h"
#ifndef __I2C_H
#define __I2C_H


#include "stm32f4xx_hal.h"
#include <stdbool.h>

extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

//Note: Definition not used in stm32f4xx_hal_msp.c as this file is part of the generation process.
#define I2C1_SCL_GPIOX GPIOB
#define I2C1_SCL_GPIOPIN GPIO_PIN_6

#define I2C1_SDA_GPIOX GPIOB
#define I2C1_SDA_GPIOPIN GPIO_PIN_7

#define I2C2_SCL_GPIOX GPIOB
#define I2C2_SCL_GPIOPIN GPIO_PIN_6

#define I2C2_SDA_GPIOX GPIOB
#define I2C2_SDA_GPIOPIN GPIO_PIN_7

typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR    = 0x01U
} I2C_StatusTypeDef;
  void  			I2C1_Init ( void );

I2C_StatusTypeDef I2C_Init(I2C_HandleTypeDef *hi2c);
I2C_StatusTypeDef I2C_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);
I2C_StatusTypeDef I2C_ReadRegister(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
I2C_StatusTypeDef I2C_WriteRegister(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress, uint16_t MemAddSize, uint8_t *pData, uint16_t Size);
I2C_StatusTypeDef I2C_Write(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size);



#endif /* __I2C_H */
//
// =============================================================================
//  The End
// =============================================================================