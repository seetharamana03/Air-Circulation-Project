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
 * File Name: r_ble_rtcs.h
 * Version : 1.0
 * Description : The header file for Real Time Clock service.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 31.12.2999 1.00 First Release
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @file
 * @defgroup rtcs Real Time Clock Service
 * @{
 * @ingroup profile
 * @brief   
 **********************************************************************************************************************/
#include "profile_cmn/r_ble_servs_if.h"
#include "gatt_db.h"

#ifndef R_BLE_RTCS_H
#define R_BLE_RTCS_H

/*----------------------------------------------------------------------------------------------------------------------
    Alive Time Characteristic
        Characteristic User Description descriptor : Characteristic User Description
----------------------------------------------------------------------------------------------------------------------*/

/***************************************************************************//**
 * @brief Characteristic User Description value structure.
*******************************************************************************/
typedef struct {
    uint8_t user_description[98]; /**< User Description */
    uint16_t length; /**< Length */
} st_ble_rtcs_time_char_user_desc_t;

/***************************************************************************//**
 * @brief     Set Alive Time characteristic value to the local GATT database.
 * @param[in] p_value  Characteristic value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_RTCS_SetTime(const int16_t *p_value);

/***************************************************************************//**
 * @brief     Get Alive Time characteristic value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_RTCS_GetTime(int16_t *p_value);

/***************************************************************************//**
 * @brief     Set Alive Time char user desc descriptor value to the local GATT database.
 * @param[in] p_value  Descriptor value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_RTCS_SetTimeCharUserDesc(const st_ble_rtcs_time_char_user_desc_t *p_value);

/***************************************************************************//**
 * @brief     Get Alive Time char user desc descriptor value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_RTCS_GetTimeCharUserDesc(st_ble_rtcs_time_char_user_desc_t *p_value);

/*----------------------------------------------------------------------------------------------------------------------
    Real Time Clock Service
----------------------------------------------------------------------------------------------------------------------*/

/***************************************************************************//**
 * @brief Real Time Clock characteristic Index.
*******************************************************************************/
typedef enum {
    BLE_RTCS_TIME_IDX,
    BLE_RTCS_TIME_CHAR_USER_DESC_IDX,
} e_ble_rtcs_char_idx_t;

/***************************************************************************//**
 * @brief Real Time Clock event type.
*******************************************************************************/
typedef enum {
    /* Alive Time */
    BLE_RTCS_EVENT_TIME_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_RTCS_TIME_IDX, BLE_SERVS_READ_REQ),
    BLE_RTCS_EVENT_TIME_CHAR_USER_DESC_WRITE_REQ = BLE_SERVS_ATTR_EVENT(BLE_RTCS_TIME_CHAR_USER_DESC_IDX, BLE_SERVS_WRITE_REQ),
    BLE_RTCS_EVENT_TIME_CHAR_USER_DESC_WRITE_COMP = BLE_SERVS_ATTR_EVENT(BLE_RTCS_TIME_CHAR_USER_DESC_IDX, BLE_SERVS_WRITE_COMP),
    BLE_RTCS_EVENT_TIME_CHAR_USER_DESC_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_RTCS_TIME_CHAR_USER_DESC_IDX, BLE_SERVS_READ_REQ),
} e_ble_rtcs_event_t;

/***************************************************************************//**
 * @brief     Initialize Real Time Clock service.
 * @param[in] cb Service callback.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_RTCS_Init(ble_servs_app_cb_t cb);

#endif /* R_BLE_RTCS_H */

/** @} */
