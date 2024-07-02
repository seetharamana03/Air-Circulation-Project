/* generated common header file - do not edit */
#ifndef COMMON_DATA_H_
#define COMMON_DATA_H_
#include <stdint.h>
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "r_sci_i2c.h"
#include "r_i2c_master_api.h"
#include "rm_comms_i2c.h"
#include "rm_comms_api.h"
#include "r_ioport.h"
#include "bsp_pin_cfg.h"
FSP_HEADER
#define BLE_CFG_DA14531_DEVICE              1
#define BLE_CFG_DEVICE_ROLE                (0x0A)
extern const i2c_master_cfg_t g_i2c_master0_cfg;
/* I2C on SCI Instance. */
extern const i2c_master_instance_t g_i2c_master0;
#ifndef rm_comms_i2c_callback
void rm_comms_i2c_callback(i2c_master_callback_args_t *p_args);
#endif

extern const sci_i2c_extended_cfg_t g_i2c_master0_cfg_extend;
extern sci_i2c_instance_ctrl_t g_i2c_master0_ctrl;
/* I2C Shared Bus */
extern rm_comms_i2c_bus_extended_cfg_t g_comms_i2c_bus0_extended_cfg;
#define IOPORT_CFG_NAME g_bsp_pin_cfg
#define IOPORT_CFG_OPEN R_IOPORT_Open
#define IOPORT_CFG_CTRL g_ioport_ctrl

/* IOPORT Instance */
extern const ioport_instance_t g_ioport;

/* IOPORT control structure. */
extern ioport_instance_ctrl_t g_ioport_ctrl;
extern QueueHandle_t g_sensor_queue;
extern QueueHandle_t g_ble_queue;
extern QueueHandle_t g_rtc_queue;
void g_common_init(void);
FSP_FOOTER
#endif /* COMMON_DATA_H_ */
