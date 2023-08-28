#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 #include <WiFiClientSecure.h> 
 
const char* ssid = "NUI";
const char* password = "lightyear";

int cloud=0;
int ledPin = D2;
int inputPin = D5;               // choose the input pin (for PIR sensor)
int pirState = LOW;  
void setup() {
  Serial.begin(115200);
   
  delay(10); 
  // We start by connecting to a WiFi network
   
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(ledPin,OUTPUT); 
  pinMode(inputPin,INPUT); 
}
int value = 0;
void loop() {
value = digitalRead(inputPin);  // read input value
  
  if (value == HIGH)  // check if the input is HIGH
  {            
    digitalWrite(ledPin, HIGH);  // turn LED ON
  delay(1000);
    //if (pirState == LOW) 
  {
      Serial.println("Motion detected"); // print on output change
     // pirState = LOW;
    }
  } 
  else 
  {
    digitalWrite(ledPin, LOW); // turn LED OFF
  delay(1000);
   // if (pirState == HIGH)
  {
      Serial.println("Motion ended");  // print on output change      Serial.println(inputPIN);
      //pirState = HIGH;
  }
}


 
WiFiClient client;
    HTTPClient http;
cloud=cloud+1;
 if(cloud>=20)
 {cloud=0; 
http.begin(client,"http://api.thingspeak.com/update?api_key=BII3NCOSDHE68LTO&field1="+ String(inputPin) ); //Replace API Key
        int httpCode = http.GET();
          if(httpCode > 0) {
               Serial.printf("[HTTP] GET... code: %d\n", httpCode);
               if(httpCode == HTTP_CODE_OK) {
                  String payload = http.getString();
                  Serial.println(payload);
              }
          } else {
              Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
          }
          http.end(); Serial.println();
  Serial.println("closing connection");
 }
delay(500);
}
