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
 * File Name: r_ble_rtcs.c
 * Version : 1.0
 * Description : The source file for Real Time Clock service.
 **********************************************************************************************************************/

#include "r_ble_rtcs.h"
#include "profile_cmn/r_ble_servs_if.h"
#include "gatt_db.h"

static st_ble_servs_info_t gs_servs_info;

/*----------------------------------------------------------------------------------------------------------------------
    Alive Time Characteristic User Description descriptor : Characteristic User Description
----------------------------------------------------------------------------------------------------------------------*/

static ble_status_t decode_st_ble_rtcs_time_char_user_desc_t(st_ble_rtcs_time_char_user_desc_t *p_app_value, const st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Alive Time Characteristic User Description descriptor value decode function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static ble_status_t encode_st_ble_rtcs_time_char_user_desc_t(const st_ble_rtcs_time_char_user_desc_t *p_app_value, st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Alive Time Characteristic User Description descriptor value encode function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static const st_ble_servs_desc_info_t gs_time_char_user_desc = {
    .attr_hdl = BLE_RTCS_TIME_CHAR_USER_DESC_DESC_HDL,
    .app_size = sizeof(st_ble_rtcs_time_char_user_desc_t),
    .desc_idx = BLE_RTCS_TIME_CHAR_USER_DESC_IDX,
    .db_size  = BLE_RTCS_TIME_CHAR_USER_DESC_LEN,
    .decode   = (ble_servs_attr_decode_t)decode_st_ble_rtcs_time_char_user_desc_t,
    .encode   = (ble_servs_attr_encode_t)encode_st_ble_rtcs_time_char_user_desc_t,
};

ble_status_t R_BLE_RTCS_SetTimeCharUserDesc(const st_ble_rtcs_time_char_user_desc_t *p_value)
{
    return R_BLE_SERVS_SetDesc(&gs_time_char_user_desc, BLE_GAP_INVALID_CONN_HDL, (const void *)p_value);
}

ble_status_t R_BLE_RTCS_GetTimeCharUserDesc(st_ble_rtcs_time_char_user_desc_t *p_value)
{
    return R_BLE_SERVS_GetDesc(&gs_time_char_user_desc, BLE_GAP_INVALID_CONN_HDL, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Alive Time characteristic
----------------------------------------------------------------------------------------------------------------------*/

/* Alive Time characteristic descriptor definition */
static const st_ble_servs_desc_info_t *gspp_time_descs[] = { 
    &gs_time_char_user_desc,
};

/* Alive Time characteristic definition */
static const st_ble_servs_char_info_t gs_time_char = {
    .start_hdl    = BLE_RTCS_TIME_DECL_HDL,
    .end_hdl      = BLE_RTCS_TIME_CHAR_USER_DESC_DESC_HDL,
    .char_idx     = BLE_RTCS_TIME_IDX,
    .app_size     = sizeof(int16_t),
    .db_size      = BLE_RTCS_TIME_LEN,
    .decode       = (ble_servs_attr_decode_t)decode_int16_t,
    .encode       = (ble_servs_attr_encode_t)encode_int16_t,
    .pp_descs     = gspp_time_descs,
    .num_of_descs = ARRAY_SIZE(gspp_time_descs),
};

ble_status_t R_BLE_RTCS_SetTime(const int16_t *p_value)
{
    return R_BLE_SERVS_SetChar(&gs_time_char, BLE_GAP_INVALID_CONN_HDL, (const void *)p_value);
}

ble_status_t R_BLE_RTCS_GetTime(int16_t *p_value)
{
    return R_BLE_SERVS_GetChar(&gs_time_char, BLE_GAP_INVALID_CONN_HDL, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Real Time Clock server
----------------------------------------------------------------------------------------------------------------------*/

/* Real Time Clock characteristics definition */
static const st_ble_servs_char_info_t *gspp_chars[] = {
    &gs_time_char,
};

/* Real Time Clock service definition */
static st_ble_servs_info_t gs_servs_info = {
    .pp_chars     = gspp_chars,
    .num_of_chars = ARRAY_SIZE(gspp_chars),
};

ble_status_t R_BLE_RTCS_Init(ble_servs_app_cb_t cb)
{
    if (NULL == cb)
    {
        return BLE_ERR_INVALID_PTR;
    }

    gs_servs_info.cb = cb;

    return R_BLE_SERVS_RegisterServer(&gs_servs_info);
}
