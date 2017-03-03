/*************************************************** 
  This is a library for the HTU21D-F Humidity & Temp Sensor

  Designed specifically to work with the HTU21D-F sensor from Adafruit
  ----> https://www.adafruit.com/products/1899

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"

#define HTU21DF_I2CADDR       0x40
#define HTU21DF_READTEMP      0xE3
#define HTU21DF_READHUM       0xE5
#define HTU21DF_WRITEREG       0xE6
#define HTU21DF_READREG       0xE7
#define HTU21DF_RESET       0xFE
#define HTU21DF_READHEATER  0x11
#define HTU21DF_WRITEHEATER  0x51

#define HTU21DR_BIT_HEADER 0b00000010


class Adafruit_HTU21DF {

 public:
  Adafruit_HTU21DF();
  boolean begin(void);

  float readTemperature(void);
  float readHumidity(void);
  bool readHeader(void);
  void reset(void);
  void setHeater(void);

 private:

  float humidity, temp;

  boolean readData(void);
  void write8(uint8_t register, uint8_t value);
  uint8_t read8(uint8_t register);
  uint16_t read16(uint16_t register);
};

