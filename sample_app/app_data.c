/*********************************************************************
 *        _       _         _
 *  _ __ | |_  _ | |  __ _ | |__   ___
 * | '__|| __|(_)| | / _` || '_ \ / __|
 * | |   | |_  _ | || (_| || |_) |\__ \
 * |_|    \__|(_)|_| \__,_||_.__/ |___/
 *
 * www.rt-labs.com
 * Copyright 2021 rt-labs AB, Sweden.
 *
 * This software is dual-licensed under GPLv3 and a commercial
 * license. See the file LICENSE.md distributed with this software for
 * full license information.
 ********************************************************************/

#include "app_data.h"
#include "app_utils.h"
#include "app_gsdml.h"
#include "app_log.h"
#include "sampleapp_common.h"
#include "osal.h"
#include "pnal.h"
#include <pnet_api.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define APP_DATA_DEFAULT_OUTPUT_DATA 0

/* Parameters data
 * Todo: Data is always in pnio data format. Add conversion to uint32_t.
 */
// uint32_t app_param_1 = 0;
// uint32_t app_param_2 = 0;

/* Process data */
uint8_t inputdata_n[APP_GSDML_INPUT_DATA_SIZE_N] = {0};
uint8_t outputdata_n[APP_GSDML_OUTPUT_DATA_SIZE_N] = {0};
/* Process data */
uint8_t inputdata_s[APP_GSDML_INPUT_DATA_SIZE_S] = {0};
uint8_t outputdata_s[APP_GSDML_OUTPUT_DATA_SIZE_S] = {0};

uint8_t counter = 0;

// /**
//  * Set LED state.
//  *
//  * Compares new state with previous state, to minimize system calls.
//  *
//  * Uses the hardware specific app_set_led() function.
//  *
//  * @param led_state        In:    New LED state
//  */
// static void app_handle_data_led_state (bool led_state)
// {
//    // static bool previous_led_state = false;

//    // if (led_state != previous_led_state)
//    // {
//    //    app_set_led (APP_DATA_LED_ID, led_state);
//    // }
//    // previous_led_state = led_state;
// }

uint8_t * app_data_get_input_data (
   uint32_t submodule_id,
   uint16_t * size,
   uint8_t * iops,
   uint8_t counter)
{
   // printf ("------ app_data_get_input_data ------\n");
   // printf ("submodule_id %u", submodule_id);
   // if (size == NULL || iops == NULL)
   // {
   //    return NULL;
   // }

   if (
      submodule_id != APP_GSDML_SUBMOD_ID_1_IN_OUT &&
      submodule_id != APP_GSDML_SUBMOD_ID_8_IN_OUT)
   {
      /* Automated RT Tester scenario 2 - unsupported (sub)module */
      *iops = PNET_IOXS_BAD;
      return NULL;
   }
   else if (submodule_id == APP_GSDML_SUBMOD_ID_1_IN_OUT)
   {
      *size = APP_GSDML_INPUT_DATA_SIZE_S;
      *iops = PNET_IOXS_GOOD;
      if ((counter % 10) > 5)
      {
         inputdata_s[0] |= 0x80;
      }
      else
      {
         inputdata_s[0] &= 0x7F;
      }
      return inputdata_s;
   }
   else if (submodule_id == APP_GSDML_SUBMOD_ID_8_IN_OUT)
   {
      *size = APP_GSDML_INPUT_DATA_SIZE_N;
      *iops = PNET_IOXS_GOOD;
      // printf ("Input n-data received!\n");
      // printf ("Count = %u!\n", counter);

      inputdata_n[0] = counter;

      return inputdata_n;
   }
   *iops = PNET_IOXS_GOOD;
   return inputdata_s;

   /* Prepare input data
    * Lowest 7 bits: Counter    Most significant bit: Button
    */
   // inputdata[0] = counter;
   // if (button_pressed)
   // {
   //    inputdata[0] |= 0x80;
   // }
   // else
   // {
   //    inputdata[0] &= 0x7F;
   // }
   // return NULL;
}

int app_data_set_output_data (
   uint32_t submodule_id,
   uint8_t * data,
   uint16_t size, 
   uint8_t counter)
{
   // printf ("------ app_data_set_output_data ------\n");
   // printf ("submodule_id %u\n", submodule_id);
   // printf ("size %u\n", size);
   // printf ("data %u\n", *data);
   if (data != NULL)
   {

      if (
         submodule_id == APP_GSDML_SUBMOD_ID_1_IN_OUT &&
         size == APP_GSDML_OUTPUT_DATA_SIZE_S)
      {
         memcpy (outputdata_s, data, size);
         // led_state = (outputdata_s[0] & 0x80) > 0;
         // printf ("safe processed\n");
         // app_handle_data_led_state (false);
         return 0;
      }
      else if (
         submodule_id == APP_GSDML_SUBMOD_ID_8_IN_OUT &&
         size == APP_GSDML_OUTPUT_DATA_SIZE_N)
      {
         memcpy (outputdata_n, data, size);
         // led_state = (outputdata_n[0] & 0x80) > 0;
         printf("old counter = %u\n", counter);
         printf ("\nnew counter = %u\n", outputdata_n[0]);
         // app_handle_data_led_state (false);
         return 0;
      }
   }
   return -1;
}

int app_data_set_default_outputs (void)
{
   outputdata_s[0] = APP_DATA_DEFAULT_OUTPUT_DATA;
   outputdata_n[0] = APP_DATA_DEFAULT_OUTPUT_DATA;

   // app_handle_data_led_state (false);
   return 0;
}

// int app_data_write_parameter (
//    uint32_t submodule_id,
//    uint32_t index,
//    const uint8_t * data,
//    uint16_t length)
// {
//    const app_gsdml_param_t * par_cfg;

//    par_cfg = app_gsdml_get_parameter_cfg (submodule_id, index);
//    if (par_cfg == NULL)
//    {
//       APP_LOG_WARNING (
//          "PLC write request unsupported submodule/parameter. "
//          "Submodule id: %u Index: %u\n",
//          (unsigned)submodule_id,
//          (unsigned)index);
//       return -1;
//    }

//    if (length != par_cfg->length)
//    {
//       APP_LOG_WARNING (
//          "PLC write request unsupported length. "
//          "Index: %u Length: %u Expected length: %u\n",
//          (unsigned)index,
//          (unsigned)length,
//          par_cfg->length);
//       return -1;
//    }

//    if (index == APP_GSDM_PARAMETER_1_IDX)
//    {
//       memcpy (&app_param_1, data, sizeof (length));
//    }
//    else if (index == APP_GSDM_PARAMETER_2_IDX)
//    {
//       memcpy (&app_param_2, data, sizeof (length));
//    }
//    APP_LOG_DEBUG ("  Writing %s\n", par_cfg->name);
//    app_log_print_bytes (APP_LOG_LEVEL_DEBUG, data, length);

//    return 0;
// }

// int app_data_read_parameter (
//    uint32_t submodule_id,
//    uint32_t index,
//    uint8_t ** data,
//    uint16_t * length)
// {
//    const app_gsdml_param_t * par_cfg;

//    par_cfg = app_gsdml_get_parameter_cfg (submodule_id, index);
//    if (par_cfg == NULL)
//    {
//       APP_LOG_WARNING (
//          "PLC read request unsupported submodule/parameter. "
//          "Submodule id: %u Index: %u\n",
//          (unsigned)submodule_id,
//          (unsigned)index);
//       return -1;
//    }

//    if (*length < par_cfg->length)
//    {
//       APP_LOG_WARNING (
//          "PLC read request unsupported length. "
//          "Index: %u Length: %u Expected length: %u\n",
//          (unsigned)index,
//          (unsigned)*length,
//          par_cfg->length);
//       return -1;
//    }

//    APP_LOG_DEBUG ("  Reading %s\n", par_cfg->name);
//    if (index == APP_GSDM_PARAMETER_1_IDX)
//    {
//       *data = (uint8_t *)&app_param_1;
//       *length = sizeof (app_param_1);
//    }
//    else if (index == APP_GSDM_PARAMETER_2_IDX)
//    {
//       *data = (uint8_t *)&app_param_2;
//       *length = sizeof (app_param_2);
//    }

//    app_log_print_bytes (APP_LOG_LEVEL_DEBUG, *data, *length);

//    return 0;
// }
