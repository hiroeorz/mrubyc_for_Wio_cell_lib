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
}
