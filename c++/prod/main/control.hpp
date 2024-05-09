#ifndef CONTROL_H
#define CONTROL_H
#include "midi_controls.hpp"
#include <Arduino.h>


class Control {
  public:
    int target_voltage;
    int previous_voltage;
    byte channel;
    byte pitch;

  Control ();
  Control (int, byte, byte);

  void toggle(byte);
  void momentary(byte);
};

#endif