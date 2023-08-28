#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 #include <WiFiClientSecure.h> 
#include <DHT.h>

  
const char* ssid = "NUI";
const char* password = "lightyear";

 
#define DHTPIN D5
#define DHTTYPE DHT11 
 
 int cloud=0;
 
 
DHT dht(DHTPIN, DHTTYPE);
 void setup() {
  Serial.begin(115200);
   
  delay(10);
dht.begin();
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
}

int value = 0;

void loop() {
  float h = dht.readHumidity();
float t = dht.readTemperature();
Serial.print("temp=");
Serial.print(t);
Serial.print("Hum=");
Serial.println(h);

if (isnan(h) || isnan(t)) 
{
Serial.println("Failed to read from DHT sensor!");
return;
}
WiFiClient client;
    HTTPClient http;
 cloud=cloud+1;
 if(cloud>=20)
 {cloud=0;
 //http://api.thingspeak.com/update?api_key=YOUR API KEY&field1=
http.begin(client,"http://api.thingspeak.com/update?api_key=1HM0EAYQ00AZMS8E&field1="+ String(t) +"&field2="+ String(h)); 
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
