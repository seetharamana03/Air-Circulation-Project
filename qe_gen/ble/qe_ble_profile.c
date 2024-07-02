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
* https://www.renesas.com/disclaimer
*
* Copyright (C) 2021 Renesas Electronics Corporation.
***********************************************************************************************************************/
/***********************************************************************************************************************
* File Name    : qe_ble_profile.c
* Description  : This file includes definitions.
***********************************************************************************************************************/
/***********************************************************************************************************************
* History      : MM/DD/YYYY Version Description
*              : 08/31/2021 1.00    First Release
***********************************************************************************************************************/

#include "qe_ble_profile.h"

static uint16_t qe_uuid1 = 0x2800;
static uint16_t qe_value1 = 0x1800;
static uint16_t qe_uuid2 = 0x2803;
static uint16_t qe_uuid3 = 0x2A00;
static uint16_t qe_uuid4 = 0x2803;
static uint16_t qe_uuid5 = 0x2A01;
static uint16_t qe_uuid6 = 0x2803;
static uint16_t qe_uuid7 = 0x2A04;
static uint16_t qe_uuid8 = 0x2803;
static uint16_t qe_uuid9 = 0x2AA6;
static uint16_t qe_uuid10 = 0x2803;
static uint16_t qe_uuid11 = 0x2AC9;
static uint16_t qe_uuid12 = 0x2800;
static uint16_t qe_value12 = 0x1801;
static uint16_t qe_uuid13 = 0x2803;
static uint16_t qe_uuid14 = 0x2A05;
static uint16_t qe_uuid15 = 0x2902;
static uint16_t qe_uuid16 = 0x2800;
static uint16_t qe_value16[] = {0x8B4B,0xD16B,0x3A61,0xAA23,0x4BC5,0x39EC,0x2EEC,0x83B8};
static uint16_t qe_uuid17 = 0x2803;
static uint16_t qe_uuid19 = 0x2901;
static uint16_t qe_uuid20 = 0x2803;
static uint16_t qe_uuid22 = 0x2901;
static uint16_t qe_uuid23 = 0x2800;
static uint16_t qe_value23[] = {0x44C4,0xC611,0x61C6,0xB9B0,0x4880,0xC789,0x2851,0x0C49};
static uint16_t qe_uuid24 = 0x2803;
static uint16_t qe_uuid26 = 0x2800;
static uint16_t qe_value26[] = {0x76F6,0x3202,0x0671,0xB489,0x45FF,0x9FEF,0x0325,0xB6D9};
static uint16_t qe_uuid27 = 0x2803;
static uint16_t qe_uuid29 = 0x2901;

const attribute_t qe_ble_profile[QE_ATTRIBUTE_HANDLE_PROFILE_END] =
{

	// Profile Declaration
	[0] =
	{
		.handle = 0,
		.encapsulated_attributes = 29,
		.permissions = 0x00, 
		.uuid_length = 0x00,
		.value_length = 0x00,
		.notify_write = 0,
		.notify_read = 0
	},
	// Service Declaration: GAP Service
	[1] =
	{
		.handle = 1,
		.encapsulated_attributes = 11,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x02,
		.uuid = (uint8_t *)&qe_uuid1,
		.value = (uint8_t *)&qe_value1,
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Device Name
	[2] =
	{
		.handle = 2,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x05,
		.uuid = (uint8_t *)&qe_uuid2,
		.value = (uint8_t []){0x0A,0x03,0x00,0x00,0x2A},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Device Name
	[3] =
	{
		.handle = 3,
		.encapsulated_attributes = 0,
		.permissions = 0x03,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x80,
		.uuid = (uint8_t *)&qe_uuid3,
		.value = (uint8_t []){0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Appearance
	[4] =
	{
		.handle = 4,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x05,
		.uuid = (uint8_t *)&qe_uuid4,
		.value = (uint8_t []){0x02,0x05,0x00,0x01,0x2A},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Appearance
	[5] =
	{
		.handle = 5,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x02,
		.uuid = (uint8_t *)&qe_uuid5,
		.value = (uint8_t []){0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Peripheral Preferred Connection Parameters
	[6] =
	{
		.handle = 6,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x05,
		.uuid = (uint8_t *)&qe_uuid6,
		.value = (uint8_t []){0x02,0x07,0x00,0x04,0x2A},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Peripheral Preferred Connection Parameters
	[7] =
	{
		.handle = 7,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x08,
		.uuid = (uint8_t *)&qe_uuid7,
		.value = (uint8_t []){0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Central Address Resolution
	[8] =
	{
		.handle = 8,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x05,
		.uuid = (uint8_t *)&qe_uuid8,
		.value = (uint8_t []){0x02,0x09,0x00,0xA6,0x2A},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Central Address Resolution
	[9] =
	{
		.handle = 9,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x01,
		.uuid = (uint8_t *)&qe_uuid9,
		.value = (uint8_t []){0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Resolvable Private Address Only
	[10] =
	{
		.handle = 10,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x05,
		.uuid = (uint8_t *)&qe_uuid10,
		.value = (uint8_t []){0x02,0x0B,0x00,0xC9,0x2A},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Resolvable Private Address Only
	[11] =
	{
		.handle = 11,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x01,
		.uuid = (uint8_t *)&qe_uuid11,
		.value = (uint8_t []){0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Service Declaration: GATT Service
	[12] =
	{
		.handle = 12,
		.encapsulated_attributes = 4,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x02,
		.uuid = (uint8_t *)&qe_uuid12,
		.value = (uint8_t *)&qe_value12,
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Service Changed
	[13] =
	{
		.handle = 13,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x05,
		.uuid = (uint8_t *)&qe_uuid13,
		.value = (uint8_t []){0x20,0x0E,0x00,0x05,0x2A},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Service Changed
	[14] =
	{
		.handle = 14,
		.encapsulated_attributes = 0,
		.permissions = 0x00,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x04,
		.uuid = (uint8_t *)&qe_uuid14,
		.value = (uint8_t []){0x00,0x00,0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Descriptor: Client Characteristic Configuration
	[15] =
	{
		.handle = 15,
		.encapsulated_attributes = 0,
		.permissions = 0x03,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x02,
		.uuid = (uint8_t *)&qe_uuid15,
		.value = (uint8_t []){0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Service Declaration: Sensor
	[16] =
	{
		.handle = 16,
		.encapsulated_attributes = 7,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x10,
		.uuid = (uint8_t *)&qe_uuid16,
		.value = (uint8_t *)&qe_value16,
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Temperature
	[17] =
	{
		.handle = 17,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x13,
		.uuid = (uint8_t *)&qe_uuid17,
		.value = (uint8_t []){0x02,0x12,0x00,0x92,0x9F,0x4E,0xF0,0x9C,0x0A,0xB6,0xA3,0x5E,0x44,0x55,0xE1,0xB2,0x4A,0x6F,0x22},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Temperature
	[18] =
	{
		.handle = 18,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_CUSTOM,
		.value_length = 0x02,
		.uuid = (uint8_t []){0x92,0x9F,0x4E,0xF0,0x9C,0x0A,0xB6,0xA3,0x5E,0x44,0x55,0xE1,0xB2,0x4A,0x6F,0x22},
		.value = (uint8_t []){0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Descriptor: Characteristic User Description
	[19] =
	{
		.handle = 19,
		.encapsulated_attributes = 0,
		.permissions = 0x03,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x64,
		.uuid = (uint8_t *)&qe_uuid19,
		.value = (uint8_t []){0x54,0x65,0x6D,0x70,0x65,0x72,0x61,0x74,0x75,0x72,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Humidity
	[20] =
	{
		.handle = 20,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x13,
		.uuid = (uint8_t *)&qe_uuid20,
		.value = (uint8_t []){0x02,0x15,0x00,0xB0,0xF2,0x93,0x2A,0x5C,0x16,0xF1,0xA0,0x00,0x4E,0x34,0x06,0x41,0xEA,0x11,0x89},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Humidity
	[21] =
	{
		.handle = 21,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_CUSTOM,
		.value_length = 0x02,
		.uuid = (uint8_t []){0xB0,0xF2,0x93,0x2A,0x5C,0x16,0xF1,0xA0,0x00,0x4E,0x34,0x06,0x41,0xEA,0x11,0x89},
		.value = (uint8_t []){0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Descriptor: Characteristic User Description
	[22] =
	{
		.handle = 22,
		.encapsulated_attributes = 0,
		.permissions = 0x03,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x64,
		.uuid = (uint8_t *)&qe_uuid22,
		.value = (uint8_t []){0x48,0x75,0x6D,0x69,0x64,0x69,0x74,0x79,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Service Declaration: RA6M4 Temp Control
	[23] =
	{
		.handle = 23,
		.encapsulated_attributes = 3,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x10,
		.uuid = (uint8_t *)&qe_uuid23,
		.value = (uint8_t *)&qe_value23,
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Temp Control
	[24] =
	{
		.handle = 24,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x13,
		.uuid = (uint8_t *)&qe_uuid24,
		.value = (uint8_t []){0x0A,0x19,0x00,0xF1,0x15,0xFC,0x28,0x05,0x8B,0xFA,0xA4,0xB9,0x49,0x35,0x78,0x3B,0x6D,0x24,0xBE},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Temp Control
	[25] =
	{
		.handle = 25,
		.encapsulated_attributes = 0,
		.permissions = 0x03,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_CUSTOM,
		.value_length = 0x01,
		.uuid = (uint8_t []){0xF1,0x15,0xFC,0x28,0x05,0x8B,0xFA,0xA4,0xB9,0x49,0x35,0x78,0x3B,0x6D,0x24,0xBE},
		.value = (uint8_t []){0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Service Declaration: Real Time Clock
	[26] =
	{
		.handle = 26,
		.encapsulated_attributes = 4,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x10,
		.uuid = (uint8_t *)&qe_uuid26,
		.value = (uint8_t *)&qe_value26,
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Declaration: Alive Time
	[27] =
	{
		.handle = 27,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x13,
		.uuid = (uint8_t *)&qe_uuid27,
		.value = (uint8_t []){0x02,0x1C,0x00,0xF9,0xF9,0x45,0x9B,0xDF,0x4E,0xE6,0x9E,0xDA,0x46,0xDC,0xF0,0x18,0x6D,0x17,0x3C},
		.notify_write = 1,
		.notify_read = 1
	},
	// Characteristic Value: Alive Time
	[28] =
	{
		.handle = 28,
		.encapsulated_attributes = 0,
		.permissions = 0x01,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_CUSTOM,
		.value_length = 0x02,
		.uuid = (uint8_t []){0xF9,0xF9,0x45,0x9B,0xDF,0x4E,0xE6,0x9E,0xDA,0x46,0xDC,0xF0,0x18,0x6D,0x17,0x3C},
		.value = (uint8_t []){0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	},
	// Descriptor: Characteristic User Description
	[29] =
	{
		.handle = 29,
		.encapsulated_attributes = 0,
		.permissions = 0x03,
		.uuid_length = QE_BLE_PROFILE_UUID_SIZE_ADOPTED,
		.value_length = 0x64,
		.uuid = (uint8_t *)&qe_uuid29,
		.value = (uint8_t []){0x41,0x6C,0x69,0x76,0x65,0x20,0x54,0x69,0x6D,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
		.notify_write = 1,
		.notify_read = 1
	}

};
