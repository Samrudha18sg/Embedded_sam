void setup()
{
  pinMode(5, OUTPUT);
}

void loop()
{
  digitalWrite(5, LOW);
  delay(2000); // Wait for 1000 millisecond(s)
  digitalWrite(5, HIGH);
  delay(2000); // Wait for 1000 millisecond(s)
}
