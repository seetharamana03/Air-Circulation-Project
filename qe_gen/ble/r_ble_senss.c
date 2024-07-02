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
 * File Name: r_ble_senss.c
 * Version : 1.0
 * Description : The source file for Sensor service.
 **********************************************************************************************************************/

#include "r_ble_senss.h"
#include "profile_cmn/r_ble_servs_if.h"
#include "gatt_db.h"

static st_ble_servs_info_t gs_servs_info;

/*----------------------------------------------------------------------------------------------------------------------
    Temperature Characteristic User Description descriptor : Characteristic User Description
----------------------------------------------------------------------------------------------------------------------*/

static ble_status_t decode_st_ble_senss_temp_char_user_desc_t(st_ble_senss_temp_char_user_desc_t *p_app_value, const st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Temperature Characteristic User Description descriptor value decode function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static ble_status_t encode_st_ble_senss_temp_char_user_desc_t(const st_ble_senss_temp_char_user_desc_t *p_app_value, st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Temperature Characteristic User Description descriptor value encode function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static const st_ble_servs_desc_info_t gs_temp_char_user_desc = {
    .attr_hdl = BLE_SENSS_TEMP_CHAR_USER_DESC_DESC_HDL,
    .app_size = sizeof(st_ble_senss_temp_char_user_desc_t),
    .desc_idx = BLE_SENSS_TEMP_CHAR_USER_DESC_IDX,
    .db_size  = BLE_SENSS_TEMP_CHAR_USER_DESC_LEN,
    .decode   = (ble_servs_attr_decode_t)decode_st_ble_senss_temp_char_user_desc_t,
    .encode   = (ble_servs_attr_encode_t)encode_st_ble_senss_temp_char_user_desc_t,
};

ble_status_t R_BLE_SENSS_SetTempCharUserDesc(const st_ble_senss_temp_char_user_desc_t *p_value)
{
    return R_BLE_SERVS_SetDesc(&gs_temp_char_user_desc, BLE_GAP_INVALID_CONN_HDL, (const void *)p_value);
}

ble_status_t R_BLE_SENSS_GetTempCharUserDesc(st_ble_senss_temp_char_user_desc_t *p_value)
{
    return R_BLE_SERVS_GetDesc(&gs_temp_char_user_desc, BLE_GAP_INVALID_CONN_HDL, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Temperature characteristic
----------------------------------------------------------------------------------------------------------------------*/

/* Temperature characteristic descriptor definition */
static const st_ble_servs_desc_info_t *gspp_temp_descs[] = { 
    &gs_temp_char_user_desc,
};

/* Temperature characteristic definition */
static const st_ble_servs_char_info_t gs_temp_char = {
    .start_hdl    = BLE_SENSS_TEMP_DECL_HDL,
    .end_hdl      = BLE_SENSS_TEMP_CHAR_USER_DESC_DESC_HDL,
    .char_idx     = BLE_SENSS_TEMP_IDX,
    .app_size     = sizeof(int16_t),
    .db_size      = BLE_SENSS_TEMP_LEN,
    .decode       = (ble_servs_attr_decode_t)decode_int16_t,
    .encode       = (ble_servs_attr_encode_t)encode_int16_t,
    .pp_descs     = gspp_temp_descs,
    .num_of_descs = ARRAY_SIZE(gspp_temp_descs),
};

ble_status_t R_BLE_SENSS_SetTemp(const int16_t *p_value)
{
    return R_BLE_SERVS_SetChar(&gs_temp_char, BLE_GAP_INVALID_CONN_HDL, (const void *)p_value);
}

ble_status_t R_BLE_SENSS_GetTemp(int16_t *p_value)
{
    return R_BLE_SERVS_GetChar(&gs_temp_char, BLE_GAP_INVALID_CONN_HDL, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Humidity Characteristic User Description descriptor : Characteristic User Description
----------------------------------------------------------------------------------------------------------------------*/

static ble_status_t decode_st_ble_senss_humid_char_user_desc_t(st_ble_senss_humid_char_user_desc_t *p_app_value, const st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Humidity Characteristic User Description descriptor value decode function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static ble_status_t encode_st_ble_senss_humid_char_user_desc_t(const st_ble_senss_humid_char_user_desc_t *p_app_value, st_ble_gatt_value_t *p_gatt_value)
{
    /* Start user code for Humidity Characteristic User Description descriptor value encode function. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    return BLE_SUCCESS;
}

static const st_ble_servs_desc_info_t gs_humid_char_user_desc = {
    .attr_hdl = BLE_SENSS_HUMID_CHAR_USER_DESC_DESC_HDL,
    .app_size = sizeof(st_ble_senss_humid_char_user_desc_t),
    .desc_idx = BLE_SENSS_HUMID_CHAR_USER_DESC_IDX,
    .db_size  = BLE_SENSS_HUMID_CHAR_USER_DESC_LEN,
    .decode   = (ble_servs_attr_decode_t)decode_st_ble_senss_humid_char_user_desc_t,
    .encode   = (ble_servs_attr_encode_t)encode_st_ble_senss_humid_char_user_desc_t,
};

ble_status_t R_BLE_SENSS_SetHumidCharUserDesc(const st_ble_senss_humid_char_user_desc_t *p_value)
{
    return R_BLE_SERVS_SetDesc(&gs_humid_char_user_desc, BLE_GAP_INVALID_CONN_HDL, (const void *)p_value);
}

ble_status_t R_BLE_SENSS_GetHumidCharUserDesc(st_ble_senss_humid_char_user_desc_t *p_value)
{
    return R_BLE_SERVS_GetDesc(&gs_humid_char_user_desc, BLE_GAP_INVALID_CONN_HDL, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Humidity characteristic
----------------------------------------------------------------------------------------------------------------------*/

/* Humidity characteristic descriptor definition */
static const st_ble_servs_desc_info_t *gspp_humid_descs[] = { 
    &gs_humid_char_user_desc,
};

/* Humidity characteristic definition */
static const st_ble_servs_char_info_t gs_humid_char = {
    .start_hdl    = BLE_SENSS_HUMID_DECL_HDL,
    .end_hdl      = BLE_SENSS_HUMID_CHAR_USER_DESC_DESC_HDL,
    .char_idx     = BLE_SENSS_HUMID_IDX,
    .app_size     = sizeof(int16_t),
    .db_size      = BLE_SENSS_HUMID_LEN,
    .decode       = (ble_servs_attr_decode_t)decode_int16_t,
    .encode       = (ble_servs_attr_encode_t)encode_int16_t,
    .pp_descs     = gspp_humid_descs,
    .num_of_descs = ARRAY_SIZE(gspp_humid_descs),
};

ble_status_t R_BLE_SENSS_SetHumid(const int16_t *p_value)
{
    return R_BLE_SERVS_SetChar(&gs_humid_char, BLE_GAP_INVALID_CONN_HDL, (const void *)p_value);
}

ble_status_t R_BLE_SENSS_GetHumid(int16_t *p_value)
{
    return R_BLE_SERVS_GetChar(&gs_humid_char, BLE_GAP_INVALID_CONN_HDL, (void *)p_value);
}

/*----------------------------------------------------------------------------------------------------------------------
    Sensor server
----------------------------------------------------------------------------------------------------------------------*/

/* Sensor characteristics definition */
static const st_ble_servs_char_info_t *gspp_chars[] = {
    &gs_temp_char,
    &gs_humid_char,
};

/* Sensor service definition */
static st_ble_servs_info_t gs_servs_info = {
    .pp_chars     = gspp_chars,
    .num_of_chars = ARRAY_SIZE(gspp_chars),
};

ble_status_t R_BLE_SENSS_Init(ble_servs_app_cb_t cb)
{
    if (NULL == cb)
    {
        return BLE_ERR_INVALID_PTR;
    }

    gs_servs_info.cb = cb;

    return R_BLE_SERVS_RegisterServer(&gs_servs_info);
}
