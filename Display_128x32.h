
#ifndef __Display_128x32__
#define __Display_128x32__

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4

class Display_128x32 {

private:
  Adafruit_SSD1306* _display;

public:
  Display_128_32() {
    
  }

  void begin() {
    _display = new Adafruit_SSD1306(OLED_RESET);
    // Initialize with the I2C addr 0x3C (for the 128x32)
    _display->begin(SSD1306_SWITCHCAPVCC, 0x3C);
  }

  void set_text(String text, int x, int y, int size = 1) {
    _display->setTextSize(size);
    _display->setTextColor(WHITE);
    _display->setCursor(x,y);
    _display->println(text);
  }

  void set_row_text(String text, int row, int start_x = 0, int size = 1) {
    _display->setTextSize(size);
    _display->setTextColor(WHITE);
    _display->setCursor(start_x,row*size*8);
    _display->println(text);
  }

  void show() {
    _display->display();
  }

  void clear() {
    _display->clearDisplay();
  }
  
};

#endif
