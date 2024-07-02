/* generated thread header file - do not edit */
#ifndef BLE_THREAD_H_
#define BLE_THREAD_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void ble_thread_entry(void * pvParameters);
                #else
extern void ble_thread_entry(void *pvParameters);
#endif
#include "r_sci_uart.h"
#include "r_uart_api.h"

#include "rm_ble_abs.h"
#include "rm_ble_abs_api.h"
FSP_HEADER
/** UART on SCI Instance. */
extern const uart_instance_t g_uart0;

/** Access the UART instance using these structures when calling API functions directly (::p_api is not used). */
extern sci_uart_instance_ctrl_t g_uart0_ctrl;
extern const uart_cfg_t g_uart0_cfg;
extern const sci_uart_extended_cfg_t g_uart0_cfg_extend;

#ifndef R_BLE_GTL_UartCallback
void R_BLE_GTL_UartCallback(uart_callback_args_t *p_args);
#endif

/** BLE_ABS on BLE Instance. */
extern const ble_abs_instance_t g_ble_abs0;

/** Access the BLE_ABS instance using these structures when calling API functions directly (::p_api is not used). */
extern ble_abs_instance_ctrl_t g_ble_abs0_ctrl;
extern const ble_abs_cfg_t g_ble_abs0_cfg;

/** Callback used by ble_abs_gtl Instance. */
#ifndef gap_cb
void gap_cb(uint16_t type, ble_status_t result, st_ble_evt_data_t *p_data);
#endif

#ifndef vs_cb
void vs_cb(uint16_t type, ble_status_t result, st_ble_vs_evt_data_t *p_data);
#endif

#ifndef gs_abs_gatts_cb_param
extern ble_abs_gatt_server_callback_set_t gs_abs_gatts_cb_param[];
#else
ble_abs_gatt_server_callback_set_t gs_abs_gatts_cb_param[];
#endif

#ifndef gs_abs_gattc_cb_param
extern ble_abs_gatt_client_callback_set_t gs_abs_gattc_cb_param[];
#else
ble_abs_gatt_client_callback_set_t gs_abs_gattc_cb_param[];
#endif
FSP_FOOTER
#endif /* BLE_THREAD_H_ */
