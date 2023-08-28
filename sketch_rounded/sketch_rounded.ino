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
  <!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>
.button {
  border: none;
  color: white;
  padding: 20px;
  text-align: center;
  text-decoration: none;
  display: inline-block;
  font-size: 16px;
  margin: 4px 2px;
  cursor: pointer;
}

.button1 {border-radius: 2px;}
.button2 {border-radius: 4px;}
.button3 {border-radius: 8px;}
.button4 {border-radius: 12px;}
.button5 {border-radius: 50%;}
</style>
</head>
<body>

<h2>Rounded Buttons</h2>
<p>Add rounded corners to a button with the border-radius property:</p>

<button class="button button1">2px</button>
<button class="button button2">4px</button>
<button class="button button3">8px</button>
<button class="button button4">12px</button>
<button class="button button5">50%</button>

</body>
</html>

    client.println("<p><a href=\"/ON\"><button class=\"button\"> ON</button></a></p>");
            client.print("<p><a href=\"/OFF\"><button class=\"button\">OFF</button></a></p>");
  
   client.println("<html>");
 
   
  delay(100);
  
  Serial.println("");
}
