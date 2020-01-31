/**
  ******************************************************************************
  * File Name          : app_x-cube-gnss1.c
  * Description        : Implementation file
  *             
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
  
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "gnss1a1_conf.h"
#include "teseo_liv3f_conf.h"

#include "gnss1a1_gnss.h"
#include "gnss_data.h"
#include "app_x-cube-gnss1.h"
#include "stm32l0xx_nucleo.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private defines -----------------------------------------------------------*/

/* Global variables ----------------------------------------------------------*/

/* Instance of GNSS Handler */

/* Private variables ---------------------------------------------------------*/
static GNSSParser_Data_t GNSSParser_Data;


void MX_GNSS_Init(void)
{
  /* USER CODE BEGIN GNSS_Init_PreTreatment */
  
  /* USER CODE END GNSS_Init_PreTreatment */
 

  /* Initialize the peripherals and the teseo device */  


  /* USER CODE BEGIN GNSS_Init_PostTreatment */
    GNSS1A1_GNSS_Init(GNSS1A1_TESEO_LIV3F);
  
	GNSS_PARSER_Init(&GNSSParser_Data);
  /* USER CODE END GNSS_Init_PostTreatment */
}

 GNSSParser_Status_t MX_GNSS_Process(GPGGA_Info_t *GPGGA_Data){
  const GNSS1A1_GNSS_Msg_t *gnssMsg;
  for(;;)
  {
#if (USE_I2C == 1)
    GNSS1A1_GNSS_BackgroundProcess(GNSS1A1_TESEO_LIV3F);
#endif
    gnssMsg = GNSS1A1_GNSS_GetMessage(GNSS1A1_TESEO_LIV3F);
    if(gnssMsg == NULL)
      continue;

    if(GNSS_PARSER_CheckSanity((uint8_t *)gnssMsg->buf, gnssMsg->len) != GNSS_PARSER_ERROR)
        if(GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)0, (uint8_t *)gnssMsg->buf) != GNSS_PARSER_ERROR)
			if(GNSSParser_Data.gpgga_data.valid == (uint8_t)VALID){
				memcpy(GPGGA_Data, &(GNSSParser_Data.gpgga_data), sizeof (*GPGGA_Data));
				return GNSS_PARSER_OK;
			}

    GNSS1A1_GNSS_ReleaseMessage(GNSS1A1_TESEO_LIV3F, gnssMsg);
  }
  return GNSS_PARSER_ERROR;
}

#ifdef __cplusplus
}
#endif
