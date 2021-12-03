/*
  ext_arduino.cpp

  Defining extension methods of Wio 3G

  Copyright (c) 2019, Shin Hiroe All rights reserved

  Detail: https://github.com/meerstern/I2C_RS422_RS485_Converter
*/

#include "libmrubyc.h"
#include "ext.h"
#include "i2c_rs485/SC16IS750.h"

static SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C, SC16IS750_ADDRESS_BB);

static void class_i2c_rs485_init(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  SerialUSB.println("begin ok.");
  int baudrate = GET_INT_ARG(1);
  i2cuart.begin(baudrate);
}

static void class_i2c_rs485_ping(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  if (i2cuart.ping())
  {
    SET_TRUE_RETURN();
    return;
  }

  SET_FALSE_RETURN();
}

static void class_i2c_rs485_set_rts_pin(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  int state = GET_INT_ARG(1);
  i2cuart.SetRtsPin(state);
  SET_NIL_RETURN();
}

static void class_i2c_rs485_available(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  int count = i2cuart.available();
  SET_INT_RETURN(count);
}

static void class_i2c_rs485_write(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  char val = (char)GET_INT_ARG(1);
  i2cuart.write(val);
  SET_TRUE_RETURN();
}

static void class_i2c_rs485_read(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  char val = i2cuart.read();
  SET_INT_RETURN(val);
}

static void class_i2c_rs485_write_test(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  i2cuart.SetRtsPin(1);

  delay(5);
  SerialUSB.print("sending modbus-rtu data......");
  i2cuart.write(0x01); // Address
  i2cuart.write(0x04); // Function
  i2cuart.write(0x00); //開始アドレス（上位）
  i2cuart.write(0x01); //開始アドレス（下位）
  i2cuart.write(0x00); //レジスタ数　（上位）
  i2cuart.write(0x02); //レジスタ数　（下位）
  i2cuart.write(0x20); // CRC（上位）
  i2cuart.write(0x0b); // CRC（下位）
  delay(5);

  SET_INT_RETURN(0);
}

static void class_i2c_rs485_read_values(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  SerialUSB.print("read_values");
  i2cuart.SetRtsPin(0);

  while (i2cuart.available() == 0)
  {
  }

  SerialUSB.print("Data:");
  SerialUSB.print("available: ");
  SerialUSB.println(i2cuart.available());

  mrbc_value array = mrbc_array_new(vm, 100);

  while (i2cuart.available() > 0)
  {
    uint8_t val;
    val = i2cuart.read();
    mrbc_value rb_val = mrbc_fixnum_value(val);
    mrbc_array_push(&array, &rb_val);
  }

  SET_RETURN(array);
}

static void class_i2c_rs485_write_values(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1)
  {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  const mrbc_value *rb_array = &GET_ARG(1);
  int length = mrbc_array_size(rb_array);

  i2cuart.SetRtsPin(1);
  delay(5);

  for (int i = 0; i < length; ++i)
  {
    mrbc_value rb_val = mrbc_array_get(rb_array, i);
    uint8_t val = (uint8_t)mrbc_fixnum(rb_val);
    i2cuart.write(val);
  }

  delay(5);
  i2cuart.SetRtsPin(0);
  SET_INT_RETURN(0);
}

void define_i2c_rs485_class()
{
  mrb_class *class_i2c_rs485;
  class_i2c_rs485 = mrbc_define_class(0, "I2C_RS485", mrbc_class_object);

  mrbc_define_method(0, class_i2c_rs485, "initialize", class_i2c_rs485_init);
  mrbc_define_method(0, class_i2c_rs485, "ping", class_i2c_rs485_ping);
  mrbc_define_method(0, class_i2c_rs485, "set_rts_pin", class_i2c_rs485_set_rts_pin);
  mrbc_define_method(0, class_i2c_rs485, "available", class_i2c_rs485_available);
  mrbc_define_method(0, class_i2c_rs485, "write", class_i2c_rs485_write);
  mrbc_define_method(0, class_i2c_rs485, "read", class_i2c_rs485_read);
  mrbc_define_method(0, class_i2c_rs485, "write_test", class_i2c_rs485_write_test);
  mrbc_define_method(0, class_i2c_rs485, "write_values", class_i2c_rs485_write_values);
  mrbc_define_method(0, class_i2c_rs485, "read_values", class_i2c_rs485_read_values);
}