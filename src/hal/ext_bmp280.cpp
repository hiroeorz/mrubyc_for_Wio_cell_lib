/*
  ext_bmp280.cpp

  Defining extension methods of BMP280.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static BMP280* bmp280 = NULL;

static void class_bmp280_init(mrb_vm *vm, mrb_value *v, int argc)
{
  hal_init_bmp280();
  bmp280 = (BMP280*)hal_get_bmp280_obj();
}


static void class_bmp280_is_enable(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  if (hal_bmp280_is_enable()) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_bmp280_get_temperature(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float temp = bmp280->getTemperature();
  SET_FLOAT_RETURN(temp);
}

static void class_bmp280_get_pressure(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float press = bmp280->getPressure();
  SET_FLOAT_RETURN(press);
}

static void class_bmp280_get_altitude(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  float press = bmp280->getPressure();
  float altitude = bmp280->calcAltitude(press);
  SET_FLOAT_RETURN(altitude);
}

void define_bmp280_class()
{
  mrb_class *class_bmp280;
  class_bmp280 = mrbc_define_class(0, "BMP280", mrbc_class_object);

  mrbc_define_method(0, class_bmp280, "init", class_bmp280_init);
  mrbc_define_method(0, class_bmp280, "enable?", class_bmp280_is_enable);
  mrbc_define_method(0, class_bmp280, "get_temperature", class_bmp280_get_temperature);
  mrbc_define_method(0, class_bmp280, "get_pressure", class_bmp280_get_pressure);
  mrbc_define_method(0, class_bmp280, "get_altitude", class_bmp280_get_altitude);
}

