
#ifndef __MOISTURE_SENSOR__
#define __MOISTURE_SENSOR__

class MoistureSensor {

private:
  int _pin;

public:
  MoistureSensor(int pin) {
    _pin = pin;
  }

  void begin() {
    pinMode(_pin, INPUT);
  }

  float read_moisture(int num_samples = 100) {
    float moisture_value = 0;
    for (int i = 0; i < num_samples; i++) { 
      moisture_value += analogRead(_pin);
      delay(1);
    }
    moisture_value /= num_samples;
    return moisture_value;
  }
  
};

#endif
