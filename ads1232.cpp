#include <Arduino.h>
#include "ads1232.h"

#define DOUT_MODE INPUT_PULLUP
#define TWAIT 20

ads1232::ads1232() {}

void ads1232::init(byte pin_DOUT, byte pin_SCLK, byte pin_PDWN){
  _pin_DOUT = pin_DOUT;
  _pin_SCLK = pin_SCLK;
  _pin_PDWN = pin_PDWN;
  //_pin_SPEED = pin_SPEED;

  pinMode(_pin_DOUT, DOUT_MODE);
  pinMode(_pin_SCLK, OUTPUT);
  pinMode(_pin_PDWN, OUTPUT);
  //pinMode(_pin_SPEED, OUTPUT);

  power_up();
}

bool ads1232::is_ready(void) {return digitalRead(_pin_DOUT) == LOW;}

void ads1232::power_up(void) {
  digitalWrite(_pin_PDWN, HIGH);
  delayMicroseconds(10);
  digitalWrite(_pin_SCLK, LOW);
  delayMicroseconds(10);
}

void ads1232::power_down(void) {
  digitalWrite(_pin_PDWN, LOW);
  delayMicroseconds(10);
  digitalWrite(_pin_SCLK, HIGH);
  delayMicroseconds(10);
}

int32_t ads1232::read() {    
  
  uint16_t wait_millis=100;   
  uint32_t data=0;

  for (; data < wait_millis && digitalRead(_pin_DOUT) != LOW; delay(1), data++);
  if (data == wait_millis) {return -1;}  // timeout

  data = 0;
  for (uint8_t i = 0; i < 24; i++) {
    digitalWrite(_pin_SCLK, HIGH); // clock out next data bit
    data <<= 1;
    data |= digitalRead(_pin_DOUT);
    digitalWrite(_pin_SCLK, LOW);
  }

  if (data & 0x00800000) data |= 0xFF000000;
  digitalWrite(_pin_SCLK, HIGH);
  delayMicroseconds(10);
  digitalWrite(_pin_SCLK, LOW);

  return data;
}
