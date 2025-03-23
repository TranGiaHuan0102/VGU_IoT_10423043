#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11

dht DHT;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int read_Data = DHT.read11(DHTPIN);
  float t = DHT.temperature;
  float h = DHT.humidity;

  Serial.print("Temperature = ");
	Serial.print(t);
	Serial.print("°C | ");
	Serial.print((t*9.0)/5.0+32.0);        // Convert celsius to fahrenheit
	Serial.println("°F ");
	Serial.print("Humidity = ");
	Serial.print(h);
	Serial.println("% ");
	Serial.println("");

	delay(2000); // wait two seconds
}
