#include <ESP8266WiFi.h>

#include <FirebaseArduino.h>

#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "WIFI PASSWORD"
#define FIREBASE_HOST "?????????????.firebaseio.com"
#define FIREBASE_AUTH "AUTH KEY"

int LED1 = 4;

void setup()
{
Serial.begin(115200);

pinMode(LED1, OUTPUT);

  delay(2000);
  Serial.println('\n');
  
  wifiConnect();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  delay(10);
}

void loop()
{  
  
Serial.print(Firebase.getString("LED1") + "\n");

analogWrite(LED1, Firebase.getString("LED1").toInt());
delay(10);

if(WiFi.status() != WL_CONNECTED)
{
  wifiConnect();
}
delay(10);

}

void wifiConnect()
{
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);        
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID); Serial.println(" ...");

  int teller = 0;
  while (WiFi.status() != WL_CONNECTED)
  {                                      
    delay(1000);
    Serial.print(++teller); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         
}
