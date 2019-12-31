#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiServer server(80);
String header;

void jsonEncode(){
  const size_t capacity = JSON_OBJECT_SIZE(3);
  DynamicJsonDocument payload(capacity);
  payload["rain"] = digitalRead(4);
  payload["humidity"] = digitalRead(5);
  payload["temperature"] = analogRead(A0);
  serializeJson(payload, Serial);
}

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
            jsonEncode();                            
            client.println("HTTP/1.1 200 OK");
            client.println("Access-Control-Allow-Origin:*");
            client.println("Content-type:application/json");
            client.println("Server:NodeMCU");
            client.println("Content-lenght:100");
            client.println("Connection:keep-alive");
            client.println();
            client.println(payload);
    Serial.println("Accessing");
    delay(2000);
  }
}
