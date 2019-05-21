#include <Wio3GforArduino.h>
#include <libmrubyc.h>
#include "task.c"

extern const uint8_t code1[];
extern const uint8_t code2[];

#define MEMSIZE (1024*30)
static uint8_t mempool[MEMSIZE];

void setup() {
  delay(1000);

  mrbc_init(mempool, MEMSIZE);
  mrbc_define_wio3g_methods();

  if (NULL == mrbc_create_task(code1, 0)) {
    SerialUSB.println("!!! mrbc_create_task error");
    return;
  }
  if (NULL == mrbc_create_task(code2, 0)) {
    SerialUSB.println("!!! mrbc_create_task error");
    return;
  }

  SerialUSB.println("--- running mruby/c ---");
  mrbc_run();
}

void loop() {
  delay(1000);
}
