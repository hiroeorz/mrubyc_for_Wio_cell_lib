/*
  libmrubyc.h

  Header file for Arduino application

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#ifndef __LIBMRUBYC_H_
#define __LIBMRUBYC_H_

#if defined ARDUINO_WIO_LTE
#include <WioLTEforArduino.h>
#else
#include <WioCellLibforArduino.h>
#endif

#include "mrubyc.h"
#include "libmrubyc_config.h"

void mrbc_define_wio_methods(void);
WioCellular* mrbc_get_wio3g_obj(void);

#endif
