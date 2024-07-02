/* generated thread header file - do not edit */
#ifndef SENSOR_THREAD0_H_
#define SENSOR_THREAD0_H_
#include "bsp_api.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "hal_data.h"
#ifdef __cplusplus
                extern "C" void sensor_thread0_entry(void * pvParameters);
                #else
extern void sensor_thread0_entry(void *pvParameters);
#endif
#include "rm_comms_i2c.h"
#include "rm_comms_api.h"
#include "r_gpt.h"
#include "r_timer_api.h"
FSP_HEADER
/* I2C Communication Device */
extern const rm_comms_instance_t g_comms_i2c_device0;
extern rm_comms_i2c_instance_ctrl_t g_comms_i2c_device0_ctrl;
extern const rm_comms_cfg_t g_comms_i2c_device0_cfg;
#ifndef comms_i2c_callback
void comms_i2c_callback(rm_comms_callback_args_t *p_args);
#endif
/** Timer on GPT Instance. */
extern const timer_instance_t g_timer0;

/** Access the GPT instance using these structures when calling API functions directly (::p_api is not used). */
extern gpt_instance_ctrl_t g_timer0_ctrl;
extern const timer_cfg_t g_timer0_cfg;

#ifndef NULL
void NULL(timer_callback_args_t *p_args);
#endif
FSP_FOOTER
#endif /* SENSOR_THREAD0_H_ */
