
#ifndef LCD_HD44780_PCF8575_H
#define LCD_HD44780_PCF8575_H
#include <Print.h>
#include "PCF8575.h"
class LCD_HD44780_PCF8575: public Print{
public:
 LCD_HD44780_PCF8575(PCF8575& pcf,uint8_t rs=0,uint8_t en=1,uint8_t d4=2,uint8_t d5=3,uint8_t d6=4,uint8_t d7=5);
 bool begin(uint8_t cols=20,uint8_t rows=4);
 size_t write(uint8_t c) override;
 void clear(); void home(); void setCursor(uint8_t col,uint8_t row);
 void printAt(uint8_t col,uint8_t row,const char* txt);
 void printfAt(uint8_t col,uint8_t row,const char* fmt,...);
 void clearLine(uint8_t row);
 void center(uint8_t row,const char* txt);
 void progressBar(uint8_t col,uint8_t row,uint8_t width,uint8_t percent);
 void update();
private:
 PCF8575& _pcf; uint8_t _rs,_en,_d4,_d5,_d6,_d7,_cols,_rows;
 char _buffer[4][21];
 void command(uint8_t c); void sendByte(uint8_t v,bool rs); void sendNibble(uint8_t n);
};
#endif
