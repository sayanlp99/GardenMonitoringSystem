#include <ESP8266WiFi.h>
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiServer server(80);
String header;
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
            client.println("HTTP/1.1 200 OK");
            client.println("Access-Control-Allow-Origin:*");
            client.println("Content-type:application/json");
            client.println("Server:NodeMCU");
            client.println("Content-lenght:100");
            client.println("Connection:keep-alive");
            client.println();
            client.println("{");
            client.print("\"rain\":");
            client.print(digitalRead(5));
            client.println(",");
            client.print("\"humidity\":");
            client.print(digitalRead(4));
            client.println(",");
            client.print("\"temperature\":");
            client.println(analogRead(A0));
            client.println("}");
    Serial.println("");
  }
}
