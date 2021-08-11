/*
  ext_sht31.cpp

  Defining extension methods of SHT31.

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

#define AQS_ADDRESS   0x32
#define AQS_DATA_LEN  16
#define AQS_ID        0x43

static void class_air_quality_init(mrb_vm *vm, mrb_value *v, int argc)
{
  hal_init_air_quality();
}


static void class_air_quality_get_data(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  uint8_t rdata[AQS_DATA_LEN];
  uint8_t i;

  Wire.requestFrom(AQS_ADDRESS, AQS_DATA_LEN);
  for(i = 0; i < AQS_DATA_LEN; i++) {
    rdata[i] = Wire.read();
  }
  Wire.endTransmission();


  if (rdata[0] != AQS_ID) {
    SET_NIL_RETURN();
    return;
  }

  int sensor_ready_flg = rdata[1];
  int16_t int_temp = ((rdata[2]&0xFF)<<8) + (rdata[3]&0xFF);
  int16_t int_humd = ((rdata[4]&0xFF)<<8) + (rdata[5]&0xFF);
  int16_t int_eth  = ((rdata[6]&0xFF)<<8) + (rdata[7]&0xFF);
  int16_t int_tvoc = ((rdata[8]&0xFF)<<8) + (rdata[9]&0xFF);
  int16_t int_eco2 = ((rdata[10]&0xFF)<<8) + (rdata[11]&0xFF);
  int16_t int_iaq  = ((rdata[12]&0xFF)<<8) + (rdata[13]&0xFF);
  int16_t int_rcda = ((rdata[14]&0xFF)<<8) + (rdata[15]&0xFF);

  mrbc_value array = mrbc_array_new(vm, 8);
  mrbc_value ready_value = mrb_fixnum_value((mrbc_int)sensor_ready_flg);
  mrbc_value temp_value = mrb_fixnum_value((mrbc_int)int_temp);
  mrbc_value humd_value = mrb_fixnum_value((mrbc_int)int_humd);
  mrbc_value eth_value = mrb_fixnum_value((mrbc_int)int_eth);
  mrbc_value tvoc_value = mrb_fixnum_value((mrbc_int)int_tvoc);
  mrbc_value eco2_value = mrb_fixnum_value((mrbc_int)int_eco2);
  mrbc_value iaq_value = mrb_fixnum_value((mrbc_int)int_iaq);
  mrbc_value rcda_value = mrb_fixnum_value((mrbc_int)int_rcda);

  mrbc_array_set(&array, 0, &ready_value);
  mrbc_array_set(&array, 1, &temp_value);
  mrbc_array_set(&array, 2, &humd_value);
  mrbc_array_set(&array, 3, &eth_value);
  mrbc_array_set(&array, 4, &tvoc_value);
  mrbc_array_set(&array, 5, &eco2_value);
  mrbc_array_set(&array, 6, &iaq_value);
  mrbc_array_set(&array, 7, &rcda_value);

  mrbc_decref(&ready_value);
  mrbc_decref(&temp_value);
  mrbc_decref(&humd_value);
  mrbc_decref(&eth_value);
  mrbc_decref(&tvoc_value);
  mrbc_decref(&eco2_value);
  mrbc_decref(&iaq_value);
  mrbc_decref(&rcda_value);

  SET_RETURN(array);
}

void define_air_quality_class()
{
  mrb_class *class_air_quality;
  class_air_quality = mrbc_define_class(0, "AirQuality", mrbc_class_object);
  mrbc_define_method(0, class_air_quality, "initialize", class_air_quality_init);
  mrbc_define_method(0, class_air_quality, "get_data", class_air_quality_get_data);
}
