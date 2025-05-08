#include <Arduino.h>
#include <TinyGPS++.h>

// Use UART2 (Serial2) on ESP32, mapped to GPIO16 (RX), GPIO17 (TX)
HardwareSerial GPS(2);  // UART2
TinyGPSPlus gps;        // TinyGPSPlus to process NMEA sentences

// Time to sleep in seconds (30 seconds)
#define SLEEP_TIME 30
// Maximum time to wait for GPS data (in milliseconds)
#define GPS_TIMEOUT 10000

bool readGPSData();
void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect
  }
  
  GPS.begin(9600, SERIAL_8N1, 16, 17);  // GPS at 9600 baud
  
  Serial.println("ESP32 GPS Tracker");
  Serial.println("Waiting for GPS data...");
  
  // Try to get GPS data for up to GPS_TIMEOUT milliseconds
  bool gpsDataReceived = false;
  unsigned long startTime = millis();
  
  while ((millis() - startTime) < GPS_TIMEOUT) {
    if (readGPSData()) {
      gpsDataReceived = true;
      break;
    }
    delay(100);  // Small delay between reads
  }
  
  if (!gpsDataReceived) {
    Serial.println("No valid GPS data received within timeout period.");
  }
  
  // Print a message before going to sleep
  Serial.println("Going to sleep for " + String(SLEEP_TIME) + " seconds...");
  Serial.flush();  // Make sure all serial data is sent before sleeping
  delay(100);
  
  // Initialize deep sleep timer for the specified duration
  esp_sleep_enable_timer_wakeup(SLEEP_TIME * 1000000);  // SLEEP_TIME in microseconds
  esp_deep_sleep_start();
}

bool readGPSData() {
  bool newData = false;
  
  // Read data from GPS module
  while (GPS.available()) {
    char c = GPS.read();
    gps.encode(c);  // Feed data to TinyGPSPlus decoder
    newData = true;
  }
  
  // If we processed new data and have a valid location, print it
  if (newData && gps.location.isValid()) {
    Serial.print("Location: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    Serial.print(" - from ");
    Serial.print(gps.satellites.value());
    Serial.println(" satellites");
    return true;
  }
  
  return false;
}

void loop() {
  // This won't be reached because we're using deep sleep
  // But it's good practice to have it for potential future changes
  delay(1000);
}