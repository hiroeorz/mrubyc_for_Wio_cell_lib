/*
  ext_sht31.cpp

  Defining extension methods of SHT31.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static SHT31* sht31 = NULL;

static void class_sht31_begin(mrb_vm *vm, mrb_value *v, int argc)
{
  hal_init_sht31();
  sht31 = (SHT31*)hal_get_sht31_obj();
}


static void class_sht31_get_temperature(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float temp = sht31->getTemperature();
  SET_FLOAT_RETURN(temp);
}

static void class_sht31_get_humidity(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float humidity = sht31->getHumidity();
  SET_FLOAT_RETURN(humidity);
}


void define_sht31_class()
{
  mrb_class *class_sht31;
  class_sht31 = mrbc_define_class(0, "SHT31", mrbc_class_object);
  mrbc_define_method(0, class_sht31, "begin", class_sht31_begin);
  mrbc_define_method(0, class_sht31, "get_temperature", class_sht31_get_temperature);
  mrbc_define_method(0, class_sht31, "get_humidity", class_sht31_get_humidity);
}

