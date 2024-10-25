#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

const char *ssid = "IoT518";
const char *password = "iot123456";
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available(); 
  if (client) {                           
    Serial.println("New Client.");        
    String currentLine = "";             
    while (client.connected()) {         
      if (client.available()) {         
        char c = client.read();          
        Serial.write(c);                  
        if (c == '\n') {                  

          if (currentLine.length() == 0) {
           
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            
            client.print("Click <a href=\"/H\">here</a> to turn ON the LED.<br>");
            client.print("Click <a href=\"/L\">here</a> to turn OFF the LED.<br>");

            
            client.println();
            
            break;
          } else {    
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;      
        }

       
        if (currentLine.endsWith("GET /H")) {
          Serial.println("HIGH");
          }
        if (currentLine.endsWith("GET /L")) {
          Serial.println("LOW");
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
