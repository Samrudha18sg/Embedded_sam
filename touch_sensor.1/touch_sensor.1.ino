const int SENSOR_PIN =D1; // the Arduino's input pin that connects to the sensor's SIGNAL pin 

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the Arduino's pin as aninput
  pinMode(SENSOR_PIN, INPUT);
  pinMode(D6,OUTPUT);
}

void loop() {
  // read the state of the the input pin:
  int state = digitalRead(SENSOR_PIN); 
if(state==HIGH)
{
  digitalWrite(D6,HIGH);
 
}
  else
  {
    digitalWrite(D6,LOW);
  }

  // print state to Serial Monitor
  Serial.println(state);
}
