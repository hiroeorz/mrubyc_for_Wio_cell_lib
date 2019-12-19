/*
  hal.cpp

  mruby/c hardware abstract layer for Wio3G
 */

#include "hal.h"
#include "libmrubyc.h"

#if defined ARDUINO_WIO_LTE
static WioLTE *Wio = NULL;
static WioLTEClient *WioClient = NULL;
#else
static WioCellular *Wio=NULL;
static WioCellularClient *WioClient = NULL;
#endif

static PubSubClient *MqttClient = NULL;

static BMP280 *Bmp280_76 = NULL;
static BMP280 *Bmp280_77 = NULL;
static int Bmp280Enable_76 = 0;
static int Bmp280Enable_77 = 0;

static SHT31 *Sht31 = NULL;

static SHT35 *Sht35_44 = NULL;
static SHT35 *Sht35_45 = NULL;

extern "C" void hal_init_modem(void)
{
  if (Wio != NULL) return;

#if defined ARDUINO_WIO_LTE
  Wio = new WioLTE();
#else
  Wio = new WioCellular();
#endif

  Wio->Init();
}

extern "C" void hal_init_serial_usb(unsigned int speed)
{
  SerialUSB.begin(speed);
}

extern "C" void* hal_get_modem_obj(void)
{
  return (void*)Wio;
}

extern "C" void hal_write_string(char* text)
{
  SerialUSB.print(text);
}

extern "C" void hal_delay(unsigned long t)
{
  delay(t);
}

/****************************************************
 * BMP280
 ****************************************************/

extern "C" void hal_init_bmp280(unsigned char iic_addr)
{
  if (0x76 == iic_addr && Bmp280_76 != NULL) {
    Bmp280_76->init();
    return;
  }

  if (0x77 == iic_addr && Bmp280_77 != NULL) {
    Bmp280_77->init();
    return;
  }

  if (0x76 == iic_addr) {
    Bmp280_76 = new BMP280();
    if (Bmp280_76->init()) { Bmp280Enable_76 = 1; }
  }

  if (0x77 == iic_addr) {
    Bmp280_77 = new BMP280();
    if (Bmp280_77->init()) { Bmp280Enable_77 = 1; }
  }
}

extern "C" void* hal_get_bmp280_obj(unsigned char iic_addr)
{
  if (0x76 == iic_addr) {
    return (void*)Bmp280_76;
  }

  return (void*)Bmp280_77;

  DEBUG_PRINTLN("!!! BMP280: invalid iic_addr");

  char s[256] = {'\0'};
  sprintf(s, "iic_addr: %02x", (const unsigned char*)&iic_addr);
  DEBUG_PRINTLN(s);
}

extern "C" int hal_bmp280_is_enable(unsigned char iic_addr)
{
  if (0x76 == iic_addr) {
    return Bmp280Enable_76;
  }

  return Bmp280Enable_77;
  DEBUG_PRINTLN("! BMP280: invalid iic_addr");

  char s[256] = {'\0'};
  sprintf(s, "iic_addr: %02x", (const unsigned char*)&iic_addr);
  DEBUG_PRINTLN(s);
}

/****************************************************
 * SHT31
 ****************************************************/

extern "C" void hal_init_sht31(void)
{
  if (Sht31 != NULL) return;

  Sht31 = new SHT31();
  Sht31->begin();
}

extern "C" void* hal_get_sht31_obj(void)
{
  return (void*)Sht31;
}

/****************************************************
 * SHT35
 ****************************************************/

#define SHT35_SCLPIN  24

// iic_addr 0x45(default) or 0x44
extern "C" int hal_init_sht35(unsigned char iic_addr)
{
  if (iic_addr == 0x44 && Sht35_44 != NULL) {
    return Sht35_44->init();
  }

  if (iic_addr == 0x45 && Sht35_45 != NULL) { 
    return Sht35_45->init();
  }

  int ret = 0;

  if (0x44 == iic_addr) {
    Sht35_44 = new SHT35(SHT35_SCLPIN, iic_addr);
    ret = Sht35_44->init();
    if (NO_ERROR != ret) { Sht35_44 = NULL; }
    return ret;
  }

  if (0x45 == iic_addr) {
    Sht35_45 = new SHT35(SHT35_SCLPIN, iic_addr);
    ret = Sht35_45->init();
    if (NO_ERROR != ret) { Sht35_45 = NULL; }
    return ret;
  }

  DEBUG_PRINTLN("!!! SHT35: invalid iic_addr");

  char s[256] = {'\0'};
  sprintf(s, "iic_addr: %02x", (const unsigned char*)&iic_addr);
  DEBUG_PRINTLN(s);
  return ERROR_OTHERS;
}

extern "C" void* hal_get_sht35_obj(unsigned char iic_addr)
{
  if (0x44 == iic_addr) {
    return (void*)Sht35_44;
  }

  if (0x45 == iic_addr) {
    return (void*)Sht35_45;
  }

  DEBUG_PRINTLN("! SHT35: invalid iic_addr");

  char s[256] = {'\0'};
  sprintf(s, "iic_addr: %02x", (const unsigned char*)&iic_addr);
  DEBUG_PRINTLN(s);
  return NULL;
}
