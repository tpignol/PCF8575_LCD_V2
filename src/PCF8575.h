
#ifndef PCF8575_H
#define PCF8575_H
#include <Arduino.h>
#include <Wire.h>
class PCF8575{
public:
 explicit PCF8575(uint8_t address, TwoWire& wire=Wire);
 bool begin(); bool isConnected();
 void digitalWrite(uint8_t pin,bool value);
 bool digitalRead(uint8_t pin);
 void toggle(uint8_t pin);
 void write16(uint16_t value);
 void writeRaw(uint16_t value);
 uint16_t read16();
 uint16_t getState() const;
 void setBits(uint16_t mask);
 void clearBits(uint16_t mask);
 static uint8_t scan(TwoWire& wire=Wire);
private:
 uint8_t _address; TwoWire* _wire; uint16_t _state;
 void flush();
};
#endif
