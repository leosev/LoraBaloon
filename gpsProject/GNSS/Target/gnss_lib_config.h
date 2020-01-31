/**
 ******************************************************************************
 * @file    gnss_lib_config.h
 * @author  SRA
 * @brief   This file is a template to be modified in the project to configure
 *          how the libGNSS is supposed to access the GNSS.
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
#ifndef GNSS_LIB_CONFIG_H
#define GNSS_LIB_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#define OS_Delay GNSS_Wrapper_Delay

/** @addtogroup MIDDLEWARES
 *  @{
 */

/** @addtogroup ST
 *  @{
 */

/** @addtogroup LIB_GNSS
 *  @{
 */
 
/** @addtogroup LibGNSS
 *  @{
 */
 
/** @defgroup GNSS_DATA_FUNCTIONS GNSS DATA FUNCTIONS
 *  @brief Prototypes of the API allowing the application to interface the driver
 *  and interact with GNSS module (sending commands, retrieving parsed NMEA info, etc.).
 *  The implementation is up to the application according to specific needs.
 *  @{
 */

/* Exported functions prototypes ---------------------------------------------*/
/**	
 * @brief  This function puts a string on the console (via UART).
 * @param  pBuffer The string that contains the data to be written on the console
 * @retval None
 */
int32_t GNSS_Wrapper_Send(uint8_t *buffer, uint16_t length);
int32_t GNSS_Wrapper_Reset(void);
void    GNSS_Wrapper_Delay(uint32_t Delay);

/**
 * @}
 */

/**
 * @}
 */
  
/**
 * @}
 */
  
/**
 * @}
 */ 

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* GNSS_LIB_CONFIG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
