// DHT sensor library - Version: Latest 
#include <DHT.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h> 
#include <DHT_U.h>

#define DHTPIN 2
 
#define DHTTYPE    DHT11
 
DHT dht(DHTPIN, DHTTYPE);

WiFiClient client;

char ssid[] = "Your WiFi Username";
char pass[] = "Your WiFi Password";
int status = WL_IDLE_STATUS;

unsigned long myChannelNumber = 2500206;
const char * myWriteAPIKey = "H83QHU5677V93V8F";

float boardTEMP;
float boardHUMID;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);

  if (WiFi.status() == WL_NO_MODULE){
    Serial.println("Wifi failed");
    while(true);
  }

  Wifi_TurnOn();

  ThingSpeak.begin(client);
  
  dht.begin();
}

void Wifi_TurnOn(){
  while (status != WL_CONNECTED){
    status = WiFi.begin(ssid, pass);
    delay(1000);
  }
}

void loop() {  
  delay(2000);
  boardTEMP = dht.readTemperature();

  ThingSpeak.setField(1, boardTEMP);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  delay(20000);  
}
