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
static BMP280 *Bmp280 = NULL;
static int Bmp280Enable = 0;

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

extern "C" void hal_init_bmp280(void)
{
  if (Bmp280 != NULL) return;

  Bmp280 = new BMP280();
  if (Bmp280->init()) { Bmp280Enable = 1; }
}

extern "C" void* hal_get_bmp280_obj(void)
{
  return (void*)Bmp280;
}

extern "C" int hal_bmp280_is_enable(void)
{
  return Bmp280Enable;
}
