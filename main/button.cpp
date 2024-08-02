#include "button.hpp"

Button::Button() { }

Button::Button(int voltage_low, int voltage_high, byte channel, byte pitch) {
  this->voltage_low = voltage_low;
  this->voltage_high = voltage_high;
  this->channel = channel;
  this->pitch = pitch;
  // this->pin = pin;
}

void Button::toggle(int voltage, int delay_amount) {
  if ((voltage > this->voltage_low) & (voltage < this->voltage_high)) {
    Serial.println("Button pressed");
    switch (previous_velocity) {
      case 0:
        this->previous_velocity = 127;
        Control::toggle(this->previous_velocity);
        break;
      case 127:
        this->previous_velocity = 0;
        Control::toggle(this->previous_velocity);
        break;
    }
    delay(delay_amount);
  }
}
