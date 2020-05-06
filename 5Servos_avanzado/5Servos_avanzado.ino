#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Servo.h>
#include "index.h"

Servo servo1, servo2, servo3, servo4, servo5;

AsyncWebServer server(80);

const char* ssid     = "REDCASA";
const char* password = "091088411";

const int GPIO4 = 4;
const int GPIO5 = 5;
const int GPIO12 = 12;
const int GPIO13 = 13;
const int GPIO14 = 14;

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

  servo1.attach(GPIO4);
  servo2.attach(GPIO5);
  servo3.attach(GPIO12);
  servo4.attach(GPIO13);
  servo5.attach(GPIO14);

  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);

  //-------Pagina principal---------------
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200,  "text/html", MAIN_page);
  });

  //------------Resepcion de datos del cliente (SLIDERS)---------------
  server.on("/set", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String pos1 = request->arg("pos1");
    servo1.write(pos1.toInt());

    String pos2 = request->arg("pos2");
    servo2.write(pos2.toInt());

    String pos3 = request->arg("pos3");
    servo3.write(pos3.toInt());

    String pos4 = request->arg("pos4");
    servo4.write(pos4.toInt());

    String pos5 = request->arg("pos5");
    servo5.write(pos5.toInt());

    delay (100);

  });
  
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
}
