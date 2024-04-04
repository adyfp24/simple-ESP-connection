#include <ESP8266WiFi.h> 
#include <WebSocketClient.h>

const char* ssid     = "Infinix12";
const char* password = "1234567890";
char path[] = "/";
char host[] = "192.168.138.165:4000";

WebSocketClient webSocketClient;
WiFiClient client;

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  delay(5000);
  

  if (client.connect("192.168.138.165", 4000)) {
    Serial.println("Connected");
  } else {
    Serial.println("Connection failed.");
    while(1) {

    }
  }
  

  webSocketClient.path = path;
  webSocketClient.host = host;
  if (webSocketClient.handshake(client)) {
    Serial.println("Handshake successful");
  } else {
    Serial.println("Handshake failed.");
    while(1) {

    }  
  }
}

void loop() {
  String data;

  if (client.connected()) {
    
    webSocketClient.getData(data);
    if (data.length() > 0) {
      Serial.print("Received data: ");
      Serial.println(data);
    }
   
    data = "1";
    
    webSocketClient.sendData(data);
    
  } else {
    Serial.println("Client disconnected.");
    while (1) {
    }
  }

 
  delay(3000);
}
