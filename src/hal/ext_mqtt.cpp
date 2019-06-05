/*
  ext_mqtt.cpp

  Defining extension methods of MQTTClient

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#include <limits.h>
#include "libmrubyc.h"
#include "ext.h"

static WioCellular *wio = NULL;
static WioCellularClient *wio_client = NULL;
static PubSubClient *mqtt_client = NULL;

static void class_mqtt_client_initialize(mrb_vm *vm, mrb_value *v, int argc)
{
}

static void class_mqtt_client_connect(mrb_vm *vm, mrb_value *v, int argc)
{
  uint8_t *host = GET_STRING_ARG(1);

  int port = 1883;
  if (argc >= 2) { port = (int)GET_INT_ARG(2); }

  uint8_t *connect_id = NULL;
  if (argc >= 3) { connect_id = GET_STRING_ARG(1); }


  mqtt_client->setServer((const char *)host, port);
  mqtt_client->setClient(*wio_client);
  bool success = mqtt_client->connect((const char *)connect_id);

  if (success) {
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

  mqtt_client->publish((const char *)topic, (const char *)payload);
  SET_TRUE_RETURN();
}

void define_mqtt_client_class()
{
  wio_client = (WioCellularClient *)hal_get_wio_client_obj();
  mqtt_client = (PubSubClient *)hal_get_mqtt_client_obj();  

  mrb_class *class_mqtt_client;
  class_mqtt_client = mrbc_define_class(0, "MQTTClient", mrbc_class_object);

  mrbc_define_method(0, class_mqtt_client, "initialize", class_mqtt_client_initialize);
  mrbc_define_method(0, class_mqtt_client, "connect", class_mqtt_client_connect);
  mrbc_define_method(0, class_mqtt_client, "disconnect", class_mqtt_client_disconnect);
  mrbc_define_method(0, class_mqtt_client, "publish", class_mqtt_client_publish);
}
