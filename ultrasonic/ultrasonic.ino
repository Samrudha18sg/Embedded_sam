#include <UltrasonicSensor.h>

#include <HCSR04.h>

int buzzer = 9;
 
#include <Ultrasonic.h>
 
Ultrasonic ultrasonic(8,7);
 
void setup() {
Serial.begin(9600);
pinMode(buzzer,OUTPUT);

}
 
void loop()
{
 
int distance=ultrasonic Ranging(cm);
if (distance<50)
{
int dil = 2*distance;
 
digitalWrite(buzzer,HIGH);
delay(100);
}
{
else
digitalWrite(buzzer,LOW);
delay(1000);
}
}
