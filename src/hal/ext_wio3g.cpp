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

static void class_wio_turn_on_or_reset(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  wio->TurnOnOrReset();
  SET_TRUE_RETURN();
}

static void class_wio_turn_off(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  wio->TurnOff();
  SET_TRUE_RETURN();
}

static void class_wio_get_imei(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }
  
  int imei_size = 32;
  char imei[32];

  int len = wio->GetIMEI(imei, imei_size);
  imei[len] = '\0';
  mrbc_value str = mrbc_string_new_cstr(vm, (const char *)imei);
  SET_RETURN(str);
}

static void class_wio_get_imsi(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }
  
  int imsi_size = 32;
  char imsi[32];

  int len = wio->GetIMSI(imsi, imsi_size);
  imsi[len] = '\0';
  mrbc_value str = mrbc_string_new_cstr(vm, (const char *)imsi);
  SET_RETURN(str);
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

  mrbc_define_method(0, class_wio, "turn_on_or_reset", class_wio_turn_on_or_reset);
  mrbc_define_method(0, class_wio, "turn_off", class_wio_turn_off);

  mrbc_define_method(0, class_wio, "get_imei", class_wio_get_imei);
  mrbc_define_method(0, class_wio, "get_imsi", class_wio_get_imsi);
}
