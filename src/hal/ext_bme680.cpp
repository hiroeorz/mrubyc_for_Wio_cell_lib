 /*
  ext_bmp280.cpp

  Defining extension methods of BMP280.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static void class_bme680_init(mrb_vm *vm, mrb_value *v, int argc)
{
  unsigned char iic_addr = 0x76; //default (selectable 0x76, 0x77)

  if (argc == 0) {
  } else if (argc == 1) {
    iic_addr = (unsigned char)GET_INT_ARG(1);
  } else {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  if (iic_addr != 0x76 && iic_addr != 0x77) {
    DEBUG_PRINTLN("invalid argc. BME680 IIC_ADDR = 0x76 or 0x77.");
    SET_NIL_RETURN();
  }

  int result = hal_init_bme680(iic_addr);
  if (result == 1) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
  
}

static void class_bme680_get_sensor_data_with_addr(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("Invalid argc");
    SET_NIL_RETURN();
    return;
  }

  unsigned char iic_addr = (unsigned char)GET_INT_ARG(1);
  Seeed_BME680* bme680 = (Seeed_BME680*)hal_get_bme680_obj(iic_addr);

  if (bme680->read_sensor_data()) {
    DEBUG_PRINTLN("Failed to read sensor data(bme280).");
    SET_NIL_RETURN();
    return;
  }

  float temp = bme680->sensor_result_value.temperature;
  float press = bme680->sensor_result_value.pressure;
  float humi = bme680->sensor_result_value.humidity;
  float gas = bme680->sensor_result_value.gas;

  mrbc_value array = mrbc_array_new(vm, 4);
  mrbc_value temp_value = mrb_float_value((mrbc_float)temp);
  mrbc_value humi_value = mrb_float_value((mrbc_float)humi);
  mrbc_value press_value = mrb_float_value((mrbc_float)press);
  mrbc_value gas_value = mrb_float_value((mrbc_float)gas);
  
  mrbc_array_set(&array, 0, &temp_value);
  mrbc_array_set(&array, 1, &humi_value);
  mrbc_array_set(&array, 2, &press_value);
  mrbc_array_set(&array, 3, &gas_value);

  mrbc_release(&temp_value);
  mrbc_release(&humi_value);
  mrbc_release(&press_value);
  mrbc_release(&gas_value);

  SET_RETURN(array);
}

void define_bme680_class()
{
  mrb_class *class_bme680;
  class_bme680 = mrbc_define_class(0, "BME680", mrbc_class_object);

  mrbc_define_method(0, class_bme680, "init", class_bme680_init);
  mrbc_define_method(0, class_bme680, "get_sensor_data_with_addr", class_bme680_get_sensor_data_with_addr);
}

