/*
  ext_sht35.cpp

  Defining extension methods of SHT35.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

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


void define_sht35_class()
{
  static mrb_class *class_sht35;
  class_sht35 = mrbc_define_class(0, "SHT35", mrbc_class_object);
  mrbc_define_method(0, class_sht35, "init", class_sht35_init);
  mrbc_define_method(0, class_sht35, "get_temperature_with_addr", class_sht35_get_temperature_with_addr);
  mrbc_define_method(0, class_sht35, "get_humidity_with_addr", class_sht35_get_humidity_with_addr);
  mrbc_define_method(0, class_sht35, "get_temp_and_humi_with_addr", class_sht35_get_temp_and_humi_with_addr);
}

