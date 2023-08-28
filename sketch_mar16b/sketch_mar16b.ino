#include <Servo.h>
Servo motor1;
void setup()
{
  motor1.attach(7);
  
}

void loop()
  {
  
  
  motor1.write(10);
  
  delay(1000); // Wait for 1000 millisecond(s)
    
  motor1.write(100);
    
  delay(1000); // Wait for 1000 millisecond(s)
}
