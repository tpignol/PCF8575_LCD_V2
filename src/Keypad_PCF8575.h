#ifndef KEYPAD_PCF8575_H
#define KEYPAD_PCF8575_H
#include <Arduino.h>
#include "PCF8575.h"

class Keypad_PCF8575 {
public:
    Keypad_PCF8575(PCF8575& pcf,const uint8_t* rows,uint8_t rowCount,
                   const uint8_t* cols,uint8_t colCount,const char* keymap=nullptr);

    bool begin();
    void setKeyMap(const char* keymap);
    void setDebounce(uint16_t ms);

    char getKey();
    bool available();
    char read();

    void enableInterrupt(uint8_t intPin);
    bool interruptTriggered();

private:
    PCF8575& _pcf;
    const uint8_t* _rows;
    const uint8_t* _cols;
    uint8_t _rowCount,_colCount;
    const char* _keymap;
    uint16_t _debounceMs;
    uint32_t _lastRead;
    volatile bool _intFlag;
    uint8_t _intPin;

    char scan();
    static Keypad_PCF8575* _instance;
    static void isrHandler();
	
	char _lastKey;
	bool _keyPressed;
};
#endif
