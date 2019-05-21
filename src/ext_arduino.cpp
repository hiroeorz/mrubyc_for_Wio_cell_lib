/*
  ext_arduino.cpp

  Defining extension methods of Wio 3G

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static void class_arduino_delay(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINTLN("invalid argc");
    SET_NIL_RETURN();
    return;
  }

  long msec = GET_INT_ARG(1);
  delay(msec);
}

void define_arduino_class()
{
  mrb_class *class_arduino;
  class_arduino = mrbc_define_class(0, "Arduino", mrbc_class_object);

  mrbc_define_method(0, class_arduino, "delay", class_arduino_delay);
}
