#include <DHT.h>
#include <math.h>

#define DHT_PIN 10
DHT dht(DHT_PIN, DHT22);

void setup() {
  Serial.begin(115200);
  Serial.println("Hello, ESP32-C3!");
  dht.begin();
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    float humidity = -999;
    float temperature = -999;
  }

  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print(" | temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  delay(1000);
}
