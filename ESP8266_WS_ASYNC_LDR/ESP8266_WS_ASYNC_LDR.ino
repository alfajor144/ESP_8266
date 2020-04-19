#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "index.h"

AsyncWebServer server(80);

const char* ssid     = "El nombre de tu red wifi";
const char* password = "El password de tu red wifi";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
void setup() {
  Serial.begin(115200);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  //-------Pagina principal---------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200,  "text/html", MAIN_page);
  });

  //------------Envío de datos al cliente----------------
  server.on("/readSensors", HTTP_GET, [](AsyncWebServerRequest *request){

   int alg = analogRead(A0); 
   
   String potes_Json = "{\"h\":\"" + String(alg)+"\"}";
   
   request->send(200, "application/json", potes_Json); 
                            
  });
  
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
}
