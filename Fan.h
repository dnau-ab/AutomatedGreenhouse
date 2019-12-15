
#ifndef __FAN__
#define __FAN__

class Fan {

private:
  int _pin;
  bool _on = false;

public:
  Fan(int pin) {
    _pin = pin;
  }

  void begin() {
    pinMode(_pin, OUTPUT);
  }

  void turn_on() {
    _on = true;
    digitalWrite(_pin, HIGH);
  }

  void turn_off() {
    _on = false;
    digitalWrite(_pin, LOW);
  }

  void toggle() {
    _on = !_on;
    digitalWrite(_pin, _on ? HIGH : LOW);
  }

  bool is_on() {
    return _on;
  }
  
};

#endif
