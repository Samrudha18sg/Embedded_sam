void setup(){
 Serial.begin(9600); 
  pinMode(5, INPUT);
}
  
void loop() {
int Sound_val=analogRead(A0);

 if (Sound_val>700){ 
  Serial.println(Sound_val);
  Serial.println("Mic is on"); 
   delay (500);
    }
    else  
    {
       Serial.println(Sound_val);
  Serial.println("Mic is off"); 
delay(500);
 }
}
