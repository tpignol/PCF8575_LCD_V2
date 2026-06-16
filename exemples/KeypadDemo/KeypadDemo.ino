#include <Wire.h>
#include <PCF8575.h>
#include <LCD_HD44780_PCF8575.h>
#include "Keypad_PCF8575.h"

PCF8575 pcf(0x20);
LCD_HD44780_PCF8575 lcd(pcf);

uint8_t rows[]={6,7,8,9};
uint8_t cols[]={10,11,12};

const char keys[]={
'1','2','3',
'4','5','6',
'7','8','9',
'*','0','#'
};

Keypad_PCF8575 keypad(pcf,rows,4,cols,3,keys);

void setup(){
 Wire.begin();
 pcf.begin();
 lcd.begin(20,4);
 keypad.begin();

 //keypad.enableInterrupt(4);
 lcd.printAt(0,0,"Clavier pret");
}

void loop(){
    
    char key = keypad.getKey();

    if(key)
    {
        lcd.print(key);
    }
}
