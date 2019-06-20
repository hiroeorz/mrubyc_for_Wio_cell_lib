/*
  ext_string.cpp

  Defining extension methods of String

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

//================================================================
/*! (method) hex
*/
static void c_string_hex(struct VM *vm, mrbc_value v[], int argc)
{
  if( argc != 0 ) {
    console_print("ArgumentError\n");	// raise?
    return;
  }

  uint8_t *str = GET_STRING_ARG(0);
  long val = strtol((const char *)str, NULL, 16);
  SET_INT_RETURN((int)val);
}


void define_string_ext_class()
{
  mrb_class *class_string;
  class_string = mrbc_get_class_by_name("String");
  mrbc_define_method(0, class_string, "hex", c_string_hex);
}
