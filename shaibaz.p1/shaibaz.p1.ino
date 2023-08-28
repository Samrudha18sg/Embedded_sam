 void setup()  
 {  
   Serial.begin(9600); // sensor buart rate  
   pinMode(D5,HIGH);  // Led Pin Connected To D5 Pin   
 }   
 void loop()   
 {  
  int s1=analogRead(A0); // IR Sensor output pin connected to A0  
  Serial.println(s1);  // See the Value In Serial Monitor     
  delay(100);  
  if(s1< 20 )  
  {  
   digitalWrite(D5,HIGH); // LED ON  
  }  
   else  
  {  
   digitalWrite(D5,LOW); // LED OFF  
  }  
 }  
