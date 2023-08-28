#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x3F,16,2);  

void setup() {
 
  lcd.init();
  lcd.clear();         
  lcd.backlight();     

}

void loop() {

lcd.setCursor(0,0);   
  lcd.print("HIMANSHU");
  
  lcd.setCursor(2,1);  
  lcd.print("LOHAKARE");
}
