/*
  ext_mqtt.cpp

  Defining extension methods of MQTTClient

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include <limits.h>
#include "libmrubyc.h"
#include "ext.h"

#if defined ARDUINO_WIO_LTE
static WioLTE *wio = NULL;
static WioLTEClient *wio_client = NULL;
#else
static WioCellular *wio = NULL;
static WioCellularClient *wio_client = NULL;
#endif

static PubSubClient *mqtt_client = NULL;
static VM *callback_vm = NULL;
static mrbc_value *callback_receiver = NULL;
static const char recive_data_iv_name[] = "_received_data";

void mqtt_subscribe_callback(char* topic, byte* payload, unsigned int len)
{
  char payload_str[len + 1];
  for (int i = 0; i < (int)len; i++){
    payload_str[i] = (char)payload[i];
  }
  payload_str[len] = '\0';

  char topic_str[sizeof(topic)];
  strcpy(topic_str, topic);

  mrbc_value topic_key = mrbc_string_new_cstr(callback_vm, "topic");
  mrbc_value payload_key = mrbc_string_new_cstr(callback_vm, "payload");
  mrbc_value topic_obj = mrbc_string_new_cstr(callback_vm, (const char *)topic_str);
  mrbc_value payload_obj = mrbc_string_new_cstr(callback_vm, (const char *)payload_str);

  mrbc_value obj = mrbc_hash_new(callback_vm, 2);
  mrbc_hash_set(&obj, &topic_key, &topic_obj);
  mrbc_hash_set(&obj, &payload_key, &payload_obj);

  mrbc_symbol_new(callback_vm, recive_data_iv_name);
  mrbc_sym sym_id = str_to_symid(recive_data_iv_name);
  mrbc_instance_setiv(callback_receiver, sym_id, &obj);
}

static void class_mqtt_client_connect(mrb_vm *vm, mrbc_value *v, int argc)
{
  uint8_t *host = GET_STRING_ARG(1);

  int port = 1883;
  if (argc >= 2) { port = (int)GET_INT_ARG(2); }

  uint8_t *connect_id = NULL;
  if (argc >= 3) { connect_id = GET_STRING_ARG(3); }


  mqtt_client->setServer((const char *)host, port);
  mqtt_client->setClient(*wio_client);
  bool success = mqtt_client->connect((const char *)connect_id);

  if (success) {
    callback_vm = vm;
    callback_receiver = &v[1];
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_mqtt_client_disconnect(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  mqtt_client->disconnect();
  SET_TRUE_RETURN();
}

static void class_mqtt_client_publish(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 2) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  uint8_t *topic = GET_STRING_ARG(1);
  uint8_t *payload = GET_STRING_ARG(2);

  bool success = mqtt_client->publish((const char *)topic, (const char *)payload);
  if (success) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_mqtt_client_subscribe(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1 && argc != 2) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  uint8_t *topic = GET_STRING_ARG(1);
  bool success = false;
  mqtt_client->setCallback(mqtt_subscribe_callback);

  if (argc == 1) {
    success = mqtt_client->subscribe((const char *)topic);
  } else {
    uint8_t qos = (uint8_t)GET_INT_ARG(2);
    success = mqtt_client->subscribe((const char *)topic, qos);
  }

  if (success) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_mqtt_client_unsubscribe(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  uint8_t *topic = GET_STRING_ARG(1);
  bool success = mqtt_client->unsubscribe((const char *)topic);
  
  if (success) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

static void class_mqtt_client_loop_msec(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 1) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  double msec = GET_INT_ARG(1);
  unsigned long next = millis();

  while (millis() < next + (long)msec) {
    mqtt_client->loop();
  }

  SET_NIL_RETURN();
}

static void class_mqtt_client_is_connected(mrb_vm *vm, mrb_value *v, int argc)
{
  if (argc != 0) {
    DEBUG_PRINT("!!! invalid argc");
    SET_FALSE_RETURN();
    return;
  }

  bool connected = mqtt_client->connected();
  if (connected) {
    SET_TRUE_RETURN();
  } else {
    SET_FALSE_RETURN();
  }
}

void define_mqtt_client_class()
{
#if defined ARDUINO_WIO_LTE
  wio = (WioLTE*)hal_get_modem_obj();
  wio_client = new WioLTEClient(wio);
#else
  wio = (WioCellular*)hal_get_modem_obj();
  wio_client = new WioCellularClient(wio);
#endif

  mqtt_client = new PubSubClient();
  static mrb_class *class_mqtt_client;
  class_mqtt_client = mrbc_define_class(0, "MQTTClient", mrbc_class_object);

  mrbc_define_method(0, class_mqtt_client, "connect", class_mqtt_client_connect);
  mrbc_define_method(0, class_mqtt_client, "disconnect", class_mqtt_client_disconnect);
  mrbc_define_method(0, class_mqtt_client, "publish", class_mqtt_client_publish);
  mrbc_define_method(0, class_mqtt_client, "subscribe", class_mqtt_client_subscribe);
  mrbc_define_method(0, class_mqtt_client, "unsubscribe", class_mqtt_client_unsubscribe);
  mrbc_define_method(0, class_mqtt_client, "loop_msec", class_mqtt_client_loop_msec);
  mrbc_define_method(0, class_mqtt_client, "connected?", class_mqtt_client_is_connected);
}
