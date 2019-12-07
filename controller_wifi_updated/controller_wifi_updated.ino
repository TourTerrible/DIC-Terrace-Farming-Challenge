
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
 
//SSID and Password to your ESP Access Point
const char* ssid = "DIC_IITG";
const char* password = "12345678";





const char INDEX_HTML[] =
"<!DOCTYPE html>"
"<html>"
"<head>"
    "<meta name = \"viewport\" content = \"width = device-width, initial-scale = 1.0, maximum-scale = 1.0, user-scalable=0\">"
    "<title>DIC Control</title>"
"<style>"
    "input[type=submit] {"
      "background-color:  #e7e7e7;"
      "padding: 10px 2px;"
      "font-size: 15px;"
      "border: 2px solid #555555;"
      "border-radius: 4px;"
      "cursor: pointer;"
      "width:100px;"
      "text-align: center;"
    "}"
    "input[value=Stop] {"
     "color: #f44336;"
     "font-size: 20px;"
    "}"
    "input[value=Start] {"
     "color:  #4CAF50;"
     "font-size: 20px;"
    "}"
    

     
     ".container{"
        "padding-left:10px;"
        "padding-top: 10px;"
        "display: grid;"
        "grid-template-columns: 1fr 1fr;"
        "grid-column-gap: 18vh;"
     "}"
     ".container2{"
        "padding-left:15px;"
        "display: grid;"
        "grid-template-columns: 1fr 1fr 1fr;"
        "grid-row-gap: 10px;"
        "margin-top: 30vh;"
     "}"
     ".container3{"
        "padding-left:15px;"
        "padding-top:15px;"
        "display: grid;"
        "grid-template-columns: 1fr 1fr 1fr;"
        "grid-row-gap: 10px;"
        
     "}"


    
"</style>"
"</head>"
"<body>"
"<div class = \"container\">"


"<form action=\"/start\" method=\"POST\">"
  "<input type=\"submit\" value=\"Start\">"
"</form>"

"<form action=\"/stop\" method=\"POST\">"
  "<input type=\"submit\" value=\"Stop\">"
"</form>"



"</div>"


"<div class = \"container2\">"


"<form action=\"/pump\" method=\"POST\">"
  "<input type=\"submit\" value=\"Pump\">"
"</form>"

"<form action=\"/side\" method=\"POST\">"
  "<input type=\"submit\" value=\"Side\">"
"</form>"
"<form action=\"/center\" method=\"POST\">"
  "<input type=\"submit\" value=\"Center\">"
"</form>"
"</div>"

"</div>"

"<div class = \"container3\">"


"<form action=\"/seeding\" method=\"POST\">"
  "<input type=\"submit\" value=\"Seeding\">"
"</form>"

"<form action=\"/ploughing\" method=\"POST\">"
  "<input type=\"submit\" value=\"Ploughing\">"
"</form>"
"<form action=\"/harvesting\" method=\"POST\">"
  "<input type=\"submit\" value=\"Harvesting\">"
"</form>"
"</div>"





"</body>"



"</html>";

 
ESP8266WebServer server(80); //Server on port 80
 
//==============================================================

//==============================================================
void handleRoot() {                         // When URI / is requested, send a web page with a button to toggle the LED
  server.send(200,"text/html",INDEX_HTML);
 
  
  
}



 
//===============================================================
//                  SETUP
//===============================================================
void setup(void){
  Serial.begin(9600);
  Serial.println("");
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password);
 

IPAddress ip(192, 168, 0, 50); // this 3 lines for a fix IP-address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
WiFi.config(ip, gateway, subnet); // before or after Wifi.Begin(ssid, password);
  
 
  IPAddress myIP = WiFi.softAPIP(); //Get IP address
  Serial.print("HotSpt IP:");
  Serial.println(ip);
 
  server.on("/", HTTP_GET, handleRoot);     // Call the 'handleRoot' function when a client requests URI "/"
  
 
  server.begin();                
  Serial.println("HTTP server started");
}
//===============================================================
//                     LOOP
//===============================================================
void loop(void){
  server.handleClient();          
}
