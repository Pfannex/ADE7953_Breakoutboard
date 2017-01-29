#pragma once


# Basic Wiring Functions: http://www.esp8266.com/wiki/doku.php?id=esp8266_gpio_pin_allocations 
#define BUTTON_PIN  6 // GPIO 6

class ESP8266_Button {
  private
    byte  buttonpin;
  public:
    ESP8266_Button(byte pin);
}

