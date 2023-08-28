#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 #include <WiFiClientSecure.h> 
 
const char* ssid = "NUI";
const char* password = "lightyear";

int cloud=0;

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
  pinMode(A0,INPUT); // LDR analog pin out 
}
int value = 0;
void loop() {

int LDR_output=analogRead(A0);
Serial.print("LDR output = ");
Serial.println(LDR_output);
 
WiFiClient client;
    HTTPClient http;
 cloud=cloud+1;
 if(cloud>=20)
 {cloud=0; 
http.begin(client,"http://samssg85.000webhostapp.com/aad1.php?ldr_output="+ String(LDR_output) ); //Replace API Key
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
