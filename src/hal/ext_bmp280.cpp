/*
  ext_bmp280.cpp

  Defining extension methods of BMP280.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static void class_bmp280_init(mrb_vm *vm, mrb_value *v, int argc)
{
  unsigned char iic_addr = 0x77; //default (selectable 0x76, 0x77)

  if (argc == 0) {
  } else if (argc == 1) {
    iic_addr = (unsigned char)GET_INT_ARG(1);
  } else {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  if (iic_addr != 0x76 && iic_addr != 0x77) {
    DEBUG_PRINTLN("invalid argc. BMP280 IIC_ADDR = 0x76 or 0x77.");
    SET_NIL_RETURN();
  }

  hal_init_bmp280(iic_addr);
}


static void class_bmp280_is_enable_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);

  if (hal_bmp280_is_enable(iic_addr)) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_bmp280_get_temperature_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  BMP280* bmp280 = (BMP280*)hal_get_bmp280_obj(iic_addr);
  float temp = bmp280->getTemperature();
  SET_FLOAT_RETURN(temp);
}

static void class_bmp280_get_pressure_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  BMP280* bmp280 = (BMP280*)hal_get_bmp280_obj(iic_addr);
  float press = bmp280->getPressure();
  SET_FLOAT_RETURN(press);
}

static void class_bmp280_get_altitude_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  BMP280* bmp280 = (BMP280*)hal_get_bmp280_obj(iic_addr);
  float press = bmp280->getPressure();
  float altitude = bmp280->calcAltitude(press);
  SET_FLOAT_RETURN(altitude);
}

void define_bmp280_class()
{
  mrb_class *class_bmp280;
  class_bmp280 = mrbc_define_class(0, "BMP280", mrbc_class_object);

  mrbc_define_method(0, class_bmp280, "init", class_bmp280_init);
  mrbc_define_method(0, class_bmp280, "enable_with_addr", class_bmp280_is_enable_with_addr);
  mrbc_define_method(0, class_bmp280, "get_temperature_with_addr", class_bmp280_get_temperature_with_addr);
  mrbc_define_method(0, class_bmp280, "get_pressure_with_addr", class_bmp280_get_pressure_with_addr);
  mrbc_define_method(0, class_bmp280, "get_altitude_with_addr", class_bmp280_get_altitude_with_addr);
}

