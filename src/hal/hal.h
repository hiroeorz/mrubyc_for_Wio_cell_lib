/*! @file
  @brief
  Hardware abstraction layer
        for POSIX

  <pre>
  Copyright (C) 2016 Kyushu Institute of Technology.
  Copyright (C) 2016 Shimane IT Open-Innovation Center.

  This file is distributed under BSD 3-Clause License.
  </pre>
*/

#ifndef MRBC_SRC_HAL_H_
#define MRBC_SRC_HAL_H_

#ifdef __cplusplus
extern "C" {
#endif

/***** Feature test switches ************************************************/
/***** System headers *******************************************************/
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

/***** Local headers ********************************************************/
#include "hal.h"

/***** Constant values ******************************************************/
/***** Macros ***************************************************************/
#ifndef MRBC_SCHEDULER_EXIT
#define MRBC_SCHEDULER_EXIT 1
#endif


/***** Typedefs *************************************************************/
/***** Global variables *****************************************************/
/***** Function prototypes **************************************************/
void mrbc_tick(void);
void hal_delay(unsigned long t);


#ifndef MRBC_NO_TIMER
void hal_init(void);
void hal_enable_irq(void);
void hal_disable_irq(void);
# define hal_idle_cpu()   sleep(1) // maybe interrupt by SIGINT

#else // MRBC_NO_TIMER
void hal_init(void);
# define hal_enable_irq()  ((void)0)
# define hal_disable_irq() ((void)0)
# define hal_idle_cpu()    (hal_delay(1), mrbc_tick())

#endif


/***** Inline functions *****************************************************/

//================================================================
/*!@brief
  Write

  @param  fd    dummy, but 1.
  @param  buf   pointer of buffer.
  @param  nbytes        output byte length.
*/
int hal_write(int fd, const void *buf, int nbytes);


//================================================================
/*!@brief
  Flush write baffer

  @param  fd    dummy, but 1.
*/
inline static int hal_flush(int fd)
{
  return fsync(1);
}

/* Wio 3G */
void hal_write_string(char* text);
void hal_init_modem(void);
void* hal_get_modem_obj(void);
void hal_init_serial_usb(unsigned int speed);

void hal_init_serial_uart(void);
void* hal_get_serial_uart_obj(void);

void hal_init_bmp280(unsigned char iic_addr);
void* hal_get_bmp280_obj(unsigned char iic_addr);
int hal_bmp280_is_enable(unsigned char iic_addr);

void hal_init_bme680(unsigned char iic_addr);
void* hal_get_bme680_obj(unsigned char iic_addr);
int hal_bme680_is_enable(unsigned char iic_addr);

void hal_init_sht31(void);
void* hal_get_sht31_obj(void);

int hal_init_sht35(unsigned char iic_addr);
void* hal_get_sht35_obj(unsigned char iic_addr);

#ifdef __cplusplus
}
#endif
#endif // ifndef MRBC_HAL_H_
