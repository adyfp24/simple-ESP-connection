#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "Infinix12";
const char* password = "1234567890";
const char* server = "192.168.138.165";
const int httpPort = 3000; 

void setup() {
  Serial.begin(9600);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println(ESP.getFreeHeap());
  delay(5000);
}

void loop() {

  // HTTP POST Request
  WiFiClient postWClient;
  
  if (!postWClient.connect(server, httpPort)) {
    Serial.println("POST Connection failed.");
  } else {
    HTTPClient http;
    String postUrl = "http://" + String(server) + ":" + String(httpPort) + "/api/sensordata";
    http.begin(postWClient, postUrl);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    int kelembapan = 80; // Data yang akan dikirim
    int httpResponseCode = http.POST(String(kelembapan));

    if (httpResponseCode > 0) {
      Serial.print("POST HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println("POST Response: " + payload);
    } else {
      Serial.print("POST Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }
  delay(1000);
}
//    HTTP GET Request
//  WiFiClient getWClient;
//  
//  if (!getWClient.connect(server, httpPort)) {
//    Serial.println("GET Connection failed.");
//  } else {
//    HTTPClient http;
//    String getUrl = "http://" + String(server) + ":" + String(httpPort) + "/api/getdata";
//    http.begin(getWClient, getUrl);
//
//    int httpResponseCode = http.GET();
//
//    if (httpResponseCode > 0) {
//      Serial.print("GET HTTP Response code: ");
//      Serial.println(httpResponseCode);
//      String payload = http.getString();
//      Serial.println("GET Response: " + payload);
//    } else {
//      Serial.print("GET Error code: ");
//      Serial.println(httpResponseCode);
//    }
//
//    http.end();
//  }
//  delay(1000); // Delay 1 second before next request 
//}
