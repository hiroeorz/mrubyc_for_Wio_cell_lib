/*
  ext_wio3g.cpp

  Defining extension methods

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

void mrbc_define_wio3g_methods(void)
{
  define_wio3g_class();
  define_arduino_class();
}
