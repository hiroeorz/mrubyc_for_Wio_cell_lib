/*
  libmrubyc_config.h

  Header file for Arduino application

  Copyright (c) 2019, Shin Hiroe All rights reserved

*/

#ifndef __LIBMRUBYC_CONFIG_H__
#define __LIBMRUBYC_CONFIG_H__

#define WIOMRBC_VERSION "0.0.1"

#define WIOMRBC_DEBUG

#ifdef WIOMRBC_DEBUG
#define DEBUG_PRINT(val)   SerialUSB.print(val)
#define DEBUG_PRINTLN(val) SerialUSB.println(val)
#else
#define DEBUG_PRINT(val)
#define DEBUG_PRINTLN(val)
#endif

#endif
