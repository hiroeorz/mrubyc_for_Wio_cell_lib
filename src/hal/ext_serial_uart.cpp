/*
  ext_serial_uart.cpp

  Defining extension methods of SerialUART

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include <limits.h>
#include "libmrubyc.h"
#include "ext.h"

// parity (0:なし, 1:奇数, 2:偶数)
int get_serial_uart_config(int parity)
{
  if (parity == 0)
  {
    return SERIAL_8N1;
  }
  if (parity == 1)
  {
    return SERIAL_8O1;
  }
  if (parity == 2)
  {
    return SERIAL_8E1;
  }
  return SERIAL_8N1;
}

static void class_serial_uart_initialize(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1 && argc != 2)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  int speed = GET_INT_ARG(1);
  int parity = 0; //パリティなし

  if (argc == 2)
  {
    parity = GET_INT_ARG(2); // 0:なし 1:奇数 2:偶数
  }

  int config = get_serial_uart_config(parity);
  SerialUART.begin(speed, config);
  SET_TRUE_RETURN();
}

static void class_serial_uart_print(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  uint8_t *str = GET_STRING_ARG(1);
  SerialUART.print((const char *)str);
}

static void class_serial_uart_write(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  int val = GET_INT_ARG(1);
  SerialUART.write((char)val);
}

static void class_serial_uart_read(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }

  char c = '\0';

  if (SerialUART.available() > 0)
  {
    c = SerialUART.read();
    const char str[] = {c, '\0'};
    mrbc_value str_obj = mrbc_string_new_cstr(vm, str);
    SET_RETURN(str_obj);
  }
  else
  {
    SET_NIL_RETURN();
  }
}

static void class_serial_uart_read_binary(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }

  if (SerialUART.available() > 0)
  {
    int val = SerialUART.read();
    SET_INT_RETURN(val);
  }
  else
  {
    SET_NIL_RETURN();
  }
}

static void class_serial_uart_available(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }

  int size = SerialUART.available();
  SET_INT_RETURN(size);
}

static void class_serial_uart_clear(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }

  for (int i = 0; i < 16; i++)
  {
    if (SerialUART.available() > 0)
    {
      while (SerialUART.available() > 0)
      {
        SerialUART.read();
      }
    }

    hal_delay(1); // sleep 1ms
  }

  SET_TRUE_RETURN();
}

static void class_serial_uart_gets(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0 && argc != 1 && argc != 2)
  {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }

  char c = '\0';
  char eol = '\r';
  int max_count = 1024;

  if (argc == 1)
  {
    uint8_t *str = GET_STRING_ARG(1);
    eol = str[0];
  }

  if (argc == 2)
  {
    max_count = GET_INT_ARG(2);
  }

  int i = 0;
  char recv[max_count + 1];
  int count = 0;

  while (c != eol)
  {
    if (count >= max_count)
    {
      break;
    }

    if (SerialUART.available() > 0)
    {
      c = SerialUART.read();
      recv[i] = c;
      i++;
    }
    else
    {
      SET_NIL_RETURN();
      return;
    }

    count++;
  }

  recv[i] = '\0';
  mrbc_value str_obj = mrbc_string_new_cstr(vm, recv);
  SET_RETURN(str_obj);
}

void define_serial_uart_class()
{
  mrb_class *class_uart;
  class_uart = mrbc_define_class(0, "SerialUART", mrbc_class_object);

  mrbc_define_method(0, class_uart, "initialize", class_serial_uart_initialize);
  mrbc_define_method(0, class_uart, "print", class_serial_uart_print);
  mrbc_define_method(0, class_uart, "write", class_serial_uart_write);
  mrbc_define_method(0, class_uart, "read", class_serial_uart_read);
  mrbc_define_method(0, class_uart, "read_binary", class_serial_uart_read_binary);
  mrbc_define_method(0, class_uart, "gets", class_serial_uart_gets);
  mrbc_define_method(0, class_uart, "available", class_serial_uart_available);
  mrbc_define_method(0, class_uart, "clear!", class_serial_uart_clear);
}
