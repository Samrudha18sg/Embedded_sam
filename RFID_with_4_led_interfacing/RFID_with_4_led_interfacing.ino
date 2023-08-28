// RFID RC522   ----    Pin Wiring to Arduino Uno
//    SDA       ----          Digital 10
//    SCK       ----          Digital 13
//    MOSI      ----          Digital 11
//    MISO      ----          Digital 12
//    IRQ       ----          unconnected
//    GND       ----              GND
//    RST       ----           Digital 9
//    3.3V      ----             3.3V

#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  pinMode(2,OUTPUT); // LED 1 output pin 
  pinMode(3,OUTPUT); // LED 2 output pin
  pinMode(4,OUTPUT);  // LED 3 output pin
  pinMode(5,OUTPUT);  //LED 4 output pin
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "93 D5 1A 24") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(300);
    digitalWrite(2,HIGH); // Turn on LED 1 
    digitalWrite(3,HIGH); // Turn on LED 2 
    digitalWrite(4,HIGH); // Turn on LED 3 
    digitalWrite(5,HIGH);
  }
 
 else   {
    Serial.println(" Access denied");
    delay(300);
    digitalWrite(2,LOW); // Turn off LED 1 
    digitalWrite(3,LOW); // Turn off LED 2
    digitalWrite(4,LOW); // Turn off LED 3 
    digitalWrite(5,LOW); // Turn on LED 4 
}
}
