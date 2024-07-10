#include <Wire.h>
#include <RTClib.h>

RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);
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

void loop() {
  // read ds1307 sensor
  DateTime now = rtc.now();
  char buffer[20];
  sprintf(buffer, "%04d-%02d-%02d %02d:%02d:%02d", 
    now.year(), now.month(), now.day(), 
    now.hour(), now.minute(), now.second());

  Serial.println("-----------------------------");
  Serial.println(buffer);
  
  delay(1000);
}
