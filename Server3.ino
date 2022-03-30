#include <ESP8266WiFi.h>
#include <WiFiClient.h>

#ifndef STASSID
#define STASSID "MSI8230"
#define STAPSK  "P181%70w"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;
WiFiServer server(80  ); 
WiFiClient client;
boolean alreadyConnected = false;
int val;
int Periodo = 10000;
unsigned long Tiempo;
String Data;

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
  client = server.available();
  if(client){
    Serial.println("Client connected");
    while(client.connected()){
       for(int i=0; i<5; i++){
         val = analogRead(A0);
         Data+=(String(val) + " ");
         }
         Serial.println(Data);
         client.println(Data);
         delay(33);//Cambiar por millitime
         Data="";
      }
    }
  
  
}
