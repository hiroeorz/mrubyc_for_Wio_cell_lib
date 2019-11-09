/*
  ext_sht35.cpp

  Defining extension methods of SHT35.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static SHT35* sht35 = NULL;

static void class_sht35_init(mrb_vm *vm, mrb_value *v, int argc)
{
  hal_init_sht35();
  sht35 = (SHT35*)hal_get_sht35_obj();
}


static void class_sht35_get_temperature(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float temp;
  float hum;

  if (NO_ERROR != sht35->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp, &hum)) {
    SET_NIL_RETURN();
  } else {
    SET_FLOAT_RETURN(temp);
  }
}

static void class_sht35_get_humidity(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float temp;
  float hum;

  if (NO_ERROR != sht35->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp, &hum)) {
    SET_NIL_RETURN();
  } else {
    SET_FLOAT_RETURN(hum);
  }
}

static void class_sht35_get_temp_and_humi(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float temp;
  float hum;
  mrbc_value obj = mrbc_hash_new(vm, 2);

  if (NO_ERROR != sht35->read_meas_data_single_shot(HIGH_REP_WITH_STRCH, &temp, &hum)) {
    SET_NIL_RETURN();
  } else {
    mrbc_value array = mrbc_array_new(vm, 2);
    mrbc_value temp_value = mrb_float_value((mrbc_float)temp);
    mrbc_value hum_value = mrb_float_value((mrbc_float)hum);
    mrbc_array_set(&array, 0, &temp_value);
    mrbc_array_set(&array, 1, &hum_value);
    SET_RETURN(array);
  }
}


void define_sht35_class()
{
  mrb_class *class_sht35;
  class_sht35 = mrbc_define_class(0, "SHT35", mrbc_class_object);
  mrbc_define_method(0, class_sht35, "initialize", class_sht35_init);
  mrbc_define_method(0, class_sht35, "get_temperature", class_sht35_get_temperature);
  mrbc_define_method(0, class_sht35, "get_humidity", class_sht35_get_humidity);
  mrbc_define_method(0, class_sht35, "get_temp_and_humi", class_sht35_get_temp_and_humi);
}

