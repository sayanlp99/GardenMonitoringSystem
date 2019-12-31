#include <ESP8266WiFi.h>
#include <ArduinoJson.h>          //ArdunioJson v5.13.0
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiServer server(80);
String header;
int c=0;

void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
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
}

void loop(){
  WiFiClient client = server.available();
  if (client) {
    const size_t capacity = JSON_OBJECT_SIZE(3);
    DynamicJsonBuffer jsonBuffer(capacity);
    JsonObject& root = jsonBuffer.createObject();
    root["rain"] = digitalRead(4);
    root["humidity"] = digitalRead(5);
    root["temperature"] = analogRead(A0);                         
    client.println("HTTP/1.1 200 OK");
    client.println("Access-Control-Allow-Origin:*");
    client.println("Content-type:application/json");
    client.println("Server:NodeMCU");
    client.println("Content-lenght:75");
    client.println("Connection:keep-alive");
    client.println();
    root.printTo(client);
    Serial.print("Accessing Data: ");
    Serial.println(c++);
    delay(2000);
  }
}
