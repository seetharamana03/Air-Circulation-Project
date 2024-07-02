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
 * File Name: r_ble_evktempctrls.h
 * Version : 1.0
 * Description : The header file for RA6M4 Temp Control service.
 **********************************************************************************************************************/
/***********************************************************************************************************************
 * History : DD.MM.YYYY Version Description
 *         : 31.12.2999 1.00 First Release
 ***********************************************************************************************************************/

/*******************************************************************************************************************//**
 * @file
 * @defgroup evktempctrls RA6M4 Temp Control Service
 * @{
 * @ingroup profile
 * @brief   
 **********************************************************************************************************************/
#include "profile_cmn/r_ble_servs_if.h"
#include "gatt_db.h"

#ifndef R_BLE_EVKTEMPCTRLS_H
#define R_BLE_EVKTEMPCTRLS_H

/*----------------------------------------------------------------------------------------------------------------------
    Temp Control Characteristic
----------------------------------------------------------------------------------------------------------------------*/
/***************************************************************************//**
 * @brief     Set Temp Control characteristic value to the local GATT database.
 * @param[in] p_value  Characteristic value to set.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_EVKTEMPCTRLS_SetTempctrl(const uint8_t *p_value);

/***************************************************************************//**
 * @brief     Get Temp Control characteristic value from the local GATT database.
 * @param[out] p_value  Output location for the acquired descriptor value.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_EVKTEMPCTRLS_GetTempctrl(uint8_t *p_value);

/*----------------------------------------------------------------------------------------------------------------------
    RA6M4 Temp Control Service
----------------------------------------------------------------------------------------------------------------------*/

/***************************************************************************//**
 * @brief RA6M4 Temp Control characteristic Index.
*******************************************************************************/
typedef enum {
    BLE_EVKTEMPCTRLS_TEMPCTRL_IDX,
} e_ble_evktempctrls_char_idx_t;

/***************************************************************************//**
 * @brief RA6M4 Temp Control event type.
*******************************************************************************/
typedef enum {
    /* Temp Control */
    BLE_EVKTEMPCTRLS_EVENT_TEMPCTRL_WRITE_REQ = BLE_SERVS_ATTR_EVENT(BLE_EVKTEMPCTRLS_TEMPCTRL_IDX, BLE_SERVS_WRITE_REQ),
    BLE_EVKTEMPCTRLS_EVENT_TEMPCTRL_WRITE_COMP = BLE_SERVS_ATTR_EVENT(BLE_EVKTEMPCTRLS_TEMPCTRL_IDX, BLE_SERVS_WRITE_COMP),
    BLE_EVKTEMPCTRLS_EVENT_TEMPCTRL_READ_REQ = BLE_SERVS_ATTR_EVENT(BLE_EVKTEMPCTRLS_TEMPCTRL_IDX, BLE_SERVS_READ_REQ),
} e_ble_evktempctrls_event_t;

/***************************************************************************//**
 * @brief     Initialize RA6M4 Temp Control service.
 * @param[in] cb Service callback.
 * @return    @ref ble_status_t
*******************************************************************************/
ble_status_t R_BLE_EVKTEMPCTRLS_Init(ble_servs_app_cb_t cb);

#endif /* R_BLE_EVKTEMPCTRLS_H */

/** @} */
