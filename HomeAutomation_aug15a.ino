#include "arduino_secrets.h"
#include <DHT11.h>
#include <DHT.h>
#include <DHT_U.h>


#include "thingProperties.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
unsigned long previousMillis = 0;
const long interval = 5000; 

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  pinMode(D7,OUTPUT);
  pinMode(D6,OUTPUT);
  delay(1500); 

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  
  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
 */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    DHT_SENSOR_READ();
  }
  
  
}



/*
  Since Light1 is READ_WRITE variable, onLight1Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onLight1Change()  {
  // Add your code here to act upon Light1 change
  if(light1) {
  digitalWrite(D7,LOW);
  Serial.println("ON");
  delay(100);
}
else {
digitalWrite(D7,HIGH);
Serial.println("OFF");
delay(100);
  }
}

/*
  Since Light2 is READ_WRITE variable, onLight2Change() is
  executed every time a new value is received from IoT Cloud.
*/
void onLight2Change()  {
  // Add your code here to act upon Light2 change
  if(light2) {
  digitalWrite(D6,LOW);
  Serial.println("ON");
  delay(100);
}
else {
digitalWrite(D6,HIGH);
Serial.println("OFF");
delay(100);
  }
}


void  DHT_SENSOR_READ(){
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
    if(isnan(temperature || humidity)){
  Serial.println("Failed to read the data from DHT sensor");
    }
  Serial.println("Temperature is");
  Serial.print(temperature);
  Serial.print(" °C ");
  Serial.println("");
  Serial.println("Humidity is");
  Serial.print(humidity);
  Serial.print(" % ");
  Serial.println("");
  
  
}
void onTemperatureChange()  {
  // Add your code here to act upon Temperature change
  
}