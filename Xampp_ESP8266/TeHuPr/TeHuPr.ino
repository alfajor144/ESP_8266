/*
 *---------BME280 VCC->3.3v, SCL-> GPIO-5, SDA->GPIO-4.
 *---------DHT    VCC->5v,   OUT-> GPIO-2.
 */
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme;
#define DHTTYPE DHT11 //DHT21, DHT22
#define DHTPIN  2 // GPIO2

DHT dht(DHTPIN, DHTTYPE, 11); // 11 works fine for ESP8266 threshold => MHZ CPU

float temperatura; // double
float humedad;
float presion;

const char* ssid = "nombre de tu wifi"; 
const char* password = "contraseña de tu wifi"; 

void setup(){
  dht.begin(); 
  Wire.pins(5, 4);
  Wire.begin(5, 4);
  bme.begin(0x76);
  WiFi.begin(ssid, password);
  
  while(WiFi.status() != WL_CONNECTED){
      delay(500);
  }
}
void loop(){
  if(WiFi.status() == WL_CONNECTED){

    HTTPClient http;
    http.begin("http://192.168.1.11/01php/ESP8266_THP/Incertar.php");
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    temperatura = bme.readTemperature();
    humedad = dht.readHumidity();
    presion = (bme.readPressure())/100;

    int httpCode = http.POST("temp="+String(temperatura)+"&hum="+String(humedad)+"&pres="+String(presion));
    
    String payload = http.getString();

    http.end();
  }
  delay(100000); // envia los datos cada 100 seg
}
