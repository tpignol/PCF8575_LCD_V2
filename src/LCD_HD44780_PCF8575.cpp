
#include "LCD_HD44780_PCF8575.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
LCD_HD44780_PCF8575::LCD_HD44780_PCF8575(PCF8575& p,uint8_t rs,uint8_t en,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7):_pcf(p),_rs(rs),_en(en),_d4(d4),_d5(d5),_d6(d6),_d7(d7){memset(_buffer,' ',sizeof(_buffer));}
void LCD_HD44780_PCF8575::sendNibble(uint8_t n){uint16_t s=_pcf.getState(); auto b=[&](uint8_t p,bool v){if(v)s|=(1U<<p);else s&=~(1U<<p);}; b(_d4,n&1);b(_d5,n&2);b(_d6,n&4);b(_d7,n&8); _pcf.write16(s); _pcf.writeRaw(s|(1U<<_en)); _pcf.writeRaw(s&~(1U<<_en)); delayMicroseconds(50);}
void LCD_HD44780_PCF8575::sendByte(uint8_t v,bool rs){uint16_t s=_pcf.getState(); if(rs)s|=(1U<<_rs);else s&=~(1U<<_rs); _pcf.write16(s); sendNibble(v>>4); sendNibble(v&0x0F);}
void LCD_HD44780_PCF8575::command(uint8_t c){sendByte(c,false);}
bool LCD_HD44780_PCF8575::begin(uint8_t c,uint8_t r){_cols=c;_rows=r; delay(50); sendNibble(3);delay(20);sendNibble(3);delay(20);sendNibble(3);delay(20);sendNibble(2); command(0x28);command(0x0C);command(0x06);clear(); return true;}
size_t LCD_HD44780_PCF8575::write(uint8_t c){sendByte(c,true); return 1;}
void LCD_HD44780_PCF8575::clear(){command(0x01); delay(2);}
void LCD_HD44780_PCF8575::home(){command(0x02); delay(2);}
void LCD_HD44780_PCF8575::setCursor(uint8_t c,uint8_t r){static const uint8_t ro[]={0,0x40,0x14,0x54}; command(0x80|(ro[r]+c));}
void LCD_HD44780_PCF8575::printAt(uint8_t c,uint8_t r,const char* t){setCursor(c,r); print(t);}
void LCD_HD44780_PCF8575::printfAt(uint8_t c,uint8_t r,const char* fmt,...){char b[64]; va_list a; va_start(a,fmt); vsnprintf(b,sizeof(b),fmt,a); va_end(a); printAt(c,r,b);}
void LCD_HD44780_PCF8575::clearLine(uint8_t r){setCursor(0,r); for(uint8_t i=0;i<_cols;i++) write(' ');}
void LCD_HD44780_PCF8575::center(uint8_t r,const char* t){uint8_t l=strlen(t); uint8_t c=(l<_cols)?(_cols-l)/2:0; printAt(c,r,t);}
void LCD_HD44780_PCF8575::progressBar(uint8_t c,uint8_t r,uint8_t w,uint8_t p){setCursor(c,r); uint8_t f=(w*p)/100; for(uint8_t i=0;i<w;i++) write(i<f?255:' ');}
void LCD_HD44780_PCF8575::update(){}
