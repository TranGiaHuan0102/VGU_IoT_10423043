#include <Arduino.h>

#define LED_PIN 5  // GPIO5 (D5)

void setup() {
    pinMode(LED_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    digitalWrite(LED_PIN, HIGH); // LED ON
    Serial.println("Hey!");
    delay(1000);
    digitalWrite(LED_PIN, LOW);  // LED OFF
    delay(1000);
}