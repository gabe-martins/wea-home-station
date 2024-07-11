#include <Arduino.h>
#include <WiFi.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""

// Initialize WiFi
void initWiFi() {
  Serial.print("Connecting to WiFi.");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(100);
  }
  Serial.println(WiFi.localIP());
  Serial.println("Connected!");
}

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32-C3!");
  initWiFi();
}

void loop() {
  delay(1000);
}
