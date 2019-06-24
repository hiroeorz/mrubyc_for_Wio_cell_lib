/*
  hal.cpp

  mruby/c hardware abstract layer for Wio3G
 */

#include "hal.h"
#include "libmrubyc.h"

#if defined ARDUINO_WIO_LTE
static WioLTE *Wio = NULL;
static WioLTEClient *WioClient = NULL;
#else
static WioCellular *Wio=NULL;
static WioCellularClient *WioClient = NULL;
#endif

static PubSubClient *MqttClient = NULL;

extern "C" void hal_init_modem(void)
{
  if (Wio != NULL) return;

#if defined ARDUINO_WIO_LTE
  Wio = new WioLTE();
#else
  Wio = new WioCellular();
#endif

  Wio->Init();
}

extern "C" void hal_init_serial_usb(unsigned int speed)
{
  SerialUSB.begin(speed);
}

extern "C" void* hal_get_modem_obj(void)
{
  return (void*)Wio;
}

extern "C" void hal_write_string(char* text)
{
  SerialUSB.print(text);
}

extern "C" void hal_delay(unsigned long t)
{
  delay(t);
}
