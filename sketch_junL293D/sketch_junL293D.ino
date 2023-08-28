// C++ code
//
void setup()
{
 pinMode(2,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(6,INPUT_PULLUP);
    

}

void loop()
{
 
  
  
  
  
 
 int x= digitalRead(6);
  if(x==0)
  {
     digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
    digitalWrite(4,HIGH);
    digitalWrite(5,LOW);
  }
  else
  {
    digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
    digitalWrite(4,LOW);
    digitalWrite(5,HIGH);
  }
  
  
  
}
