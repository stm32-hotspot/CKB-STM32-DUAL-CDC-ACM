/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_conf.h
  * @version        : v1.0_Cube
  * @brief          : Header for usbd_conf.c file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

/* USER CODE BEGIN INCLUDE */
/* Activate the IAD option */
#define USBD_COMPOSITE_USE_IAD                             1U

/* Activate the composite builder */
#define USE_USBD_COMPOSITE

/* Activate HID and MSC classes in composite builder */
#define USBD_CMPSIT_ACTIVATE_CDC                           1U

/* The definition of endpoint numbers must respect the order of classes instantiation  */
#define HID_EPIN_ADDR                         0x85U  /* EP3 for HID data IN */

#define CDC_OUT_EP                            0x01U  /* EP1 for CDC data OUT First Instance */
#define CDC_IN_EP                             0x81U  /* EP1 for CDC data IN First Instance */
#define CDC_CMD_EP                            0x82U  /* EP2 for CDC commands First Instance */

#define SECOND_CDC_OUT_EP                     0x02  /* EP2 for CDC data OUT Second Instance */
#define SECOND_CDC_IN_EP                      0x83  /* EP4 for CDC data IN Second Instance */
#define SECOND_CDC_CMD_EP                     0x84  /* EP5 for CDC commands Second Instance */

/* Common Config */
#define USBD_MAX_NUM_INTERFACES               6U
#define USBD_MAX_NUM_CONFIGURATION            1U
#define USBD_MAX_STR_DESC_SIZ                 0x100U
#define USBD_SUPPORT_USER_STRING              1U
#define USBD_SUPPORT_USER_STRING_DESC         1U
#define USBD_SELF_POWERED                     1U
#define USBD_DEBUG_LEVEL                      0U
#define USBD_CONFIG_STR_DESC_IDX                           4U
#define USBD_CONFIG_BMATTRIBUTES                           0xC0U
#define USBD_CONFIG_MAXPOWER                               0x32U

   
/* USER CODE END INCLUDE */

/** @addtogroup USBD_OTG_DRIVER
  * @{
  */

/** @defgroup USBD_CONF USBD_CONF
  * @brief Configuration file for Usb otg low level driver.
  * @{
  */

/** @defgroup USBD_CONF_Exported_Variables USBD_CONF_Exported_Variables
  * @brief Public variables.
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CONF_Exported_Defines USBD_CONF_Exported_Defines
  * @brief Defines for configuration of the Usb device.
  * @{
  */

/* MSC Class Config */
//#define MSC_MEDIA_PACKET                      512U
///*---------- -----------*/
//#define USBD_MAX_NUM_INTERFACES     1U
///*---------- -----------*/
//#define USBD_MAX_NUM_CONFIGURATION     1U
///*---------- -----------*/
//#define USBD_MAX_STR_DESC_SIZ     512U
///*---------- -----------*/
//#define USBD_DEBUG_LEVEL     3U
///*---------- -----------*/
//#define USBD_LPM_ENABLED     1U
///*---------- -----------*/
//#define USBD_SELF_POWERED     1U

/****************************************/
/* #define for FS and HS identification */
#define DEVICE_FS 		0
#define DEVICE_HS 		1

/**
  * @}
  */

/** @defgroup USBD_CONF_Exported_Macros USBD_CONF_Exported_Macros
  * @brief Aliases.
  * @{
  */

/* Memory management macros */

/** Alias for memory allocation. */
#define USBD_malloc         malloc

/** Alias for memory release. */
#define USBD_free           free

/** Alias for memory set. */
#define USBD_memset         memset

/** Alias for memory copy. */
#define USBD_memcpy         memcpy

/** Alias for delay. */
#define USBD_Delay          HAL_Delay

/* DEBUG macros */

#if (USBD_DEBUG_LEVEL > 0)
#define USBD_UsrLog(...)    printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_UsrLog(...)
#endif

#if (USBD_DEBUG_LEVEL > 1)

#define USBD_ErrLog(...)    printf("ERROR: ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_ErrLog(...)
#endif

#if (USBD_DEBUG_LEVEL > 2)
#define USBD_DbgLog(...)    printf("DEBUG : ") ;\
                            printf(__VA_ARGS__);\
                            printf("\n");
#else
#define USBD_DbgLog(...)
#endif

/**
  * @}
  */

/** @defgroup USBD_CONF_Exported_Types USBD_CONF_Exported_Types
  * @brief Types.
  * @{
  */

/**
  * @}
  */

/** @defgroup USBD_CONF_Exported_FunctionsPrototype USBD_CONF_Exported_FunctionsPrototype
  * @brief Declaration of public functions for Usb device.
  * @{
  */

/* Exported functions -------------------------------------------------------*/

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

#endif /* __USBD_CONF__H__ */
