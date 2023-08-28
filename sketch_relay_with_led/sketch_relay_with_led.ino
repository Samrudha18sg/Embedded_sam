
 void setup()
 {
 pinMode(D5,OUTPUT); // put your setup code here, to run onc
 pinMode(D3,OUTPUT);
}

void loop() {
 digitalWrite(D5,HIGH);// put your main code here, to run repeatedly:
 digitalWrite(D3,LOW);                  
delay(5000);
digitalWrite(D5,LOW);
digitalWrite(D3,HIGH);
delay(5000);
}
