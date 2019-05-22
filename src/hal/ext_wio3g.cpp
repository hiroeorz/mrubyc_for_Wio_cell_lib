/*
  ext_wio3g.cpp

  Defining extension methods of Wio 3G

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include <limits.h>
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

  bool success = wio->TurnOnOrReset();

  if (success) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_wio_turn_off(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  bool success = wio->TurnOff();

  if (success) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
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
  if (len < 0) {
    DEBUG_PRINT("cannot get IMEI");
    SET_NIL_RETURN();
    return;
  }

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
  if (len < 0) {
    DEBUG_PRINT("cannot get IMSI");
    SET_NIL_RETURN();
    return;
  }

  imsi[len] = '\0';
  mrbc_value str = mrbc_string_new_cstr(vm, (const char *)imsi);
  SET_RETURN(str);
}

static void class_wio_get_phone_number(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }
  
  int phone_number_size = 32;
  char phone_number[32];

  int len = wio->GetPhoneNumber(phone_number, phone_number_size);
  if (len < 0) {
    DEBUG_PRINT("cannot get phone number");
    SET_NIL_RETURN();
    return;
  }

  phone_number[len] = '\0';
  mrbc_value str = mrbc_string_new_cstr(vm, (const char *)phone_number);
  SET_RETURN(str);
}

static void class_wio_wait_for_cs_registration(mrb_vm *vm, mrb_value *v, int argc)
{
  long timeout = 120000;

  if (argc > 1) {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }
  
  if (argc == 1) {
    timeout = GET_INT_ARG(1);
  }

  bool success = wio->WaitForCSRegistration(timeout);
  if (success) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_wio_get_received_signal_strength(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }
  
  int strength = wio->GetReceivedSignalStrength();

  if (INT_MIN == strength) {
    DEBUG_PRINT("!!! cannot get receive signal strength");
    SET_NIL_RETURN();
    return;
  }

  SET_INT_RETURN(strength);
}

void set_time_to_obj(mrb_vm *vm, mrb_value *time_obj, const char* key, int val)
{
  mrbc_value key_obj = mrbc_string_new_cstr(vm, key);
  mrbc_value val_obj = mrb_fixnum_value(val);
  mrbc_hash_set(time_obj, &key_obj, &val_obj);  
}

static void class_wio_get_time(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_NIL_RETURN();
    return;
  }

  struct tm now;
  if (!wio->GetTime(&now)) {
    DEBUG_PRINT("!!! cannot get time");
    SET_NIL_RETURN();
  }

  mrbc_value time_obj = mrbc_hash_new(vm, 6);
  set_time_to_obj(vm, &time_obj, "year" , now.tm_year + 1900);
  set_time_to_obj(vm, &time_obj, "month", now.tm_mon);
  set_time_to_obj(vm, &time_obj, "day"  , now.tm_mday);
  set_time_to_obj(vm, &time_obj, "hour" , now.tm_hour);
  set_time_to_obj(vm, &time_obj, "min"  , now.tm_min);
  set_time_to_obj(vm, &time_obj, "sec"  , now.tm_sec);
  SET_RETURN(time_obj);
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
  mrbc_define_method(0, class_wio, "get_phone_number", class_wio_get_phone_number);

  mrbc_define_method(0, class_wio, "wait_for_cs_registration", class_wio_wait_for_cs_registration);
  mrbc_define_method(0, class_wio, "get_received_signal_strength", class_wio_get_received_signal_strength);
  mrbc_define_method(0, class_wio, "get_time", class_wio_get_time);
}
