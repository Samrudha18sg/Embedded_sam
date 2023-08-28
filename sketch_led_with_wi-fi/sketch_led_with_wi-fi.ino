#include <ESP8266WiFi.h> 
 
const char* ssid ="NUI";
const char* pwd = "lightyear";
int ledPin1 = D2;
  
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
     
  } 
  if (request.indexOf("/OFF") != -1) // Rev
  {
       digitalWrite(ledPin1, LOW);
        
    Serial.println("OFF LED");
       
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
