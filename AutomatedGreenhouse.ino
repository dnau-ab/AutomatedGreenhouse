
#include "MoistureSensor.h"
#include "TemperatureHumiditySensor.h"
#include "LightSensor.h"
#include "Display_128x32.h"
#include "Fan.h"

#define PRINT_STATE_TO_SERIAL

// SENSORS
#define MOISTURE_SENSOR_PIN A0
#define TEMPERATURE_HUMIDITY_SENSOR_1_PIN A1
#define TEMPERATURE_HUMIDITY_SENSOR_2_PIN A2
#define LIGHT_SENSOR_PIN A3

LightSensor _lightSensor(LIGHT_SENSOR_PIN);

MoistureSensor _moistureSensor(MOISTURE_SENSOR_PIN);

TemperatureHumiditySensor _temperatureHumiditySensor1(TEMPERATURE_HUMIDITY_SENSOR_1_PIN);
TemperatureHumiditySensor _temperatureHumiditySensor2(TEMPERATURE_HUMIDITY_SENSOR_2_PIN);


// LIMITS
const float max_temperature = 60;
const float max_humidity = 0; // TODO: set


// ACTUATORS
#define FAN_1_PIN 3
#define FAN_2_PIN 4

Fan _fan1(FAN_1_PIN);
Fan _fan2(FAN_2_PIN);


// DISPLAY
Display_128x32 _display;


// MAIN PROGRAM

struct GreenhouseState {
  float moisture = 0;
  float temperature = 0;
  float humidity = 0;
  float light = 0;
  bool fans_on = false;
} _state;

// Read from sensors and set state
void update_sensors(GreenhouseState& state) {
  state.moisture = _moistureSensor.read_moisture();

  state.temperature = _temperatureHumiditySensor1.read_temperature();
  state.temperature += _temperatureHumiditySensor2.read_temperature();
  state.temperature /= 2;

  state.humidity = _temperatureHumiditySensor1.read_humidity();
  state.humidity += _temperatureHumiditySensor2.read_humidity();
  state.humidity /= 2;

  state.light = _lightSensor.read_light();
}

// Read from state and set actuators
void update_actuators(GreenhouseState& state) {
  if (state.temperature > max_temperature) {
    if (!state.fans_on) {
      state.fans_on = true;
      _fan1.turn_on();
      _fan2.turn_on();
    }
  }
  else if (state.fans_on) {
    state.fans_on = false;
    _fan1.turn_off();
    _fan2.turn_off();
  }
}

// Print Info to Serial
void print_state(GreenhouseState& state) {
  Serial.println("Moisture: " + String(state.moisture));
  Serial.println("Temperature: " + String(state.temperature));
  Serial.println("Humidity: " + String(state.humidity));
  Serial.println("Light: " + String(state.light));
  Serial.println("Fans: " + String(state.fans_on ? "ON" : "OFF"));
  Serial.println("");
}

// Display Info on OLED
void display_state(GreenhouseState& state) {
  _display.clear();
  // Sensor Readings
  _display.set_text("Mois: " + String((int)state.moisture), 0, 0);
  _display.set_text("Temp: " + String((int)state.temperature) + "F", 0, 8);
  _display.set_text("Humi: " + String((int)state.humidity), 0, 16);
  _display.set_text("Lumi: " + String((int)state.light), 0, 24);
  // Actuator states
  _display.set_text("Fans: " + String(state.fans_on ? "Y" : "N"), 80, 0);
  _display.show();
}

void setup() {

  Serial.begin(9600);

  _lightSensor.begin();
  _moistureSensor.begin();
  _temperatureHumiditySensor1.begin();
  _temperatureHumiditySensor2.begin();

  _fan1.begin();
  _fan2.begin();

  _display.begin();

  delay(1000);
}

void loop() {

  update_sensors(_state);
  update_actuators(_state);
#ifdef PRINT_STATE_TO_SERIAL
  print_state(_state);
#endif
  display_state(_state);

  // Wait
  delay(1000);

}
