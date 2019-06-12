#include <libmrubyc.h>
#include "task.c"

extern const uint8_t code[];

#define MEMSIZE (1024*40)
static uint8_t mempool[MEMSIZE];

void setup() {
  delay(1000);

  mrbc_init(mempool, MEMSIZE);
  mrbc_define_wio_methods();

  if (NULL == mrbc_create_task(code, 0)) {
    SerialUSB.println("!!! mrbc_create_task error");
    return;
  } 
}

void loop() {
  SerialUSB.println("--- running mruby/c ---");
  mrbc_run();
}
