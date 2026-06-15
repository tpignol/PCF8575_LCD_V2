
#include "PCF8575.h"
PCF8575::PCF8575(uint8_t a,TwoWire& w):_address(a),_wire(&w),_state(0){}
bool PCF8575::isConnected(){_wire->beginTransmission(_address);return _wire->endTransmission()==0;}
bool PCF8575::begin(){if(!isConnected()) return false; flush(); delay(10); return true;}
void PCF8575::flush(){_wire->beginTransmission(_address);_wire->write(_state&0xFF);_wire->write((_state>>8)&0xFF);_wire->endTransmission();}
void PCF8575::digitalWrite(uint8_t p,bool v){if(v)_state|=(1U<<p);else _state&=~(1U<<p);flush();}
bool PCF8575::digitalRead(uint8_t p){return read16()&(1U<<p);}
void PCF8575::toggle(uint8_t p){_state^=(1U<<p);flush();}
void PCF8575::write16(uint16_t v){_state=v;flush();}
void PCF8575::writeRaw(uint16_t v){_wire->beginTransmission(_address);_wire->write(v&0xFF);_wire->write((v>>8)&0xFF);_wire->endTransmission();}
uint16_t PCF8575::read16(){_wire->requestFrom((int)_address,2);uint16_t v=0;if(_wire->available()>=2){v=_wire->read();v|=((uint16_t)_wire->read())<<8;}return v;}
uint16_t PCF8575::getState() const{return _state;}
void PCF8575::setBits(uint16_t m){_state|=m;flush();}
void PCF8575::clearBits(uint16_t m){_state&=~m;flush();}
uint8_t PCF8575::scan(TwoWire& wire){for(uint8_t a=0x20;a<=0x27;a++){wire.beginTransmission(a);if(wire.endTransmission()==0)return a;}return 0;}
