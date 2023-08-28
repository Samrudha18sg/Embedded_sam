#include <ESP8266WiFi.h> 
 
const char* ssid ="NUI";
const char* pwd = "lightyear";
int ledPin1= D2;
int ledPin2= D3;
WiFiServer server(80);  

 void setup() {
  Serial.begin(9600); 
  pinMode(ledPin1, OUTPUT);
  digitalWrite(ledPin1,LOW);
  pinMode(ledPin2, OUTPUT); 
  digitalWrite(ledPin2,LOW); 
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
 void loop() 
 {
    WiFiClient client = server.available();
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  //int value = LOW;
  if (request.indexOf("/LED1_ON") != -1) //Forward 
  {
    digitalWrite(ledPin1, HIGH);
    
    Serial.println("ON LED");
     
  } 
  if (request.indexOf("/LED2_ON") != -1) //Forward 
  {
    digitalWrite(ledPin2, HIGH);
    
    Serial.println("ON LED"); 
  }
     
  if (request.indexOf("/LED1_OFF") != -1) // Rev
  {
       digitalWrite(ledPin1, LOW);
                     
    Serial.println("OFF LED");
       
  }   
  if (request.indexOf("/LED2_OFF") != -1) // Rev
  {
       digitalWrite(ledPin2, LOW);
                     
    Serial.println("OFF LED");
    }    
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
            
             
  client.print(" <h1> IoT Based Project </h1> ");
  
    client.println("<p><a href=\"/LED1_ON\"><button class=\"button\"> ON LED1_ON</button></a></p>");
            client.print("<p><a href=\"/LED1_OFF\"><button class=\"button\">OFF LED1_OFF</button></a></p>");
  client.println("<p><a href=\"/LED2_ON\"><button class=\"button\"> ON LED2_ON</button></a></p>");
            client.print("<p><a href=\"/LED2_OFF\"><button class=\"button\">OFF LED2_OFF</button></a></p>");
  
   client.println("<html>");
 
   
  delay(100);
  
  Serial.println("");
 
}
