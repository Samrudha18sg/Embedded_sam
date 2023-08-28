#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h> 
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

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
  pinMode(A0,INPUT); 
  lcd.init();                      
lcd.init();
lcd.backlight(); 
}
int value = 0;
void loop() {

int soil_sensor_output=analogRead(A0);
Serial.print("soil_sensor = ");
Serial.println(soil_sensor_output);
lcd.clear();
 lcd.print("soil_sensor=");
 lcd.print(soil_sensor_output);
  lcd.setCursor(2,1);
WiFiClient client;
    HTTPClient http;
 cloud=cloud+1;
 if(cloud>=20)
 {cloud=0; 
http.begin(client,"http://api.thingspeak.com/update?api_key=467JJN2379Z696OO&field1="+ String(soil_sensor_output) ); //Replace API Key
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
