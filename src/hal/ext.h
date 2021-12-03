/*
  ext.cpp

  Header file for  extension methods

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#ifndef __EXT_H_
#define __EXT_H_

#include "value.h"

bool mrbc_trans_cppbool_value(mrbc_vtype tt);

void define_wio_class(void);
void define_arduino_class(void);
void define_serial_uart_class(void);
void define_mqtt_client_class(void);
void define_string_ext_class(void);
void define_bmp280_class(void);
void define_sht31_class(void);
void define_sht35_class(void);
void define_bme680_class(void);
void define_i2c_rs485_class(void);

#endif
