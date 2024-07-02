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

/******************************************************************************
* File Name    : app_main.c
* Device(s)    : RA4W1
* Tool-Chain   : e2Studio
* Description  : This is a application file for peripheral role.
*******************************************************************************/

/******************************************************************************
 Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <string.h>
#include "r_ble_api.h"
#include "rm_ble_abs.h"
#include "rm_ble_abs_api.h"
#include "gatt_db.h"
#include "profile_cmn/r_ble_servs_if.h"
#include "profile_cmn/r_ble_servc_if.h"
#include "hal_data.h"

/* This code is needed for using FreeRTOS */
#if (BSP_CFG_RTOS == 2 || BSP_CFG_RTOS_USED == 1)
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#define BLE_EVENT_PATTERN   (0x0A0A)
EventGroupHandle_t  g_ble_event_group_handle;
#endif
#include "r_ble_gats.h"
#include "r_ble_senss.h"
#include "r_ble_evktempctrls.h"
#include "r_ble_rtcs.h"
#include "ble_thread.h"

/******************************************************************************
 User file includes
*******************************************************************************/
/* Start user code for file includes. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

#define BLE_LOG_TAG "app_main"
#define BLE_GATTS_QUEUE_ELEMENTS_SIZE       (14)
#define BLE_GATTS_QUEUE_BUFFER_LEN          (245)
#define BLE_GATTS_QUEUE_NUM                 (1)

/******************************************************************************
 User macro definitions
*******************************************************************************/
/* Start user code for macro definitions. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/******************************************************************************
 Generated function prototype declarations
*******************************************************************************/
/* Internal functions */
void gap_cb(uint16_t type, ble_status_t result, st_ble_evt_data_t *p_data);
void gatts_cb(uint16_t type, ble_status_t result, st_ble_gatts_evt_data_t *p_data);
void gattc_cb(uint16_t type, ble_status_t result, st_ble_gattc_evt_data_t *p_data);
void vs_cb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *p_data);
ble_status_t ble_init(void);
void app_main(void);

/******************************************************************************
 User function prototype declarations
*******************************************************************************/
/* Start user code for function prototype declarations. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/******************************************************************************
 Generated global variables
*******************************************************************************/
/* Advertising Data */
static uint8_t gs_advertising_data[] =
{
    /* Flags */
    0x02, /**< Data Size */
    0x01, /**< Data Type */
    ( 0x06 ), /**< Data Value */

    /* Complete Local Name */
    0x0F, /**< Data Size */
    0x09, /**< Data Type */
    0x41, 0x69, 0x72, 0x43, 0x69, 0x72, 0x63, 0x75, 0x6c, 0x61, 0x74, 0x69, 0x6f, 0x6e, /**< Data Value */
};

ble_abs_legacy_advertising_parameter_t g_ble_advertising_parameter =
{
 .p_peer_address             = NULL,       ///< Peer address.
 .slow_advertising_interval  = 0x00000640, ///< Slow advertising interval. 1,000.0(ms)
 .slow_advertising_period    = 0x0000,     ///< Slow advertising period.
 .p_advertising_data         = gs_advertising_data,             ///< Advertising data. If p_advertising_data is specified as NULL, advertising data is not set.
 .advertising_data_length    = ARRAY_SIZE(gs_advertising_data), ///< Advertising data length (in bytes).
 .advertising_filter_policy  = BLE_ABS_ADVERTISING_FILTER_ALLOW_ANY, ///< Advertising Filter Policy.
 .advertising_channel_map    = ( BLE_GAP_ADV_CH_37 | BLE_GAP_ADV_CH_38 | BLE_GAP_ADV_CH_39 ), ///< Channel Map.
 .own_bluetooth_address_type = BLE_GAP_ADDR_RAND, ///< Own Bluetooth address type.
 .own_bluetooth_address      = { 0 },
};

/* GATT server callback parameters */
ble_abs_gatt_server_callback_set_t gs_abs_gatts_cb_param[] =
{
    {
        .gatt_server_callback_function = gatts_cb,
        .gatt_server_callback_priority = 1,
    },
    {
        .gatt_server_callback_function = NULL,
    }
};

/* GATT client callback parameters */
ble_abs_gatt_client_callback_set_t gs_abs_gattc_cb_param[] =
{
    {
        .gatt_client_callback_function = gattc_cb,
        .gatt_client_callback_priority = 1,
    },
    {
        .gatt_client_callback_function = NULL,
    }
};

/* GATT server Prepare Write Queue parameters */
static st_ble_gatt_queue_elm_t  gs_queue_elms[BLE_GATTS_QUEUE_ELEMENTS_SIZE];
static uint8_t gs_buffer[BLE_GATTS_QUEUE_BUFFER_LEN];
static st_ble_gatt_pre_queue_t gs_queue[BLE_GATTS_QUEUE_NUM] = {
    {
        .p_buf_start = gs_buffer,
        .buffer_len  = BLE_GATTS_QUEUE_BUFFER_LEN,
        .p_queue     = gs_queue_elms,
        .queue_size  = BLE_GATTS_QUEUE_ELEMENTS_SIZE,
    }
};

/* Connection handle */
uint16_t g_conn_hdl;

/******************************************************************************
 User global variables
*******************************************************************************/
/* Start user code for global variables. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/******************************************************************************
 Generated function definitions
*******************************************************************************/
/******************************************************************************
 * Function Name: gap_cb
 * Description  : Callback function for GAP API.
 * Arguments    : uint16_t type -
 *                  Event type of GAP API.
 *              : ble_status_t result -
 *                  Event result of GAP API.
 *              : st_ble_vs_evt_data_t *p_data - 
 *                  Event parameters of GAP API.
 * Return Value : none
 ******************************************************************************/
void gap_cb(uint16_t type, ble_status_t result, st_ble_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GAP callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    switch(type)
    {
        case BLE_GAP_EVENT_STACK_ON:
        {
            /* Get BD address for Advertising */
            R_BLE_VS_GetBdAddr(BLE_VS_ADDR_AREA_REG, BLE_GAP_ADDR_RAND);
        } break;

        case BLE_GAP_EVENT_CONN_IND:
        {
            if (BLE_SUCCESS == result)
            {
                /* Store connection handle */
                st_ble_gap_conn_evt_t *p_gap_conn_evt_param = (st_ble_gap_conn_evt_t *)p_data->p_param;
                g_conn_hdl = p_gap_conn_evt_param->conn_hdl;
            }
            else
            {
                /* Restart advertising when connection failed */
                RM_BLE_ABS_StartLegacyAdvertising(&g_ble_abs0_ctrl, &g_ble_advertising_parameter);
            }
        } break;

        case BLE_GAP_EVENT_DISCONN_IND:
        {
            /* Restart advertising when disconnected */
            g_conn_hdl = BLE_GAP_INVALID_CONN_HDL;
            RM_BLE_ABS_StartLegacyAdvertising(&g_ble_abs0_ctrl, &g_ble_advertising_parameter);
        } break;

        case BLE_GAP_EVENT_CONN_PARAM_UPD_REQ:
        {
            /* Send connection update response with value received on connection update request */
            st_ble_gap_conn_upd_req_evt_t *p_conn_upd_req_evt_param = (st_ble_gap_conn_upd_req_evt_t *)p_data->p_param;

            st_ble_gap_conn_param_t conn_updt_param = {
                .conn_intv_min = p_conn_upd_req_evt_param->conn_intv_min,
                .conn_intv_max = p_conn_upd_req_evt_param->conn_intv_max,
                .conn_latency  = p_conn_upd_req_evt_param->conn_latency,
                .sup_to        = p_conn_upd_req_evt_param->sup_to,
            };

            R_BLE_GAP_UpdConn(p_conn_upd_req_evt_param->conn_hdl,
                              BLE_GAP_CONN_UPD_MODE_RSP,
                              BLE_GAP_CONN_UPD_ACCEPT,
                              &conn_updt_param);
        } break;

/* Hint: Add cases of GAP event macros defined as BLE_GAP_XXX */
/* Start user code for GAP callback function event process. Do not edit comment generated here */
            /* End user code. Do not edit comment generated here */
    }
}

/******************************************************************************
 * Function Name: gatts_cb
 * Description  : Callback function for GATT Server API.
 * Arguments    : uint16_t type -
 *                  Event type of GATT Server API.
 *              : ble_status_t result -
 *                  Event result of GATT Server API.
 *              : st_ble_gatts_evt_data_t *p_data - 
 *                  Event parameters of GATT Server API.
 * Return Value : none
 ******************************************************************************/
void gatts_cb(uint16_t type, ble_status_t result, st_ble_gatts_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GATT Server callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    R_BLE_SERVS_GattsCb(type, result, p_data);
    switch(type)
    {
/* Hint: Add cases of GATT Server event macros defined as BLE_GATTS_XXX */
/* Start user code for GATT Server callback function event process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    }
}

/******************************************************************************
 * Function Name: gattc_cb
 * Description  : Callback function for GATT Client API.
 * Arguments    : uint16_t type -
 *                  Event type of GATT Client API.
 *              : ble_status_t result -
 *                  Event result of GATT Client API.
 *              : st_ble_gattc_evt_data_t *p_data - 
 *                  Event parameters of GATT Client API.
 * Return Value : none
 ******************************************************************************/
void gattc_cb(uint16_t type, ble_status_t result, st_ble_gattc_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GATT Client callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    R_BLE_SERVC_GattcCb(type, result, p_data);
    switch(type)
    {

/* Hint: Add cases of GATT Client event macros defined as BLE_GATTC_XXX */
/* Start user code for GATT Client callback function event process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    }
}

/******************************************************************************
 * Function Name: vs_cb
 * Description  : Callback function for Vendor Specific API.
 * Arguments    : uint16_t type -
 *                  Event type of Vendor Specific API.
 *              : ble_status_t result -
 *                  Event result of Vendor Specific API.
 *              : st_ble_vs_evt_data_t *p_data - 
 *                  Event parameters of Vendor Specific API.
 * Return Value : none
 ******************************************************************************/
void vs_cb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for vender specific callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    
    R_BLE_SERVS_VsCb(type, result, p_data);
    switch(type)
    {
        case BLE_VS_EVENT_GET_ADDR_COMP:
        {
            /* Start advertising when BD address is ready */
            st_ble_vs_get_bd_addr_comp_evt_t * get_address = (st_ble_vs_get_bd_addr_comp_evt_t *)p_data->p_param;
            memcpy(g_ble_advertising_parameter.own_bluetooth_address, get_address->addr.addr, BLE_BD_ADDR_LEN);
            RM_BLE_ABS_StartLegacyAdvertising(&g_ble_abs0_ctrl, &g_ble_advertising_parameter);
        } break;

/* Hint: Add cases of vender specific event macros defined as BLE_VS_XXX */
/* Start user code for vender specific callback function event process. Do not edit comment generated here */
            /* End user code. Do not edit comment generated here */
    }
}

/******************************************************************************
 * Function Name: gats_cb
 * Description  : Callback function for GATT Service server feature.
 * Arguments    : uint16_t type -
 *                  Event type of GATT Service server feature.
 *              : ble_status_t result -
 *                  Event result of GATT Service server feature.
 *              : st_ble_servs_evt_data_t *p_data - 
 *                  Event parameters of GATT Service server feature.
 * Return Value : none
 ******************************************************************************/
static void gats_cb(uint16_t type, ble_status_t result, st_ble_servs_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for GATT Service Server callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    switch(type)
    {
/* Hint: Add cases of GATT Service server events defined in e_ble_gats_event_t */
/* Start user code for GATT Service Server callback function event process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    }    
}

/******************************************************************************
 * Function Name: senss_cb
 * Description  : Callback function for Sensor server feature.
 * Arguments    : uint16_t type -
 *                  Event type of Sensor server feature.
 *              : ble_status_t result -
 *                  Event result of Sensor server feature.
 *              : st_ble_servs_evt_data_t *p_data - 
 *                  Event parameters of Sensor server feature.
 * Return Value : none
 ******************************************************************************/
static void senss_cb(uint16_t type, ble_status_t result, st_ble_servs_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for Sensor Server callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    switch(type)
    {
/* Hint: Add cases of Sensor server events defined in e_ble_senss_event_t */
/* Start user code for Sensor Server callback function event process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    }    
}

/******************************************************************************
 * Function Name: evktempctrls_cb
 * Description  : Callback function for RA6M4 Temp Control server feature.
 * Arguments    : uint16_t type -
 *                  Event type of RA6M4 Temp Control server feature.
 *              : ble_status_t result -
 *                  Event result of RA6M4 Temp Control server feature.
 *              : st_ble_servs_evt_data_t *p_data - 
 *                  Event parameters of RA6M4 Temp Control server feature.
 * Return Value : none
 ******************************************************************************/
static void evktempctrls_cb(uint16_t type, ble_status_t result, st_ble_servs_evt_data_t *p_data)
{
    /* Hint: Input common process of callback function such as variable definitions */
    /* Start user code for RA6M4 Temp Control Server callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    switch (type)
    {
        case BLE_EVKTEMPCTRLS_EVENT_TEMPCTRL_WRITE_REQ:
        {
            if (BLE_SUCCESS == result)
            {
                uint8_t state = *(uint8_t*) p_data->p_param;
                uint8_t data[1] = { state };
                        xQueueSend(g_ble_queue, (uint8_t* )data, 0);
                        xEventGroupSetBits (g_ble_event_group_handle, BLE_EVENT_PATTERN);
            }
        }
            /* Hint: Add cases of RA6M4 Temp Control server events defined in e_ble_evktempctrls_event_t */
            /* Start user code for RA6M4 Temp Control Server callback function event process. Do not edit comment generated here */
            /* End user code. Do not edit comment generated here */
    }
}

/******************************************************************************
 * Function Name: rtcs_cb
 * Description  : Callback function for Real Time Clock server feature.
 * Arguments    : uint16_t type -
 *                  Event type of Real Time Clock server feature.
 *              : ble_status_t result -
 *                  Event result of Real Time Clock server feature.
 *              : st_ble_servs_evt_data_t *p_data - 
 *                  Event parameters of Real Time Clock server feature.
 * Return Value : none
 ******************************************************************************/
static void rtcs_cb(uint16_t type, ble_status_t result, st_ble_servs_evt_data_t *p_data)
{
/* Hint: Input common process of callback function such as variable definitions */
/* Start user code for Real Time Clock Server callback function common process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    switch(type)
    {
/* Hint: Add cases of Real Time Clock server events defined in e_ble_rtcs_event_t */
/* Start user code for Real Time Clock Server callback function event process. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
    }    
}
/******************************************************************************
 * Function Name: ble_init
 * Description  : Initialize BLE and profiles.
 * Arguments    : none
 * Return Value : BLE_SUCCESS - SUCCESS
 *                BLE_ERR_INVALID_OPERATION -
 *                    Failed to initialize BLE or profiles.
 ******************************************************************************/
ble_status_t ble_init(void)
{
    ble_status_t status;
    fsp_err_t err;

    /* Initialize BLE */
    err = RM_BLE_ABS_Open(&g_ble_abs0_ctrl, &g_ble_abs0_cfg);
    if (FSP_SUCCESS != err)
    {
        return err;
    }

    /* Initialize GATT Database */
    status = R_BLE_GATTS_SetDbInst(NULL);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize GATT server */
    status = R_BLE_SERVS_Init();
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /*Initialize GATT client */
    status = R_BLE_SERVC_Init();
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }
    
    /* Set Prepare Write Queue */
    R_BLE_GATTS_SetPrepareQueue(gs_queue, BLE_GATTS_QUEUE_NUM);

    /* Initialize GATT Service server API */
    status = R_BLE_GATS_Init(gats_cb);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize Sensor server API */
    status = R_BLE_SENSS_Init(senss_cb);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize RA6M4 Temp Control server API */
    status = R_BLE_EVKTEMPCTRLS_Init(evktempctrls_cb);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    /* Initialize Real Time Clock server API */
    status = R_BLE_RTCS_Init(rtcs_cb);
    if (BLE_SUCCESS != status)
    {
        return BLE_ERR_INVALID_OPERATION;
    }

    return status;
}

/******************************************************************************
 * Function Name: app_main
 * Description  : Application main function with main loop
 * Arguments    : none
 * Return Value : none
 ******************************************************************************/
void app_main(void)
{
#if (BSP_CFG_RTOS == 2 || BSP_CFG_RTOS_USED == 1)
    /* Create Event Group */
    g_ble_event_group_handle = xEventGroupCreate ();
    assert(g_ble_event_group_handle);
#endif

    /* Initialize BLE and profiles */
    ble_init ();

    /* Hint: Input process that should be done before main loop such as calling initial function or variable definitions */
    /* Start user code for process before main loop. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    /* main loop */
    while (1)
    {
        /* Process BLE Event */
        R_BLE_Execute ();

        /* When this BLE application works on the FreeRTOS */
#if (BSP_CFG_RTOS == 2 || BSP_CFG_RTOS_USED == 1)
        if (0 != R_BLE_IsTaskFree ())
        {
            /* If the BLE Task has no operation to be processed, it transits block state until the event from RF transciever occurs. */
            xEventGroupWaitBits (g_ble_event_group_handle, (EventBits_t) BLE_EVENT_PATTERN,
            pdTRUE,
                                 pdFALSE,
                                 portMAX_DELAY);
        }
#endif

        /* Hint: Input process that should be done during main loop such as calling processing functions */
        /* Start user code for process during main loop. Do not edit comment generated here */
        /* End user code. Do not edit comment generated here */
        int16_t sens_data[2] =
        { 0 };
        if (pdTRUE == xQueueReceive (g_sensor_queue, &sens_data[0], 0))
        {
            (void) R_BLE_SENSS_SetTemp (&sens_data[0]);
            (void) R_BLE_SENSS_SetHumid (&sens_data[1]);
        }

        int16_t time_data[1] = { 0 };
        if (pdTRUE == xQueueReceive (g_rtc_queue, &time_data[0], 0)){
            (void) R_BLE_RTCS_SetTime(&time_data[0]);
        }

    }
    /* Hint: Input process that should be done after main loop such as calling closing functions */
    /* Start user code for process after main loop. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */

    /* Terminate BLE */
    RM_BLE_ABS_Close (&g_ble_abs0_ctrl);
}
/******************************************************************************
 User function definitions
 *******************************************************************************/
/* Start user code for function definitions. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
