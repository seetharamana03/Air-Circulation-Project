/* generated configuration header file - do not edit */
#ifndef RM_BLE_ABS_GTL_CFG_H_
#define RM_BLE_ABS_GTL_CFG_H_
#ifdef __cplusplus
extern "C" {
#endif

#define BLE_ABS_CFG_RF_CONNECTION_MAXIMUM           (1)
#define BLE_ABS_CFG_GATT_MTU_SIZE                   (247)
#define BLE_ABS_CFG_NUMBER_BONDING                  (1)
#define BLE_ABS_CFG_TIMER_NUMBER_OF_SLOT            (10)
#define BLE_ABS_CFG_PARAM_CHECKING_ENABLE           (BSP_CFG_PARAM_CHECKING_ENABLE)
#define BLE_CFG_RF_CONN_MAX                         (1)
#define BLE_ABS_CFG_TRANSMIT_POWER_INDEX            (34)

#if RA_NOT_DEFINED > 0
            #define RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_SPI
#else
#define RM_BLE_ABS_GTL_TRANSPORT_INTERFACE_UART
#endif

#ifdef __cplusplus
}
#endif
#endif /* RM_BLE_ABS_GTL_CFG_H_ */
