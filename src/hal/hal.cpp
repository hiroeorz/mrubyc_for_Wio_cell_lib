/*
  hal.cpp

  mruby/c hardware abstract layer for Wio3G
 */

#include <Wio3GforArduino.h>
#include "hal.h"

static Wio3G *Wio=NULL;

extern "C" void hal_init_modem(void)
{
  if (Wio != NULL) return;
  Wio = new Wio3G();
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

