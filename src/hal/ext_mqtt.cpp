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

void mqtt_subscribe_callback(char* topic, byte* payload, unsigned int len)
{
  char payload_str[len + 1];

  for (int i = 0; i < (int)len; i++){
    payload_str[i] = payload[i];
  }
  payload_str[len] = '\0';

  SerialUSB.print("received: ");
  SerialUSB.print(topic);
  SerialUSB.print("  payload: ");
  SerialUSB.println(payload_str);

  mrbc_value topic_obj = mrbc_string_new_cstr(0, (const char *)topic);
  mrbc_value payload_obj = mrbc_string_new_cstr(0, (const char *)payload);
  mrbc_value obj = mrbc_hash_new(0, 2);
  mrbc_hash_set(&obj, &topic_obj, &payload_obj);
  
  //mrbc_value v[] = {};
  //mrbc_send(callback_vm, v, 0, callback_receiver, "recv_test", 0);

  mrbc_value v[] = {*callback_receiver};
  mrbc_funcall(callback_vm, "receive_callback", v, 0);
  DEBUG_PRINT("funcalled.");
}


static void class_mqtt_client_recv_callback_exec(mrb_vm *vm, mrb_value *v, int argc)
{
  SerialUSB.println("received in c function");
  mrbc_funcall(vm, "receive_callback", v, 0);  // not work...
}

static void class_mqtt_client_initialize(mrb_vm *vm, mrb_value *v, int argc)
{
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
  //callback_vm = vm;
  //callback_receiver = &v[1];
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

  mrbc_define_method(0, class_mqtt_client, "initialize", class_mqtt_client_initialize);
  mrbc_define_method(0, class_mqtt_client, "connect", class_mqtt_client_connect);
  mrbc_define_method(0, class_mqtt_client, "disconnect", class_mqtt_client_disconnect);
  mrbc_define_method(0, class_mqtt_client, "publish", class_mqtt_client_publish);
  mrbc_define_method(0, class_mqtt_client, "subscribe", class_mqtt_client_subscribe);
  mrbc_define_method(0, class_mqtt_client, "unsubscribe", class_mqtt_client_unsubscribe);
  mrbc_define_method(0, class_mqtt_client, "loop_msec", class_mqtt_client_loop_msec);
  mrbc_define_method(0, class_mqtt_client, "connected?", class_mqtt_client_is_connected);

  mrbc_define_method(0, class_mqtt_client, "recv_test", class_mqtt_client_recv_callback_exec);
}
