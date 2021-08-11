/*
  ext.cpp

  Defining extension methods

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

bool mrbc_trans_cppbool_value(mrbc_vtype tt)
{
  if (tt == MRBC_TT_TRUE) {
    return true;
  }

  return false;
}


void mrbc_define_wio_methods(void)
{
  define_wio_class();
  define_arduino_class();
  define_serial_uart_class();
  define_mqtt_client_class();
  define_string_ext_class();
  define_bmp280_class();
  define_sht31_class();
  define_sht35_class();
  define_bme680_class();
  define_air_quality_class();

  // mrblib以下のrubyソースから生成したバイトコードを読み込む.
  // src/hal/wio_mrb_lib.c
  extern const uint8_t mruby_wio_code[];

  if (NULL == mrbc_create_task(mruby_wio_code, 0)) {
    hal_write_string((char *)"!!! wio bytecode load error\n");
  }

  mrbc_run();
}
