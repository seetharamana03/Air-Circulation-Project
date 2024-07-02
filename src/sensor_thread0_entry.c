#include <sensor_thread0.h>
#include "SEGGER_RTT/SEGGER_RTT.h"
#include "rtc_ep.h"
#include "common_utils.h"
#include "event_groups.h"
#include "r_ble_api.h"
/* New Thread entry function */

#define READ                    0x00
#define SLEEP                   0x50
#define CLEAN                   0x51
#define RESET                   0x52
#define MAVE                    0x53
#define TINTC_H                 0x5A
#define TINTC_L                 0x5B
#define TCLEAN                  0x5C
#define SPEEDFAN                0x63
#define TX_LENGTH               2

#define BLE_EVENT_PATTERN  (0x0A0A)
extern EventGroupHandle_t g_ble_event_group_handle;

float g_temp = 0.0f;
float g_humid = 0.0f;
int16_t alive_time = 0;

rtc_time_t g_set_time =
{ .tm_hour = RESET_VALUE,
  .tm_isdst = RESET_VALUE,
  .tm_mday = RESET_VALUE,
  .tm_min = RESET_VALUE,
  .tm_mon = RESET_VALUE,
  .tm_sec = RESET_VALUE,
  .tm_wday = RESET_VALUE,
  .tm_yday = RESET_VALUE,
  .tm_year = RESET_VALUE, };

rtc_time_t g_get_time =
{ .tm_hour = RESET_VALUE,
  .tm_isdst = RESET_VALUE,
  .tm_mday = RESET_VALUE,
  .tm_min = RESET_VALUE,
  .tm_mon = RESET_VALUE,
  .tm_sec = RESET_VALUE,
  .tm_wday = RESET_VALUE,
  .tm_yday = RESET_VALUE,
  .tm_year = RESET_VALUE, };

rtc_time_t time_diff =
{ .tm_hour = RESET_VALUE,
  .tm_isdst = RESET_VALUE,
  .tm_mday = RESET_VALUE,
  .tm_min = RESET_VALUE,
  .tm_mon = RESET_VALUE,
  .tm_sec = RESET_VALUE,
  .tm_wday = RESET_VALUE,
  .tm_yday = RESET_VALUE,
  .tm_year = RESET_VALUE, };

/* pvParameters contains TaskHandle_t */
void sensor_thread0_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED(pvParameters);

    /* TODO: add your own code here */
    i2c_master_status_t p_status;
    fsp_err_t err = FSP_SUCCESS;

    //*********RTC Timer Code*******************************************
    err = R_RTC_Open (&g_rtc0_ctrl, &g_rtc0_cfg);
    assert(err == FSP_SUCCESS);

    err = R_RTC_CalendarTimeSet (&g_rtc0_ctrl, &g_set_time);
    assert(err == FSP_SUCCESS);

    //err = R_RTC_PeriodicIrqRateSet(&g_rtc0_ctrl, RTC_PERIODIC_IRQ_SELECT_1_SECOND);
    //assert(err == FSP_SUCCESS);

    //*********IIC Sensor Code******************************************

    uint8_t sensor_data[37] =
    { 0 };
    uint8_t TX_BUFFER[TX_LENGTH] =
    { 0 };
    TX_BUFFER[0] = CLEAN;
    TX_BUFFER[1] = 0x01;

    uint8_t TX_BUFFER2[TX_LENGTH] =
    { 0 };
    TX_BUFFER2[0] = READ;

    rm_comms_i2c_bus_extended_cfg_t* p_extend = (rm_comms_i2c_bus_extended_cfg_t*) g_comms_i2c_device0_cfg.p_extend;
    i2c_master_instance_t* p_driver_instance = (i2c_master_instance_t*) p_extend->p_driver_instance;
    p_driver_instance->p_api->open(p_driver_instance->p_ctrl,p_driver_instance->p_cfg);

    if(p_extend->p_blocking_semaphore != NULL){
        *(p_extend->p_blocking_semaphore->p_semaphore_handle) = xSemaphoreCreateCountingStatic((UBaseType_t) 1,(UBaseType_t) 0,p_extend->p_blocking_semaphore->p_semaphore_memory);
    }

    if(p_extend->p_bus_recursive_mutex != NULL){
            *(p_extend->p_bus_recursive_mutex->p_mutex_handle) = xSemaphoreCreateRecursiveMutexStatic(p_extend->p_bus_recursive_mutex->p_mutex_memory);
        }


    //open verification
    err = RM_COMMS_I2C_Open (&g_comms_i2c_device0_ctrl, &g_comms_i2c_device0_cfg);
    if (err == FSP_SUCCESS)
    {
        APP_PRINT("Open IS SUCCESSFUL \r\n");
    }
    else
    {
        APP_ERR_PRINT("ERROR ON READ%d", err);
    }
    vTaskDelay (500);

//    err = RM_COMMS_I2C_StatusGet (&g_comms_i2c_device0, &p_status);
//    APP_PRINT("%s \r\n", p_status);

    //clean function for fan
        err = RM_COMMS_I2C_Write (&g_comms_i2c_device0_ctrl, &TX_BUFFER[0], 2);
        if (err == FSP_SUCCESS)
        {
            APP_PRINT("Clean Function IS SUCCESSFUL \r\n");
        }
        else
        {
            APP_ERR_PRINT("ERROR ON READ%d", err);
        }
        vTaskDelay (500);

    //read sensor data
    err = RM_COMMS_I2C_Write (&g_comms_i2c_device0_ctrl, &TX_BUFFER2[0], 1);
    if (err == FSP_SUCCESS)
    {
        APP_PRINT("Write Function IS SUCCESSFUL \r\n");
    }
    vTaskDelay (500);

    err = RM_COMMS_I2C_Read (&g_comms_i2c_device0_ctrl, &sensor_data[0], 38);
    assert(err == FSP_SUCCESS);
    vTaskDelay (500);

    //*********General PWM Code******************************************

    err = R_GPT_Open (&g_timer0_ctrl, &g_timer0_cfg);
    if (err != FSP_SUCCESS)
    {
        err = R_GPT_Close (&g_timer0_ctrl);
        assert(err == FSP_SUCCESS);
    }

    err = R_GPT_Start (&g_timer0_ctrl);
    if (err != FSP_SUCCESS)
    {
        err = R_GPT_Close (&g_timer0_ctrl);
        assert(err == FSP_SUCCESS);
    }

    while (1)
    {
        uint8_t byte_temperature[2] =
        { sensor_data[25], sensor_data[24] };
        uint8_t byte_temperature2[2] =
        { sensor_data[24], sensor_data[25] };
        uint8_t byte_humidity[2] =
        { sensor_data[27], sensor_data[26] };
        uint8_t byte_humidity2[2] =
        { sensor_data[26], sensor_data[27] };
        int16_t int_temperature[1] =
        { 0 };
        int16_t int_temperature2[1] =
        { 0 };
        int16_t int_humidity[1] =
        { 0 };
        int16_t int_humidity2[1] =
        { 0 };
        memcpy (&int_temperature, byte_temperature, 2);
        memcpy (&int_temperature2, byte_temperature2, 2);
        memcpy (&int_humidity, byte_humidity, 2);
        memcpy (&int_humidity2, byte_humidity2, 2);
        //check this code if it doesn't work
        int16_t data[2] =
        { int_temperature2[0], int_humidity2[0] };
        xQueueSend(g_sensor_queue, (uint32_t* )data, 0);
        xEventGroupSetBits (g_ble_event_group_handle, BLE_EVENT_PATTERN);
        g_temp = (float) int_temperature[0];
        g_humid = (float) int_humidity[0];

        int8_t set_temp[1] =
        { 0 };
        if (pdTRUE == xQueueReceive (g_ble_queue, &set_temp[0], 0))
        {
            uint32_t duty_cycle_counts = RESET_VALUE;
            uint32_t current_period_counts = RESET_VALUE;
            timer_info_t info =
            { (timer_direction_t) RESET_VALUE, RESET_VALUE, RESET_VALUE };

            /* Get the current period setting. */
            err = R_GPT_InfoGet (&g_timer0_ctrl, &info);
            if (FSP_SUCCESS != err)
            {
                /* GPT Timer InfoGet Failure message */
                APP_ERR_PRINT("\r\n ** R_GPT_InfoGet API failed ** \r\n");
            }
            else
            {
                /* update period counts locally. */
                current_period_counts = info.period_counts;
            }

            if ((*set_temp) != 0x00)
            {
                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_04_PIN_15, BSP_IO_LEVEL_HIGH);
                duty_cycle_counts = (uint32_t) ((uint64_t) (current_period_counts * 100) / 100);

                err = R_GPT_DutyCycleSet (&g_timer0_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
                if (FSP_SUCCESS != err)
                {
                    err = R_GPT_Close (&g_timer0_ctrl);
                    APP_ERR_PRINT("\r\n ** R_GPT_DutyCycleSet API failed ** \r\n");
                }
//                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_03_PIN_04, BSP_IO_LEVEL_HIGH);
            }
            else
            {
                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_04_PIN_15, BSP_IO_LEVEL_LOW);
                duty_cycle_counts = (uint32_t) ((uint64_t) (current_period_counts * 0) / 100);

                err = R_GPT_DutyCycleSet (&g_timer0_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
                if (FSP_SUCCESS != err)
                {
                    err = R_GPT_Close (&g_timer0_ctrl);
                    APP_ERR_PRINT("\r\n ** R_GPT_DutyCycleSet API failed ** \r\n");
                }
//                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_03_PIN_04, BSP_IO_LEVEL_HIGH);
            }
            if (FSP_SUCCESS != err)
            {
                APP_ERR_PRINT("** R_GPT_DutyCycleSet API failed ** \r\n");
            }
        }

        uint16_t alive_time2[1] =
        { 0 };
        uint16_t alive_time3[1] =
        { 0 };

        err = R_RTC_CalendarTimeGet (&g_rtc0_ctrl, &g_get_time);
        assert(err == FSP_SUCCESS);
        time_diff.tm_sec = (int) difftime (g_get_time.tm_sec, g_set_time.tm_sec);
        time_diff.tm_min = (int) difftime (g_get_time.tm_min, g_set_time.tm_min);
        time_diff.tm_hour = (int) difftime (g_get_time.tm_hour, g_set_time.tm_hour);

        alive_time = (int16_t) ((time_diff.tm_sec) + (time_diff.tm_min * 60) + (time_diff.tm_hour * 3600));
        alive_time3[0] = (uint16_t) ((time_diff.tm_sec) + (time_diff.tm_min * 60) + (time_diff.tm_hour * 3600));

        uint8_t alive_time_lsb = (alive_time3[0] & 0xFF00U) >> 8U;
        uint8_t alive_time_msb = (alive_time3[0] & 0x00FFU);

        uint8_t alive_time_byte[2] =
        { alive_time_lsb, alive_time_msb };
        memcpy (&alive_time2, alive_time_byte, 2);

        xQueueSend(g_rtc_queue, (uint32_t* )alive_time2, 0);
        xEventGroupSetBits (g_ble_event_group_handle, BLE_EVENT_PATTERN);

        vTaskDelay (100);

//        uint8_t byte_humidity[2] =
//        { sensor_data[27], sensor_data[26] };
//        int int_humidity[1] =
//        { 0 };
//        memcpy (&int_humidity, byte_humidity, 2);
//        APP_PRINT ("Humidity = %02d\n", int_humidity[0]);
//
//        uint8_t byte_carbon_dioxide[2] = {sensor_data[31],sensor_data[30]};
//        int int_carbon_dioxide[1] = {0};
//        memcpy(&int_carbon_dioxide,byte_carbon_dioxide,2);
//        APP_PRINT("Carbon Dioxide = %02d\n", int_carbon_dioxide[0])
//        vTaskDelay (1);
    }
}

/* Callback function */
void comms_i2c_callback(rm_comms_callback_args_t *p_args)
{
    if (NULL != p_args)
        {
            APP_PRINT("\n%p: %x\n", p_args, p_args->event);
            switch (p_args->event)
            {
                case I2C_MASTER_EVENT_ABORTED:
                    APP_PRINT("ERROR: I2C_MASTER_EVENT_ABORTED\n")
                    ;
                break;
                case I2C_MASTER_EVENT_RX_COMPLETE:
                    APP_PRINT("ERROR: I2C_MASTER_EVENT_RX_COMPLETE\n")
                    ;
                break;
                case I2C_MASTER_EVENT_TX_COMPLETE:
                    APP_PRINT("ERROR: I2C_MASTER_EVENT_TX_COMPLETE\n")
                    ;
                break;
                default:
                    APP_PRINT("No Matching Case.\n")
                    ;
                    APP_ERR_TRAP(p_args->event)
                    ;
                break;
            }
        }
}
