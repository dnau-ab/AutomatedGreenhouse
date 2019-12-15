
#ifndef __LIGHT_SENSOR__
#define __LIGHT_SENSOR__

class LightSensor {

private:
  int _pin;

public:
  LightSensor(int pin) {
    _pin = pin;
  }

  void begin() {
    pinMode(_pin, INPUT);
  }

  float read_light(int num_samples = 1) {
    float light = 0;
    for (int i = 0; i < num_samples; i++) {
      light += analogRead(_pin);
      delay(1);
    }
    light /= num_samples;
    return light;
  }
  
};

#endif
