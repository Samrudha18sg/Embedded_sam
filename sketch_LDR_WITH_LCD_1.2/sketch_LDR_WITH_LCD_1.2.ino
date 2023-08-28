#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 #include <WiFiClientSecure.h> 
 #include <Wire.h> 
 
LiquidCrystal_I2C lcd(0x3F,20,4);

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
  lcd.init();
  lcd.clear();         
  lcd.backlight();
}
int value = 0;
void loop() {

int LDR_output=analogRead(A0);
Serial.print("LDR output = ");
Serial.println(LDR_output);

lcd.clear();
//lcd.print("LDR_output: ");
//lcd.print(LDR_output);
//lcd.setCursor(0,2);
lcd.print("LDR_out: ");
lcd.print(LDR_output);
lcd.setCursor(2,1);
WiFiClient client;
    HTTPClient http;
 cloud=cloud+1;
 if(cloud>=20)
 {cloud=0; 
http.begin(client,"http://api.thingspeak.com/update?api_key=9QYF521BQ7GWNE13&field1="+ String(LDR_output) ); //Replace API Key
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
