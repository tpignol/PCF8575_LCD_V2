#include "Keypad_PCF8575.h"
Keypad_PCF8575* Keypad_PCF8575::_instance=nullptr;

Keypad_PCF8575::Keypad_PCF8575(PCF8575& pcf,const uint8_t* rows,uint8_t rowCount,
const uint8_t* cols,uint8_t colCount,const char* keymap)
:_pcf(pcf),_rows(rows),_cols(cols),_rowCount(rowCount),_colCount(colCount),
_keymap(keymap),
_debounceMs(50),
_lastRead(0),
_intFlag(false),
_intPin(255),
_lastKey(0),
_keyPressed(false){}

bool Keypad_PCF8575::begin(){
 for(uint8_t r=0;r<_rowCount;r++) _pcf.digitalWrite(_rows[r],HIGH);
 for(uint8_t c=0;c<_colCount;c++) _pcf.digitalWrite(_cols[c],HIGH);
 return true;
}
void Keypad_PCF8575::setKeyMap(const char* keymap){_keymap=keymap;}
void Keypad_PCF8575::setDebounce(uint16_t ms){_debounceMs=ms;}
void Keypad_PCF8575::isrHandler(){ if(_instance) _instance->_intFlag=true; }
void Keypad_PCF8575::enableInterrupt(uint8_t intPin){
 _intPin=intPin; pinMode(intPin,INPUT_PULLUP); _instance=this;
 attachInterrupt(digitalPinToInterrupt(intPin),isrHandler,FALLING);
}
bool Keypad_PCF8575::interruptTriggered(){return _intFlag;}
bool Keypad_PCF8575::available(){
 if(_intPin!=255 && !_intFlag) return false;
 if(millis()-_lastRead<_debounceMs) return false;
 char k=scan(); if(k) return true; _intFlag=false; return false;
}
char Keypad_PCF8575::read(){ _lastRead=millis(); char k=scan(); _intFlag=false; return k; }
char Keypad_PCF8575::getKey()
{
    if(millis() - _lastRead < _debounceMs)
        return 0;

    _lastRead = millis();

    char current = scan();

    // Nouveau front d'appui
    if(current && !_keyPressed)
    {
        _keyPressed = true;
        _lastKey = current;

        _intFlag = false;

        return current;
    }

    // Touche relâchée
    if(!current)
    {
        _keyPressed = false;
        _lastKey = 0;
        _intFlag = false;
    }

    return 0;
}

char Keypad_PCF8575::scan(){
 uint16_t base=_pcf.getState();
 for(uint8_t r=0;r<_rowCount;r++){
   uint16_t state=base;
   for(uint8_t i=0;i<_rowCount;i++) state|=(1U<<_rows[i]);
   state&=~(1U<<_rows[r]);
   _pcf.write16(state);
   delayMicroseconds(50);
   uint16_t in=_pcf.read16();
   for(uint8_t c=0;c<_colCount;c++){
      if(!(in & (1U<<_cols[c]))){
        return _keymap ? _keymap[r*_colCount+c] : 1;
      }
   }
 }
 _pcf.write16(base);
 return 0;
}
