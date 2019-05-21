/*
  libmrubyc.h

  Header file for Arduino application

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#ifndef __LIBMRUBYC_H_
#define __LIBMRUBYC_H_

#include <Wio3GforArduino.h>
#include "mrubyc.h"
#include "libmrubyc_config.h"

void mrbc_define_wio3g_methods(void);
Wio3G* mrbc_get_wio3g_obj(void);

#endif
