/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2018 rt-labs AB, Sweden.
 *
 * This software is dual-licensed under GPLv3 and a commercial
 * license. See the file LICENSE.md distributed with this software for
 * full license information.
 ********************************************************************/

#ifndef APP_GSDML_H
#define APP_GSDML_H

/**
 * @file
 * @brief Device properties defined by the GSDML device definition
 *
 * Functions for getting module, submodule and parameter
 * configurations using their ids.
 *
 * Important:
 * Any change in this file may require an update of the GSDML file.
 * Note that when the GSDML file is updated it has to be reloaded
 * in your Profinet engineering tool. PLC applications may be affected.
 *
 * Design requires unique submodule ids.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <pnet_api.h>

#define APP_GSDML_API 0

#define APP_GSDML_DEFAULT_STATION_NAME "krc4"

/* GSDML tag: VendorID */
#define APP_GSDML_VENDOR_ID 0x019B

/* GSDML tag: DeviceID */
#define APP_GSDML_DEVICE_ID 0x0300

/* Allowed: 'V', 'R', 'P', 'U', 'T' */
#define APP_GSDML_SW_REV_PREFIX     'V'
#define APP_GSDML_PROFILE_ID        0x1234
#define APP_GSDML_PROFILE_SPEC_TYPE 0x5678

/* GSDML tag: Writeable_IM_Records */
#define APP_GSDML_IM_SUPPORTED                                                 \
   (PNET_SUPPORTED_IM1 | PNET_SUPPORTED_IM2 | PNET_SUPPORTED_IM3)

/* GSDML tag: OrderNumber */
#define APP_GSDML_ORDER_ID "0x300"
/* GSDML tag: ModuleInfo / Name */
#define APP_GSDML_PRODUCT_NAME "KRC4_ProfiNet_4_1"

/* GSDML tag: MinDeviceInterval */
#define APP_GSDML_MIN_DEVICE_INTERVAL 32 /* 1ms */

#define APP_GSDML_DIAG_CUSTOM_USI 0x1234

/* See "Specification for GSDML" 8.26 LogBookEntryItem for allowed values */
#define APP_GSDML_LOGBOOK_ERROR_CODE   0x20 /* Manufacturer specific */
#define APP_GSDML_LOGBOOK_ERROR_DECODE 0x82 /* Manufacturer specific */
#define APP_GSDML_LOGBOOK_ERROR_CODE_1 PNET_ERROR_CODE_1_FSPM
#define APP_GSDML_LOGBOOK_ERROR_CODE_2 0x00       /* Manufacturer specific */
#define APP_GSDML_LOGBOOK_ENTRY_DETAIL 0xFEE1DEAD /* Manufacturer specific */

#define APP_GSDM_PARAMETER_1_IDX  123
#define APP_GSDM_PARAMETER_2_IDX  124
#define APP_GSDM_PARAMETER_LENGTH 4

typedef struct cfg_module
{
   uint32_t id;
   const char * name;
   uint32_t submodules[]; /* Variable length, ends with 0*/
} app_gsdml_module_t;

typedef struct app_gsdml_submodule
{
   uint32_t id;
   const char * name;
   uint32_t api;
   pnet_submodule_dir_t data_dir;
   uint16_t insize;
   uint16_t outsize;
   uint16_t parameters[]; /* Variable length, ends with 0 */
} app_gsdml_submodule_t;

typedef struct
{
   uint32_t index;
   const char * name;
   uint16_t length;
} app_gsdml_param_t;

// #define APP_GSDML_MOD_ID_8_0_DIGITAL_IN     0x00000030
// #define APP_GSDML_MOD_ID_0_8_DIGITAL_OUT    0x00000031
// #define APP_GSDML_MOD_ID_8_8_DIGITAL_IN_OUT 0x00000032
// #define APP_GSDML_SUBMOD_ID_DIGITAL_IN      0x00000130
// #define APP_GSDML_SUBMOD_ID_DIGITAL_OUT     0x00000131
// #define APP_GSDML_SUBMOD_ID_DIGITAL_IN_OUT  0x00000132

#define APP_GSDML_MOD_ID_1_IN_OUT           0x0000008F
#define APP_GSDML_MOD_ID_2_IN_OUT           0x00000080
#define APP_GSDML_MOD_ID_3_IN_OUT           0x00000100
#define APP_GSDML_MOD_ID_4_IN_OUT           0x00000200
#define APP_GSDML_MOD_ID_5_IN_OUT           0x00000400
#define APP_GSDML_MOD_ID_6_IN_OUT           0x00000800
#define APP_GSDML_MOD_ID_7_IN_OUT           0x00000C00
#define APP_GSDML_MOD_ID_8_IN_OUT           0x00001000
#define APP_GSDML_MOD_ID_9_IN_OUT           0x00001400
#define APP_GSDML_MOD_ID_10_IN_OUT          0x00001800
#define APP_GSDML_MOD_ID_11_IN_OUT          0x00001C00
#define APP_GSDML_MOD_ID_12_IN_OUT          0x00002000
#define APP_GSDML_MOD_ID_13_IN_OUT          0x00003000
#define APP_GSDML_MOD_ID_14_IN_OUT          0x00004000
#define APP_GSDML_MOD_ID_15_IN_OUT          0x00006000
#define APP_GSDML_MOD_ID_16_IN_OUT          0x00007F00

#define APP_GSDML_SUBMOD_ID_1_IN_OUT           0x0000008F
#define APP_GSDML_SUBMOD_ID_2_IN_OUT           0x00010080
#define APP_GSDML_SUBMOD_ID_3_IN_OUT           0x00010100
#define APP_GSDML_SUBMOD_ID_4_IN_OUT           0x00010200
#define APP_GSDML_SUBMOD_ID_5_IN_OUT           0x00010400
#define APP_GSDML_SUBMOD_ID_6_IN_OUT           0x00010800
#define APP_GSDML_SUBMOD_ID_7_IN_OUT           0x00010C00
#define APP_GSDML_SUBMOD_ID_8_IN_OUT           0x00001000
#define APP_GSDML_SUBMOD_ID_9_IN_OUT           0x00011400
#define APP_GSDML_SUBMOD_ID_10_IN_OUT          0x00011800
#define APP_GSDML_SUBMOD_ID_11_IN_OUT          0x00011C00
#define APP_GSDML_SUBMOD_ID_12_IN_OUT          0x00012000
#define APP_GSDML_SUBMOD_ID_13_IN_OUT          0x00013000
#define APP_GSDML_SUBMOD_ID_14_IN_OUT          0x00014000
#define APP_GSDML_SUBMOD_ID_15_IN_OUT          0x00016000
#define APP_GSDML_SUBMOD_ID_16_IN_OUT          0x00017F00

#define APP_GSDML_INPUT_DATA_SIZE_N   32 /* bytes, for digital inputs data */
#define APP_GSDML_OUTPUT_DATA_SIZE_N  32 /* bytes, for digital outputs data */
#define APP_GSDM_ALARM_PAYLOAD_SIZE_N 1 /* bytes */

#define APP_GSDML_INPUT_DATA_SIZE_S   12 /* bytes, for digital inputs data */
#define APP_GSDML_OUTPUT_DATA_SIZE_S  12 /* bytes, for digital outputs data */
#define APP_GSDM_ALARM_PAYLOAD_SIZE_S 1 /* bytes */

/**
 * Get module configuration from module id
 * @param module_id  In: Module id
 * @return Module configuration, NULL if not found
 */
const app_gsdml_module_t * app_gsdml_get_module_cfg (uint32_t module_id);

/**
 * Get submodule module configuration from submodule id
 * @param submodule_id  In: Submodule id
 * @return Submodule configuration, NULL if not found
 */
const app_gsdml_submodule_t * app_gsdml_get_submodule_cfg (
   uint32_t submodule_id);

/**
 * Get parameter configuration from parameter index
 * @param submodule_id  In: Submodule id
 * @param index         In: Parameters index
 * @return Parameter configuration, NULL if not found
 */
const app_gsdml_param_t * app_gsdml_get_parameter_cfg (
   uint32_t submodule_id,
   uint32_t index);

#ifdef __cplusplus
}
#endif

#endif /* APP_GSDML_H */
