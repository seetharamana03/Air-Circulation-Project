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
float g_tvoc = 0.0f;
float g_eCO2 = 0.0f;
float g_iaq = 0.0f;
float g_NC03 = 0.0f;
float g_NC05 = 0.0f;
float g_NC1 = 0.0f;
float g_NC25 = 0.0f;
float g_NC4 = 0.0f;
float g_PM1_1 = 0.0f;
float g_PM25_1 = 0.0f;
float g_PM10_1 = 0.0f;
float g_PM1_2 = 0.0f;
float g_PM25_2 = 0.0f;
float g_PM10_2 = 0.0f;

float g_dust_concentration = 0.0f;
float g_dust_accumulation = 0.0f;
float g_fan_speed = 0.0f;
float g_fan_status = 0.0f;

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

    rm_comms_i2c_bus_extended_cfg_t *p_extend = (rm_comms_i2c_bus_extended_cfg_t*) g_comms_i2c_device0_cfg.p_extend;
    i2c_master_instance_t *p_driver_instance = (i2c_master_instance_t*) p_extend->p_driver_instance;
    p_driver_instance->p_api->open (p_driver_instance->p_ctrl, p_driver_instance->p_cfg);

    if (p_extend->p_blocking_semaphore != NULL)
    {
        *(p_extend->p_blocking_semaphore->p_semaphore_handle) = xSemaphoreCreateCountingStatic(
                (UBaseType_t ) 1, (UBaseType_t ) 0, p_extend->p_blocking_semaphore->p_semaphore_memory);
    }

    if (p_extend->p_bus_recursive_mutex != NULL)
    {
        *(p_extend->p_bus_recursive_mutex->p_mutex_handle) = xSemaphoreCreateRecursiveMutexStatic(
                p_extend->p_bus_recursive_mutex->p_mutex_memory);
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
    float temp_compare = 0;
    int duty_cycle = 0;
    float humid_compare = 0;

    while (1)
    {
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

        uint8_t byte_status = sensor_data[0];
        int16_t dust_concentration = ((byte_status >> 0) & 1);
        int16_t dust_accumulation = ((byte_status >> 1) & 1);
        int16_t fan_speed = ((byte_status >> 2) & 1);
        int16_t fan_status = ((byte_status >> 3) & 1);

        uint8_t byte_temperature[2] =
        { sensor_data[25], sensor_data[24] };
        uint8_t byte_humidity[2] =
        { sensor_data[27], sensor_data[26] };
        uint8_t byte_tvoc[2] =
        { sensor_data[29], sensor_data[28] };
        uint8_t byte_eCO2[2] =
        { sensor_data[31], sensor_data[30] };
        uint8_t byte_iaq[2] =
        { sensor_data[33], sensor_data[32] };
        uint8_t byte_NC03[2] =
        { sensor_data[3], sensor_data[2] };
        uint8_t byte_NC05[2] =
        { sensor_data[5], sensor_data[4] };
        uint8_t byte_NC1[2] =
        { sensor_data[7], sensor_data[6] };
        uint8_t byte_NC25[2] =
        { sensor_data[9], sensor_data[8] };
        uint8_t byte_NC4[2] =
        { sensor_data[11], sensor_data[10] };
        uint8_t byte_PM1_1[2] =
        { sensor_data[13], sensor_data[12] };
        uint8_t byte_PM25_1[2] =
        { sensor_data[15], sensor_data[14] };
        uint8_t byte_PM10_1[2] =
        { sensor_data[17], sensor_data[16] };
        uint8_t byte_PM1_2[2] =
        { sensor_data[19], sensor_data[18] };
        uint8_t byte_PM25_2[2] =
        { sensor_data[21], sensor_data[20] };
        uint8_t byte_PM10_2[2] =
        { sensor_data[23], sensor_data[22] };
        int16_t int_temperature[1] =
        { 0 };
        int16_t int_humidity[1] =
        { 0 };
        int16_t int_tvoc[1] =
        { 0 };
        int16_t int_eCO2[1] =
        { 0 };
        int16_t int_iaq[1] =
        { 0 };
        int16_t int_NC03[1] =
        { 0 };
        int16_t int_NC05[1] =
        { 0 };
        int16_t int_NC1[1] =
        { 0 };
        int16_t int_NC25[1] =
        { 0 };
        int16_t int_NC4[1] =
        { 0 };
        int16_t int_PM1_1[1] =
        { 0 };
        int16_t int_PM25_1[1] =
        { 0 };
        int16_t int_PM10_1[1] =
        { 0 };
        int16_t int_PM1_2[1] =
        { 0 };
        int16_t int_PM25_2[1] =
        { 0 };
        int16_t int_PM10_2[1] =
        { 0 };
        memcpy (&int_temperature, byte_temperature, 2);
        memcpy (&int_humidity, byte_humidity, 2);
        memcpy (&int_tvoc, byte_tvoc, 2);
        memcpy (&int_eCO2, byte_eCO2, 2);
        memcpy (&int_iaq, byte_iaq, 2);
        memcpy (&int_NC03, byte_NC03, 2);
        memcpy (&int_NC05, byte_NC05, 2);
        memcpy (&int_NC1, byte_NC1, 2);
        memcpy (&int_NC25, byte_NC25, 2);
        memcpy (&int_NC4, byte_NC4, 2);
        memcpy (&int_PM1_1, byte_PM1_1, 2);
        memcpy (&int_PM25_1, byte_PM25_1, 2);
        memcpy (&int_PM10_1, byte_PM10_1, 2);
        memcpy (&int_PM1_2, byte_PM1_2, 2);
        memcpy (&int_PM25_2, byte_PM25_2, 2);
        memcpy (&int_PM10_2, byte_PM10_2, 2);

        int16_t data[20] =
        { int_temperature[0],
          int_humidity[0],
          int_tvoc[0],
          int_eCO2[0],
          int_iaq[0],
          int_NC03[0],
          int_NC05[0],
          int_NC1[0],
          int_NC25[0],
          int_NC4[0],
          int_PM1_1[0],
          int_PM25_1[0],
          int_PM10_1[0],
          int_PM1_2[0],
          int_PM25_2[0],
          int_PM10_2[0],
          dust_concentration,
          dust_accumulation,
          fan_speed,
          fan_status };

        xQueueSend(g_sensor_queue, (uint32_t* )data, 0);
        xEventGroupSetBits (g_ble_event_group_handle, BLE_EVENT_PATTERN);
        g_temp = (float) int_temperature[0];
        g_humid = (float) int_humidity[0];
        g_tvoc = (float) int_tvoc[0];
        g_eCO2 = (float) int_eCO2[0];
        g_iaq = (float) int_iaq[0];
        g_NC03 = (float) int_NC03[0];
        g_NC05 = (float) int_NC05[0];
        g_NC1 = (float) int_NC1[0];
        g_NC25 = (float) int_NC25[0];
        g_NC4 = (float) int_NC4[0];
        g_PM1_1 = (float) int_PM1_1[0];
        g_PM25_1 = (float) int_PM25_1[0];
        g_PM10_1 = (float) int_PM10_1[0];
        g_PM1_2 = (float) int_PM1_2[0];
        g_PM25_2 = (float) int_PM25_2[0];
        g_PM10_2 = (float) int_PM10_2[0];
        g_dust_accumulation = (float) dust_accumulation;
        g_dust_concentration = (float) dust_concentration;
        g_fan_speed = (float) fan_speed;
        g_fan_status = (float) fan_status;

        int8_t data_pwm[1] =
        { 0 };
        int8_t set_temperature[1] =
        { 0 };
        int8_t set_humidity[1] =
        { 0 };

        if (pdTRUE == xQueueReceive (g_pwm_queue, &data_pwm[0], 0))
        {
            APP_PRINT("PWM Data Successfully Received \r\n");
            duty_cycle = data_pwm[0];
            if (duty_cycle > 0)
            {
                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_04_PIN_15, BSP_IO_LEVEL_HIGH);
            }
            else
            {
                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_04_PIN_15, BSP_IO_LEVEL_LOW);
            }
        }

        if (pdTRUE == xQueueReceive (g_temp_queue, &set_temperature[0], 0))
        {
            APP_PRINT("Temperature Data Successfully Received \r\n");
            temp_compare = set_temperature[0] * 100;
        }

        if (pdTRUE == xQueueReceive (g_humid_queue, &set_humidity[0], 0)){
            APP_PRINT("Humidity Data Successfully Received \r\n");
            humid_compare = set_humidity[0] * 100;
        }

            if (temp_compare < g_temp && humid_compare < g_humid)
            {
                APP_PRINT("Set Temperature Less \r\n");
                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_HIGH);
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
                duty_cycle_counts = (uint32_t) ((uint64_t) (current_period_counts * duty_cycle) / 100);
                err = R_GPT_DutyCycleSet (&g_timer0_ctrl, duty_cycle_counts, GPT_IO_PIN_GTIOCB);
                if (FSP_SUCCESS != err)
                {
                    err = R_GPT_Close (&g_timer0_ctrl);
                    APP_ERR_PRINT("\r\n ** R_GPT_DutyCycleSet API failed ** \r\n");
                }
            }
            else
            {
                APP_PRINT("Set Temperature is Greater \r\n");
                err = R_GPT_DutyCycleSet (&g_timer0_ctrl, 0, GPT_IO_PIN_GTIOCB);
                if (FSP_SUCCESS != err)
                {
                    err = R_GPT_Close (&g_timer0_ctrl);
                    APP_ERR_PRINT("\r\n ** R_GPT_DutyCycleSet API failed ** \r\n");
                }
                R_IOPORT_PinWrite (&g_ioport_ctrl, BSP_IO_PORT_04_PIN_00, BSP_IO_LEVEL_LOW);
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
        { alive_time_msb, alive_time_lsb };
        memcpy (&alive_time2, alive_time_byte, 2);

        xQueueSend(g_rtc_queue, (uint32_t* )alive_time2, 0);
        xEventGroupSetBits (g_ble_event_group_handle, BLE_EVENT_PATTERN);

        vTaskDelay (100);
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
            case RM_COMMS_EVENT_ERROR:
                APP_PRINT("RM_COMMS_EVENT_ERROR\n")
                ;
            break;
            case RM_COMMS_EVENT_RX_OPERATION_COMPLETE:
                APP_PRINT("RM_COMMS_EVENT_RX_OPERATION_COMPLETE\n")
                ;
            break;
            case RM_COMMS_EVENT_TX_OPERATION_COMPLETE:
                APP_PRINT("RM_COMMS_EVENT_TX_OPERATION_COMPLETE\n")
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
