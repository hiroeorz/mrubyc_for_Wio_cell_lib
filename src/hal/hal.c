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

/***** Feature test switches ************************************************/
/***** System headers *******************************************************/
#include <signal.h>
#include <sys/time.h>


/***** Local headers ********************************************************/
#include "hal.h"


/***** Constat values *******************************************************/
#define SERIAL_USB_SPEED 115200

/***** Macros ***************************************************************/
/***** Typedefs *************************************************************/
/***** Function prototypes **************************************************/
/***** Local variables ******************************************************/
/***** Global variables *****************************************************/
/***** Signal catching functions ********************************************/
/***** Local functions ******************************************************/
/***** Global functions *****************************************************/
#ifndef MRBC_NO_TIMER

//================================================================
/*!@brief
  initialize

*/
void hal_init(void)
{
  hal_init_serial_usb(SERIAL_USB_SPEED);
  hal_init_modem();
  hal_init_wio_client();
  hal_init_mqtt_client();
}


//================================================================
/*!@brief
  enable interrupt

*/
void hal_enable_irq(void)
{
}


//================================================================
/*!@brief
  disable interrupt

*/
void hal_disable_irq(void)
{
}


#endif /* ifndef MRBC_NO_TIMER */

int hal_write(int fd, const void *buf, int nbytes)
{
  char* t = (char*)buf;
  char tbuf[2];
  
  if (nbytes == 1) {
    tbuf[0] = *t;
    tbuf[1] = '\0';
    hal_write_string(tbuf);
    return nbytes;
  }

  hal_write_string(t);
  return nbytes;
}
