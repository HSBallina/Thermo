#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHT_ORANGE 2
#define DHT_BLUE 3
#define DHT_RED 4
#define DHTTYPE DHT11

DHT_Unified dht_orange(DHT_ORANGE, DHTTYPE);
DHT_Unified dht_blue(DHT_BLUE, DHTTYPE);
DHT_Unified dht_red(DHT_RED, DHTTYPE);

DHT_Unified sensors[3] = {dht_orange, dht_blue, dht_red};

uint32_t delayMS;

// void display(int snum, sensor_t s){
//   Serial.print(F(" sensor:  ")); Serial.println(snum);
//   Serial.print(F(" id:      ")); Serial.println(s.sensor_id);
//   Serial.print(F(" name:    ")); Serial.println(s.name);
//   Serial.print(F(" type:    ")); Serial.println(s.type);
//   Serial.print(F(" version: ")); Serial.println(s.version);
//   Serial.println(F("------------------------------------"));
// }

void setup() {
  Serial.begin(9600);
  Serial.println(F("v 0.2"));
  Serial.println(F("Initializing sensors."));

  int i = 0;
  for(DHT_Unified &dht : sensors) {
    dht.begin();
    Serial.print(F("Sensor ")); Serial.print(++i); Serial.println(F(" ok."));
  }

  Serial.println(F("Done."));
  Serial.println(F("------------------------------------"));

  delayMS = 5000;
}

void loop() {

  int i = 0;

  for(DHT_Unified dht : sensors){
    delay(delayMS);

    sensors_event_t event;

    Serial.print(F("Sensor ")); Serial.println(++i);

    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("\tError reading temperature!"));
    }
    else {
      Serial.print(F("\tTemperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }

    dht.humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {
      Serial.println(F("\tError reading humidity!"));
    }
    else {
      Serial.print(F("\tHumidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
  }
}
