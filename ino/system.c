#include <DHT.h>
#include <Wire.h>
#include <RTClib.h>
#include <math.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define DHT_PIN 10

DHT dht(DHT_PIN, DHT22);
RTC_DS1307 rtc;

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

void initClock() {
  Wire.begin(5, 6); // SDA, SCL

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (!rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    // Uncomment the next line to set the date and time to the moment the sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  initWiFi();
  initClock();
}

void loop() {
  // read dht values
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    float humidity = -999;
    float temperature = -999;
  }

  // read ds1307 sensor
  DateTime now = rtc.now();
  char buffer[20];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d",
          now.year(), now.month(), now.day(),
          now.hour(), now.minute(), now.second());

  // Construir o objeto JSON
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["humidity"] = humidity;
  jsonDoc["temperature"] = temperature;
  jsonDoc["date_time"] = buffer;

  String jsonData;
  serializeJson(jsonDoc, jsonData);

  Serial.println(jsonData);

  delay(60000);
}