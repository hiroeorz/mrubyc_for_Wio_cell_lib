/*
  ext_sht35.cpp

  Defining extension methods of SHT35.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "Wire.h"
#include "libmrubyc.h"
#include "ext.h"

static void class_sht35_init(mrb_vm *vm, mrb_value *v, int argc)
{
  unsigned char iic_addr = 0x45; //default (selectable 0x44, 0x45)

  if (argc == 0) {
  } else if (argc == 1) {
    iic_addr = (unsigned char)GET_INT_ARG(1);
  } else {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  if (iic_addr != 0x44 && iic_addr != 0x45) {
    DEBUG_PRINTLN("invalid argc. SHT35 IIC_ADDR = 0x44 or 0x45.");
    SET_NIL_RETURN();
  }

  int ret = hal_init_sht35(iic_addr);

  if (NO_ERROR == ret) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}


static void class_sht35_get_temperature_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  float temp;
  float hum;

  if (NO_ERROR != sht35->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp, &hum)) {
    SET_NIL_RETURN();
  } else {
    SET_FLOAT_RETURN(temp);
  }
}

static void class_sht35_get_humidity_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  float temp;
  float hum;

  if (NO_ERROR != sht35->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp, &hum)) {
    SET_NIL_RETURN();
  } else {
    SET_FLOAT_RETURN(hum);
  }
}

static void class_sht35_get_temp_and_humi_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  float temp;
  float hum;

  DEBUG_PRINT("SHT35 Getting Data...");
 
  if (NO_ERROR != sht35->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp, &hum)) {
    DEBUG_PRINT("!!! SHT35 Data Get Error.\n");
    SET_NIL_RETURN();
  } else {
    DEBUG_PRINT("SHT35 Data Get OK.\n");
    mrbc_value array = mrbc_array_new(vm, 2);
    mrbc_value temp_value = mrb_float_value((mrbc_float)temp);
    mrbc_value hum_value = mrb_float_value((mrbc_float)hum);
    mrbc_array_set(&array, 0, &temp_value);
    mrbc_array_set(&array, 1, &hum_value);
    mrbc_release(&temp_value);
    mrbc_release(&hum_value);
    SET_RETURN(array);
  }
}

#define HEATER_STATUS_ON  (0x01)
#define HEATER_STATUS_OFF (0x00)


static void class_sht35_heater_status_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  u16 value;

  if (NO_ERROR != sht35->heaterStatus(&value)) {
    DEBUG_PRINTLN("SHT35: Cannnot get HeaterStatus");
    SET_NIL_RETURN();
  } else {
    if (HEATER_STATUS_ON == value || HEATER_STATUS_OFF == value) {
      SET_INT_RETURN(value);
    } else {
      char str[128];
      sprintf(str, "SHT35: Invalid HeaterStatus: %02X", value);
      DEBUG_PRINTLN(str);
      SET_NIL_RETURN();
    }
  }
}

#define RESET_CHECK_ON  (0x01)
#define RESET_CHECK_OFF (0x00)

static void class_sht35_reset_check_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  u16 value;

  if (NO_ERROR != sht35->reset_check(&value)) {
    DEBUG_PRINTLN("SHT35: Cannnot get ResetCheck");
    SET_NIL_RETURN();
  } else {
    if (RESET_CHECK_ON == value || RESET_CHECK_OFF == value) {
      SET_INT_RETURN(value);
    } else {
      char str[128];
      sprintf(str, "SHT35: Invalid ResetCheck: %02X", value);
      DEBUG_PRINTLN(str);
      SET_NIL_RETURN();
    }
  }
}

static void class_sht35_soft_reset_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);

  if (NO_ERROR != sht35->soft_reset()) {
    DEBUG_PRINTLN("SHT35: soft reset error");
    SET_FALSE_RETURN();
  } else {
    SET_TRUE_RETURN();
  }
}

static void class_sht35_change_heater_status_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 2) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  int status = GET_INT_ARG(2);

  if (NO_ERROR != sht35->change_heater_status(status)) {
    DEBUG_PRINTLN("SHT35: change heater status error");
    SET_FALSE_RETURN();
  } else {
    SET_TRUE_RETURN();
  }
}

static void class_sht35_read_reg_status_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  SHT35* sht35 = (SHT35*)hal_get_sht35_obj(iic_addr);
  u16 value;

  if (NO_ERROR != sht35->read_reg_status(&value)) {
    DEBUG_PRINTLN("SHT35: Cannnot get RegStatus");
    SET_NIL_RETURN();
  } else {
    SET_INT_RETURN(value);
  }
}

void define_sht35_class()
{
  static mrb_class *class_sht35;
  class_sht35 = mrbc_define_class(0, "SHT35", mrbc_class_object);
  mrbc_define_method(0, class_sht35, "init", class_sht35_init);
  mrbc_define_method(0, class_sht35, "get_temperature_with_addr", class_sht35_get_temperature_with_addr);
  mrbc_define_method(0, class_sht35, "get_humidity_with_addr", class_sht35_get_humidity_with_addr);
  mrbc_define_method(0, class_sht35, "get_temp_and_humi_with_addr", class_sht35_get_temp_and_humi_with_addr);
  mrbc_define_method(0, class_sht35, "heater_status_with_addr", class_sht35_heater_status_with_addr);
  mrbc_define_method(0, class_sht35, "reset_check_with_addr", class_sht35_reset_check_with_addr);
  mrbc_define_method(0, class_sht35, "soft_reset_with_addr", class_sht35_soft_reset_with_addr);
  mrbc_define_method(0, class_sht35, "change_heater_status_with_addr", class_sht35_change_heater_status_with_addr);
  mrbc_define_method(0, class_sht35, "read_reg_status_with_addr", class_sht35_read_reg_status_with_addr);
}

