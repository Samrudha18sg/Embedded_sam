#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

int val = 0 ;  
 void setup()  
 {  
   Serial.begin(9600); // sensor buart rate  
   pinMode(D5,HIGH);  // Led Pin Connected To D5 Pin 
   lcd.init();
  lcd.clear();         
  lcd.backlight();  

   lcd.clear();
lcd.print("HELLO BROTHER ");
//lcd.print(LDR_output);
lcd.setCursor(1,2);
delay(1000);
 }  
 void loop()   
 {  
  val = digitalRead(D6); // IR Sensor output pin connected to D1  
  Serial.println(val);  // see the value in serial m0nitor in Arduino IDE  
  delay(100);      // for timer  
  if(val == 1 )  
  {  
   digitalWrite(D5,HIGH); // LED ON  
   lcd.clear();
lcd.print("AUTOMATION ON");
//lcd.println(ON);
lcd.setCursor(1,2);
delay(100);
  }  
  else  
  {  
   digitalWrite(D5,LOW); // LED OFF  
   lcd.clear();
lcd.print("AUTOMATION OFF");
//lcd.println(OFF);
lcd.setCursor(1,2);
delay(100);
  }  
  }  
