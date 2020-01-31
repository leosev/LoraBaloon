/**
  ******************************************************************************
  * @file  : app_x-cube-gnss1.h
  * @brief : Header file
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
#ifndef APP_X_CUBE_GNSS1_H
#define APP_X_CUBE_GNSS1_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gnss_parser.h"

/* Exported Functions --------------------------------------------------------*/
void MX_GNSS_Init(void);
// void MX_GNSS_Process(void);
GNSSParser_Status_t MX_GNSS_Process(GPGGA_Info_t *GPGGA_Data);
#ifdef __cplusplus
}
#endif
#endif /* APP_X_CUBE_GNSS1_H */
