#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
 #include <WiFiClientSecure.h> 
 #include <Wire.h> 
 


const char* ssid = "IOT";
const char* password = "ELECSTARK";

int cloud=0;
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


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
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

}
int value =0;
void loop() {

int LDR_output=analogRead(A0);
Serial.print("LDR_output = ");
Serial.println(LDR_output);

delay(2000);         // wait for initializing
  display.clearDisplay(); // clear display
   display.setTextSize(1);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);        // position to display
  display.println("Hello World!"); // text to display
  display.display();
display.clearDisplay();
  display.setTextSize(1);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 20);        // position to display
  display.print("LDR_output = "); // text to display
  display.print( LDR_output);
  display.display();
//display.clearDisplay();
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
