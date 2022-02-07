#include <WioLTEforArduino.h>
#include <WioLTEClient.h>
#include <Wire.h>

#include <string.h>
#include <SPI.h>
#include "SC16IS750.h"

WioCellular Wio;
SC16IS750 i2cuart = SC16IS750(SC16IS750_PROTOCOL_I2C,SC16IS750_ADDRESS_BB);

//Connect TX and RX with a wire and run this sketch

void setup() 
{
    Wio.Init();
    delay(500);
    Wio.PowerSupplyGrove(true);
    delay(500);
    
    SerialUSB.begin(115200);
    SerialUSB.println("Init OK");
    
    // UART to Serial Bridge Initialization
    i2cuart.begin(9600); //baudrate setting
    
    if (i2cuart.ping()!=1) {
        SerialUSB.println("device not found");
        while(1);
    } else {
        SerialUSB.println("device found");
    }
    
    SerialUSB.println("start serial communication");
};

char str_tmp;
void loop() 
{
    SerialUSB.print("set rts pin...");
    i2cuart.SetRtsPin(1);
    SerialUSB.println("done");

    delay(5);
    SerialUSB.print("sending modbus-rtu data......");
    //i2cuart.write(0x55);
    i2cuart.write(0x01); //Address
    i2cuart.write(0x04); //Function
    i2cuart.write(0x00); //開始アドレス（上位）
    i2cuart.write(0x01); //開始アドレス（下位）
    i2cuart.write(0x00); //レジスタ数　（上位）
    i2cuart.write(0x02); //レジスタ数　（下位）
    i2cuart.write(0x20); //CRC（上位）
    i2cuart.write(0x0b); //CRC（下位）

    //unsigned char buff[] = {0x01, 0x03, 0x00, 0x00, 0x00, 0x03};
    //unsigned short crc = calc_crc(buff, 6);
    //i2cuart.write((crc >> 8));   //CRC（上位）    
    //i2cuart.write((crc & 0x0F)); //CRC（下位）    
    
    delay(5);
    i2cuart.SetRtsPin(0);
    SerialUSB.println("done");
    
    while(i2cuart.available()==0);
    SerialUSB.print("Data:");

    SerialUSB.print("available: ");
    SerialUSB.println(i2cuart.available());
    
    while(i2cuart.available() > 0)
    {
      str_tmp=i2cuart.read();
      SerialUSB.print("data: ");
      SerialUSB.println((uint8_t)str_tmp);
      //SerialUSB.print(" ");
    }

    SerialUSB.println("");
    SerialUSB.println("--------------Read finish---------------");
    delay(3000);
};

// buf    受信データ
// length 受信データ長(CRCを除く)
unsigned short calc_crc(unsigned char *buf, int length) {
  unsigned short crc = 0xFFFF;
  int i,j;
  unsigned char carrayFlag;
  for (i = 0; i < length; i++) {
    crc ^= buf[i];
    for (j = 0; j < 8; j++) {
      carrayFlag = crc & 1;
      crc = crc >> 1;
      if (carrayFlag) {
        crc ^= 0xA001;
      }
    }
  }
  return crc;
}
