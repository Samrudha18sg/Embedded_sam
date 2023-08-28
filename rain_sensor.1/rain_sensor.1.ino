const int RAIN_SENSOR_PIN = D2;
const int buzzer = D6;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // initialize the Arduino's pin as aninput
  pinMode(RAIN_SENSOR_PIN, INPUT);
  pinMode(D6,OUTPUT);
}

void loop() {
  // read the state of the the input pin:
  int state = digitalRead(RAIN_SENSOR_PIN);

  if (state == HIGH){
  digitalWrite(D6,HIGH);
    Serial.println("The rain is present");
  }
  else
  { digitalWrite(D6,LOW);
    Serial.println("The rain is NOT present");
  }
  delay(100);
}
