/*! @file
  @brief
  Global configration of mruby/c VM's

  <pre>
  Copyright (C) 2015-2019 Kyushu Institute of Technology.
  Copyright (C) 2015-2019 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.


  </pre>
*/

#ifndef MRBC_SRC_VM_CONFIG_H_
#define MRBC_SRC_VM_CONFIG_H_

// maximum number of VMs
#if !defined(MAX_VM_COUNT)
#define MAX_VM_COUNT 2
#endif

// maximum size of registers
#if !defined(MAX_REGS_SIZE)
#define MAX_REGS_SIZE 100
#endif

// maximum number of symbols
#if !defined(MAX_SYMBOLS_COUNT)
#define MAX_SYMBOLS_COUNT 1024
#endif

// maximum number of exception depth
#if !defined(MAX_EXCEPTION_COUNT)
#define MAX_EXCEPTION_COUNT 16
#endif

// memory management
//  MRBC_ALLOC_16BIT or MRBC_ALLOC_24BIT
#define MRBC_ALLOC_24BIT

// Console new-line mode.
//  If you need to convert LF to CRLF in console output, enable the following:
// #define MRBC_CONVERT_CRLF

/* Configure environment
   0: NOT USE
   1: USE float
   2: USE double
*/
// USE Float. Support Float class.
#if !defined(MRBC_USE_FLOAT)
#define MRBC_USE_FLOAT 1
#endif

// Use math. Support Math class.
#if !defined(MRBC_USE_MATH)
#define MRBC_USE_MATH 0
#endif
/* (NOTE)
   maybe you need
   $ export LDFLAGS=-lm
   $ make

   on ubuntu
   $ export LDFLAGS="-Wl,--no-as-needed -lm"
   $ make
*/

// USE String. Support String class.
#if !defined(MRBC_USE_STRING)
#define MRBC_USE_STRING 1
#endif

/* Hardware dependent flags */

/* Endian
   Define either MRBC_BIG_ENDIAN or MRBC_LITTLE_ENDIAN.
*/
#if !defined(MRBC_BIG_ENDIAN) && !defined(MRBC_LITTLE_ENDIAN)
#define MRBC_LITTLE_ENDIAN
#endif

/* 32it alignment
   If 32-bit alignment is required, enable the following line.
 */
// #define MRBC_REQUIRE_32BIT_ALIGNMENT

// Debug code.
#if !defined(NDEBUG)
#define MRBC_DEBUG
#endif

// #define MRBC_NO_TIMER
#if !defined(MRBC_NO_TIMER)
#define MRBC_NO_TIMER
#endif

#endif
