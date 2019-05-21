/* dumped in big endian order.
   use `mrbc -e` option for better performance on little endian CPU. */
#include <stdint.h>
extern const uint8_t code1[];

const uint8_t
#if defined __GNUC__
__attribute__((aligned(4)))
#elif defined _MSC_VER
__declspec(align(4))
#endif
code1[] = {
0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x34,0xd8,0x7e,0x00,0x00,0x00,0xfb,0x4d,0x41,
0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0xbb,0x30,0x30,
0x30,0x30,0x00,0x00,0x00,0xb3,0x00,0x03,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x14,
0x01,0x80,0x00,0x11,0x01,0x80,0x40,0x20,0x00,0x80,0xc0,0x01,0x01,0x80,0x01,0x11,
0x01,0x80,0x40,0x20,0x01,0x00,0xc0,0x01,0x01,0x80,0x00,0x06,0x02,0x00,0x00,0x3d,
0x01,0x80,0xc0,0xa0,0x00,0x40,0x03,0x17,0x01,0x80,0x00,0x06,0x02,0x40,0x00,0x03,
0x01,0x81,0x00,0xa0,0x01,0x80,0x00,0x06,0x02,0x00,0x00,0xbd,0x01,0x80,0xc0,0xa0,
0x01,0x80,0x00,0x07,0x01,0xbf,0xfc,0x18,0x01,0x80,0x00,0x05,0x00,0x00,0x00,0x4a,
0x00,0x00,0x00,0x02,0x00,0x00,0x19,0x68,0x65,0x6c,0x6c,0x6f,0x20,0x6d,0x72,0x75,
0x62,0x79,0x21,0x20,0x49,0x20,0x61,0x6d,0x20,0x74,0x61,0x73,0x6b,0x31,0x20,0x21,
0x00,0x00,0x05,0x74,0x61,0x73,0x6b,0x31,0x00,0x00,0x00,0x05,0x00,0x03,0x57,0x69,
0x6f,0x00,0x00,0x03,0x6e,0x65,0x77,0x00,0x00,0x07,0x41,0x72,0x64,0x75,0x69,0x6e,
0x6f,0x00,0x00,0x04,0x70,0x75,0x74,0x73,0x00,0x00,0x05,0x73,0x6c,0x65,0x65,0x70,
0x00,0x4c,0x56,0x41,0x52,0x00,0x00,0x00,0x22,0x00,0x00,0x00,0x02,0x00,0x03,0x77,
0x69,0x6f,0x00,0x07,0x61,0x72,0x64,0x75,0x69,0x6e,0x6f,0x00,0x00,0x00,0x01,0x00,
0x01,0x00,0x02,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
};

extern const uint8_t code2[];
const uint8_t
#if defined __GNUC__
__attribute__((aligned(4)))
#elif defined _MSC_VER
__declspec(align(4))
#endif
code2[] = {
0x52,0x49,0x54,0x45,0x30,0x30,0x30,0x34,0x6c,0x6a,0x00,0x00,0x00,0xab,0x4d,0x41,
0x54,0x5a,0x30,0x30,0x30,0x30,0x49,0x52,0x45,0x50,0x00,0x00,0x00,0x8d,0x30,0x30,
0x30,0x30,0x00,0x00,0x00,0x85,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x0e,
0x00,0x80,0x00,0x06,0x01,0x00,0x00,0x3d,0x00,0x80,0x00,0xa0,0x00,0x40,0x03,0x17,
0x00,0x80,0x00,0x06,0x01,0x40,0x00,0x83,0x00,0x80,0x40,0xa0,0x00,0x80,0x00,0x06,
0x01,0x00,0x00,0xbd,0x00,0x80,0x00,0xa0,0x00,0x80,0x00,0x07,0x00,0xbf,0xfc,0x18,
0x00,0x80,0x00,0x05,0x00,0x00,0x00,0x4a,0x00,0x00,0x00,0x02,0x00,0x00,0x19,0x68,
0x65,0x6c,0x6c,0x6f,0x20,0x6d,0x72,0x75,0x62,0x79,0x21,0x20,0x49,0x20,0x61,0x6d,
0x20,0x74,0x61,0x73,0x6b,0x32,0x20,0x21,0x00,0x00,0x05,0x74,0x61,0x73,0x6b,0x32,
0x00,0x00,0x00,0x02,0x00,0x04,0x70,0x75,0x74,0x73,0x00,0x00,0x05,0x73,0x6c,0x65,
0x65,0x70,0x00,0x45,0x4e,0x44,0x00,0x00,0x00,0x00,0x08,
};

#include <Wio3GforArduino.h>
#include <libmrubyc.h>
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
