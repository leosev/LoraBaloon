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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_SimOSGetPos_Process(void);

#if (configUSE_FEATURE == 1)
static void AppCfgMsgList(int level);
static void AppGeofenceCfg(char *command);
static void AppEnFeature(char *command);
#endif /* configUSE_FEATURE */

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

void MX_GNSS_Init(void)
{
  /* USER CODE BEGIN GNSS_Init_PreTreatment */
  
  /* USER CODE END GNSS_Init_PreTreatment */
 

  /* Initialize the peripherals and the teseo device */  
  if(BSP_COM_Init(COM1) != BSP_ERROR_NONE)
  {
    Error_Handler();
  }

  PRINT_DBG("Booting...\r\n");

  /* USER CODE BEGIN GNSS_Init_PostTreatment */
  
  /* USER CODE END GNSS_Init_PostTreatment */
}

void MX_GNSS_Process(void)
{
  /* USER CODE BEGIN GNSS_Process_PreTreatment */
  
  /* USER CODE END GNSS_Process_PreTreatment */  
  MX_SimOSGetPos_Process();
	
	
  /* USER CODE BEGIN GNSS_Process_PostTreatment */
  
  /* USER CODE END GNSS_Process_PostTreatment */
}

/* TeseoConsumerTask function */
static void MX_SimOSGetPos_Process(void)
{
  GNSSParser_Status_t status, check;
  const GNSS1A1_GNSS_Msg_t *gnssMsg;

  GNSS1A1_GNSS_Init(GNSS1A1_TESEO_LIV3F);
  
  GNSS_PARSER_Init(&GNSSParser_Data);

#if (configUSE_FEATURE == 1)
  /* See CDB-ID 201 - This LOW_BITS Mask enables the following messages:
   * 0x1 $GPGNS Message
   * 0x2 $GPGGA Message
   * 0x4 $GPGSA Message
   * 0x8 $GPGST Message
   * 0x40 $GPRMC Message
   * 0x80000 $GPGSV Message
   * 0x100000 $GPGLL Message
   */
  int lowMask = 0x18004F;
  int highMask = GEOFENCE;
  PRINT_DBG("\n\rConfigure Message List\n\r");
  AppCfgMsgList(lowMask, highMask);
  HAL_Delay(500);

  PRINT_OUT("\n\rEnable Geofence\r");
  AppEnFeature("GEOFENCE,1");
  HAL_Delay(500);

  PRINT_OUT("\n\rConfigure Geofence Circle\n\r");
  AppGeofenceCfg("Geofence-Lecce");

#endif /* configUSE_FEATURE */

  for(;;)
  {
#if (USE_I2C == 1)
    GNSS1A1_GNSS_BackgroundProcess(GNSS1A1_TESEO_LIV3F);
#endif /* USE_I2C */

    gnssMsg = GNSS1A1_GNSS_GetMessage(GNSS1A1_TESEO_LIV3F);
    if(gnssMsg == NULL)
    {
      continue;
    }
    
    check = GNSS_PARSER_CheckSanity((uint8_t *)gnssMsg->buf, gnssMsg->len);

    if(check != GNSS_PARSER_ERROR)
    {

      for(int m = 0; m < NMEA_MSGS_NUM; m++)
      {

        status = GNSS_PARSER_ParseMsg(&GNSSParser_Data, (eNMEAMsg)m, (uint8_t *)gnssMsg->buf);

        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == GPGGA))
        {
          GNSS_DATA_GetValidInfo(&GNSSParser_Data);
        }
#if (configUSE_FEATURE == 1)
        if((status != GNSS_PARSER_ERROR) && ((eNMEAMsg)m == PSTMGEOFENCE))
        {
          GNSS_DATA_GetGeofenceInfo(&GNSSParser_Data);
        }
#endif /* configUSE_FEATURE */
      }
    }

    GNSS1A1_GNSS_ReleaseMessage(GNSS1A1_TESEO_LIV3F, gnssMsg);
  }
}

#if (configUSE_FEATURE == 1)
/* CfgMessageList */
static void AppCfgMsgList(int lowMask, int highMask)
{
  GNSS_DATA_CfgMessageList(lowMask, highMask);
}

static void AppEnFeature(char *command)
{
  if(strcmp(command, "GEOFENCE,1") == 0)
  {
    GNSS_DATA_EnableGeofence(1);
  }
  if(strcmp(command, "GEOFENCE,0") == 0)
  {
    GNSS_DATA_EnableGeofence(0);
  }
}

static void AppGeofenceCfg(char *command)
{ 
  if(strcmp(command, "Geofence-Lecce") == 0)
  {
    GNSS_DATA_ConfigGeofence(&Geofence_STLecce);
  }
  if(strcmp(command, "Geofence-Catania") == 0)
  {
    GNSS_DATA_ConfigGeofence(&Geofence_Catania);
  }
}
#endif /* configUSE_FEATURE */

int GNSS_PRINT(char *pBuffer)
{
  if (HAL_UART_Transmit(&hcom_uart[COM1], (uint8_t*)pBuffer, (uint16_t)strlen((char *)pBuffer), 1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}

int GNSS_PUTC(char pChar)
{
  if (HAL_UART_Transmit(&hcom_uart[COM1], (uint8_t*)&pChar, 1, 1000) != HAL_OK)
  {
    return 1;
  }
  fflush(stdout);

  return 0;
}

#ifdef __cplusplus
}
#endif
