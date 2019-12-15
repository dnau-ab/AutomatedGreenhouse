
#ifndef __TEMPERATURE_HUMIDITY_SENSOR__
#define __TEMPERATURE_HUMIDITY_SENSOR__

#include <DHT.h>

class TemperatureHumiditySensor {

private:
  int _pin;
  DHT* _sensor;

public:
  TemperatureHumiditySensor(int pin) {
    _pin = pin;
  }

  void begin() {
    pinMode(_pin, INPUT);
    _sensor = new DHT(_pin, DHT22);
    _sensor->begin();
  }

  float read_temperature(bool fahrenheit = true, int num_samples = 1) {
    float temperature = 0;
    for (int i = 0; i < num_samples; i++) {
      temperature += _sensor->readTemperature();
      delay(1);
    }
    temperature /= num_samples;

    if (fahrenheit) {
      temperature = (9.0/5.0 * temperature) + 32;
    }
    
    return temperature;
  }

  float read_humidity(int num_samples = 1) {
    float humidity = 0;
    for (int i = 0; i < num_samples; i++) {
      humidity += _sensor->readHumidity();
      delay(1);
    }
    humidity /= num_samples;
    return humidity;
  }
  
};

#endif
