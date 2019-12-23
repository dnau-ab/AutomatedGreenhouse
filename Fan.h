
#ifndef __FAN__
#define __FAN__

class Fan {

private:
  int _pin;
  bool _on = false;
  bool _on_logic = HIGH;

public:
  Fan(int pin, bool on_logic = HIGH) {
    _pin = pin;
    _on_logic = on_logic;
  }

  void begin() {
    pinMode(_pin, OUTPUT);
  }

  void turn_on() {
    _on = true;
    digitalWrite(_pin, _on_logic);
  }

  void turn_off() {
    _on = false;
    digitalWrite(_pin, !_on_logic);
  }

  void toggle() {
    _on = !_on;
    digitalWrite(_pin, _on ? _on_logic : !_on_logic);
  }

  bool is_on() {
    return _on;
  }
  
};

#endif
