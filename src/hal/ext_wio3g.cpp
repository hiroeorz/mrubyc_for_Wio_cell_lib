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

static void class_wio_power_supply_cellular(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  bool b = mrbc_trans_cppbool_value(GET_TT_ARG(1));
  wio->PowerSupplyCellular(b);
  SET_TRUE_RETURN();
}

static void class_wio_power_supply_led(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  bool b = mrbc_trans_cppbool_value(GET_TT_ARG(1));
  wio->PowerSupplyLed(b);
  SET_TRUE_RETURN();
}

static void class_wio_power_supply_grove(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  bool b = mrbc_trans_cppbool_value(GET_TT_ARG(1));
  wio->PowerSupplyGrove(b);
  SET_TRUE_RETURN();
}

static void class_wio_led_set_rgb(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 3) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  int red   = GET_INT_ARG(1);
  int green = GET_INT_ARG(2);
  int blue  = GET_INT_ARG(3);

  wio->LedSetRGB(red, green, blue);
  SET_TRUE_RETURN();
}

void define_wio3g_class()
{
  wio = (Wio3G*)hal_get_modem_obj();

  mrb_class *class_wio;
  class_wio = mrbc_define_class(0, "Wio", mrbc_class_object);
  
  mrbc_define_method(0, class_wio, "init", class_wio_init);
  mrbc_define_method(0, class_wio, "power_supply_cellular", class_wio_power_supply_cellular);
  mrbc_define_method(0, class_wio, "power_supply_led", class_wio_power_supply_led);
  mrbc_define_method(0, class_wio, "power_supply_grove", class_wio_power_supply_grove);

  mrbc_define_method(0, class_wio, "led_set_rgb", class_wio_led_set_rgb);
}
