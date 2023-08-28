#include <ESP8266WiFi.h> 
 #include <Wire.h> 
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using I2C
#define OLED_RESET     -1 // Reset pin
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


const char* ssid ="IOT";
const char* pwd = "ELECSTARK";
int ledPin1 = D6;
  
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200); 
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1, LOW); 
   
   
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, pwd); 
 

    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    
  }
  Serial.println("");
  Serial.println("WiFi connected");
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());//nodemcu 
  Serial.println("/");
 if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer.
  display.clearDisplay();

 
}
 
void loop() {
    
  WiFiClient client = server.available();
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
    client.flush();
 
  // Match the request
 
  //int value = LOW;
  if (request.indexOf("/ON") != -1) //Forward 
  {
    digitalWrite(ledPin1, HIGH);
    
    Serial.println("ON LED");
    display.clearDisplay(); // clear display
   display.setTextSize(1);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);        // position to display
  display.println("ON LED"); // text to display
  display.display();

  } 
  if (request.indexOf("/OFF") != -1) // Rev
  {
       digitalWrite(ledPin1, LOW);
        
    Serial.println("OFF LED");
    display.clearDisplay(); // clear display
   display.setTextSize(1);          // text size
  display.setTextColor(WHITE);     // text color
  display.setCursor(0, 10);        // position to display
  display.println("OFF LED"); // text to display
  display.display();  
  }
  
  
   
   

   
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
            
             
  client.print(" <h1> One LED ON OFF </h1> ");
  
    client.println("<p><a href=\"/ON\"><button class=\"button\"> ON</button></a></p>");
            client.print("<p><a href=\"/OFF\"><button class=\"button\">OFF</button></a></p>");
  
   client.println("<html>");
 
   
  delay(100);
  
  Serial.println("");
}
