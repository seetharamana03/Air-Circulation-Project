/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products. No
* other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED. TO THE MAXIMUM
* EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES
* SHALL BE LIABLE FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS
* SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability of
* this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2019-2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/
/***********************************************************************************************************************
 * File Name: r_ble_senss.h
 * Version : 1.0
 * Description : The header file for Sensor service.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 31.12.2999 1.00 First Release
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @file
 * @defgroup senss Sensor Service
 * @{
 * @ingroup profile
 * @brief   
 **********************************************************************************************************************/
#include "profile_cmn/r_ble_servs_if.h"
#include "gatt_db.h"

#ifndef R_BLE_SENSS_H
#define R_BLE_SENSS_H

/*----------------------------------------------------------------------------------------------------------------------
    Temperature Characteristic
        Characteristic User Description descriptor : Characteristic User Description
----------------------------------------------------------------------------------------------------------------------*/

/***************************************************************************//**
 * @brief Characteristic User Description value structure.
*******************************************************************************/
typedef struct {
    uint8_t user_description[98]; /**< User Description */
    uint16_t length; /**< Length */
} st_ble_senss_temp_char_user_desc_t;

/***************************************************************************//**
 * @brief     Set Temperature characteristic value to the local GATT database.
 * @param[in] p_value  Characteristic value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_SetTemp(const int16_t *p_value);

/***************************************************************************//**
 * @brief     Get Temperature characteristic value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_GetTemp(int16_t *p_value);

/***************************************************************************//**
 * @brief     Set Temperature char user desc descriptor value to the local GATT database.
 * @param[in] p_value  Descriptor value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_SetTempCharUserDesc(const st_ble_senss_temp_char_user_desc_t *p_value);

/***************************************************************************//**
 * @brief     Get Temperature char user desc descriptor value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_GetTempCharUserDesc(st_ble_senss_temp_char_user_desc_t *p_value);

/*----------------------------------------------------------------------------------------------------------------------
    Humidity Characteristic
        Characteristic User Description descriptor : Characteristic User Description
----------------------------------------------------------------------------------------------------------------------*/

/***************************************************************************//**
 * @brief Characteristic User Description value structure.
*******************************************************************************/
typedef struct {
    uint8_t user_description[98]; /**< User Description */
    uint16_t length; /**< Length */
} st_ble_senss_humid_char_user_desc_t;

/***************************************************************************//**
 * @brief     Set Humidity characteristic value to the local GATT database.
 * @param[in] p_value  Characteristic value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_SetHumid(const int16_t *p_value);

/***************************************************************************//**
 * @brief     Get Humidity characteristic value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_GetHumid(int16_t *p_value);

/***************************************************************************//**
 * @brief     Set Humidity char user desc descriptor value to the local GATT database.
 * @param[in] p_value  Descriptor value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_SetHumidCharUserDesc(const st_ble_senss_humid_char_user_desc_t *p_value);

/***************************************************************************//**
 * @brief     Get Humidity char user desc descriptor value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_GetHumidCharUserDesc(st_ble_senss_humid_char_user_desc_t *p_value);

/*----------------------------------------------------------------------------------------------------------------------
    Sensor Service
----------------------------------------------------------------------------------------------------------------------*/

/***************************************************************************//**
 * @brief Sensor characteristic Index.
*******************************************************************************/
typedef enum {
    BLE_SENSS_TEMP_IDX,
    BLE_SENSS_TEMP_CHAR_USER_DESC_IDX,
    BLE_SENSS_HUMID_IDX,
    BLE_SENSS_HUMID_CHAR_USER_DESC_IDX,
} e_ble_senss_char_idx_t;

/***************************************************************************//**
 * @brief Sensor event type.
*******************************************************************************/
typedef enum {
    /* Temperature */
    BLE_SENSS_EVENT_TEMP_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_SENSS_TEMP_IDX, BLE_SERVS_READ_REQ),
    BLE_SENSS_EVENT_TEMP_CHAR_USER_DESC_WRITE_REQ = BLE_SERVS_ATTR_EVENT(BLE_SENSS_TEMP_CHAR_USER_DESC_IDX, BLE_SERVS_WRITE_REQ),
    BLE_SENSS_EVENT_TEMP_CHAR_USER_DESC_WRITE_COMP = BLE_SERVS_ATTR_EVENT(BLE_SENSS_TEMP_CHAR_USER_DESC_IDX, BLE_SERVS_WRITE_COMP),
    BLE_SENSS_EVENT_TEMP_CHAR_USER_DESC_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_SENSS_TEMP_CHAR_USER_DESC_IDX, BLE_SERVS_READ_REQ),
    /* Humidity */
    BLE_SENSS_EVENT_HUMID_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_SENSS_HUMID_IDX, BLE_SERVS_READ_REQ),
    BLE_SENSS_EVENT_HUMID_CHAR_USER_DESC_WRITE_REQ = BLE_SERVS_ATTR_EVENT(BLE_SENSS_HUMID_CHAR_USER_DESC_IDX, BLE_SERVS_WRITE_REQ),
    BLE_SENSS_EVENT_HUMID_CHAR_USER_DESC_WRITE_COMP = BLE_SERVS_ATTR_EVENT(BLE_SENSS_HUMID_CHAR_USER_DESC_IDX, BLE_SERVS_WRITE_COMP),
    BLE_SENSS_EVENT_HUMID_CHAR_USER_DESC_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_SENSS_HUMID_CHAR_USER_DESC_IDX, BLE_SERVS_READ_REQ),
} e_ble_senss_event_t;

/***************************************************************************//**
 * @brief     Initialize Sensor service.
 * @param[in] cb Service callback.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_SENSS_Init(ble_servs_app_cb_t cb);

#endif /* R_BLE_SENSS_H */

/** @} */
