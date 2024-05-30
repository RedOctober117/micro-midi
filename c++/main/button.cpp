#include "button.hpp"

Button::Button() { }

Button::Button(int voltage_low, int voltage_high, byte channel, byte pitch) {
  // this->voltage_range = voltage;
  this->voltage_low = voltage_low;
  this->voltage_high = voltage_high;
  this->channel = channel;
  this->pitch = pitch;
}

void Button::toggle() {
  switch (previous_velocity) {
    case 0:
      Control::toggle(127);
      this->previous_velocity = 127;
      break;
    case 127:
      Control::toggle(0);
      this->previous_velocity = 0;
      break;
  }
}