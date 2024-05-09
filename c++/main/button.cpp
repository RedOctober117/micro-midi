#include "button.hpp"

Button::Button() { }

Button::Button(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}