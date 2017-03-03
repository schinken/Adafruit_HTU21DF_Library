/*************************************************** 
  This is a library for the HTU21DF Humidity & Temp Sensor

  Designed specifically to work with the HTU21DF sensor from Adafruit
  ----> https://www.adafruit.com/products/1899

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_HTU21DF.h"
#if defined(__AVR__)
#include <util/delay.h>
#endif

Adafruit_HTU21DF::Adafruit_HTU21DF() {
}


boolean Adafruit_HTU21DF::begin(void) {
  Wire.begin();
  
  reset();

  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READREG);
  Wire.endTransmission();
  Wire.requestFrom(HTU21DF_I2CADDR, 1);
  return (Wire.read() == 0x2); // after reset should be 0x2
}

void Adafruit_HTU21DF::reset(void) {
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_RESET);
  Wire.endTransmission();
  delay(15);
}


float Adafruit_HTU21DF::readTemperature(void) {
  float temp = read16(HTU21DF_READTEMP);

  temp *= 175.72;
  temp /= 65536;
  temp -= 46.85;

  return temp;
}
  

float Adafruit_HTU21DF::readHumidity(void) {
  float hum = read16(HTU21DF_READHUM);
  hum *= 125;
  hum /= 65536;
  hum -= 6;

  return hum;
}

bool Adafruit_HTU21DF::readHeater(void) {
  uint8_t userRegister = read8(HTU21DF_READREG);
  return (userRegister & HTU21DR_BIT_HEADER);
}

void Adafruit_HTU21DF::setHeater(bool on) {
  uint8_t userRegister = read8(HTU21DF_READREG);

  if (on) {
    userRegister |= HTU21DR_BIT_HEADER;
  } else {
    userRegister &= ~HTU21DR_BIT_HEADER;
  }

  write8(HTU21DF_WRITEREG, userRegister);
}


/*********************************************************************/

void Adafruit_HTU21DF::write8(uint8_t register, uint8_t value) {
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READREG);
  delay(50);

  Wire.write(register);
  Wire.write(value);

  Wire.endTransmission();
}

uint8_t Adafruit_HTU21DF::read8(uint8_t register) {
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READREG);
  delay(50);

  Wire.write(register);
  Wire.endTransmission();

  Wire.requestFrom(HTU21DF_I2CADDR, 1);

  return Wire.read();
}

uint16_t Adafruit_HTU21DF::read16(uint16_t register) {
  Wire.beginTransmission(HTU21DF_I2CADDR);
  Wire.write(HTU21DF_READREG);
  delay(50);

  Wire.write(register);
  Wire.endTransmission();
  Wire.requestFrom(HTU21DF_I2CADDR, 2);

  uint16_t tmp = Wire.read();
  tmp <<= 8;
  tmp |= Wire.read();

  return h;
}
