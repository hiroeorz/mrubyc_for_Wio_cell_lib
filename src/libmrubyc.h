/*
  libmrubyc.h

  Header file for Arduino application

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#ifndef __LIBMRUBYC_H_
#define __LIBMRUBYC_H_

#include <WioCellLibforArduino.h>
#include "mrubyc.h"
#include "libmrubyc_config.h"

void mrbc_define_wio_methods(void);
WioCellular* mrbc_get_wio3g_obj(void);

#endif
