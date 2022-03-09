#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "INFINITUM319E_2.4"
#define STAPSK  "R6RnK3yb95"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
WiFiServer server(80); 
WiFiClient client;
boolean alreadyConnected = false;
int val;
int Periodo = 10000;
unsigned long Tiempo;

void setup(void) {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
}

void loop(void) {
  SendData();
  
  
}
void SendData(void){
  client = server.available();
  if(client){
    Serial.println("Client connected");
    while(client.connected()){
      val = analogRead(A0);
      Serial.println(val);
      client.println(String(val));
      delay(33);
      }
    }
}

  
