/**
 ******************************************************************************
 * @file    stm32_bus_ex.h
 * @author  MCD Application Team
 * @brief   Header file for GNSS1A1 Bus Extension
 ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32_BUS_EX_H
#define STM32_BUS_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_nucleo_conf.h"
#include "stm32l0xx_nucleo_errno.h"
#include "stm32l0xx_nucleo.h"
	
/* Defines -------------------------------------------------------------------*/

#define BUS_I2C1_EV_IRQn        I2C1_EV_IRQn
#define BUS_I2C1_ER_IRQn        I2C1_ER_IRQn

int32_t BSP_I2C1_Send_IT(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
int32_t BSP_I2C1_Recv_IT(uint16_t DevAddr, uint8_t *pData, uint16_t Length);
#if (USE_HAL_I2C_REGISTER_CALLBACKS == 1)
int32_t BSP_I2C1_RegisterRxCallback(pI2C_CallbackTypeDef pCallback);
int32_t BSP_I2C1_RegisterErrorCallback(pI2C_CallbackTypeDef pCallback);
int32_t BSP_I2C1_RegisterAbortCallback(pI2C_CallbackTypeDef pCallback);
#endif

void BSP_EV_I2C1_IRQHanlder(void);
void BSP_ER_I2C1_IRQHanlder(void);

#ifdef __cplusplus
}
#endif

#endif /* STM32_BUS_EX_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
