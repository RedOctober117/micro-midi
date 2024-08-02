#ifndef CONTROL_H
#define CONTROL_H
#include "midi_controls.hpp"
#include <Arduino.h>


class Control {
  public:
    int previous_voltage;
    byte channel;
    byte pitch;
    uint8_t pin;

  Control ();
  Control (byte, byte, uint8_t);

  void toggle(byte);
  void momentary(byte);
};

#endif