
#include <Wire.h>
#include <PCF8575.h>
#include <LCD_HD44780_PCF8575.h>

PCF8575 pcf(0x20);
LCD_HD44780_PCF8575 lcd(pcf);

void setup(){
 Wire.begin(21,22);
 if(!pcf.begin()) while(true);
 lcd.begin(20,4);

 pcf.digitalWrite(8,false);
 pcf.digitalWrite(11,true);

 lcd.center(0,"TABLEAU DE BORD");
 lcd.printfAt(0,1,"Temp %.1fC",24.5);
 lcd.printfAt(0,2,"Pompe ON");
 for (int p = 0; p <= 100; p += 5) {
    lcd.progressBar(0, 3, 20, p);
    delay(200);
}



}
void loop(){

 

}
