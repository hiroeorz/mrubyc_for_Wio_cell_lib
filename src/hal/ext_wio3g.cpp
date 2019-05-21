/*
  ext_wio3g.cpp

  Defining extension methods of Wio 3G

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include "libmrubyc.h"
#include "ext.h"

static Wio3G* wio = NULL;

static void class_wio_init(mrb_vm *vm, mrb_value *v, int argc)
{
  wio->Init();
  SET_TRUE_RETURN();
}

void define_wio3g_class()
{
  wio = (Wio3G*)hal_get_modem_obj();

  mrb_class *class_wio;
  class_wio = mrbc_define_class(0, "Wio", mrbc_class_object);
  
  // --- Power ---
  mrbc_define_method(0, class_wio, "init", class_wio_init);
}
