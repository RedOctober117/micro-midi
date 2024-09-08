#include "button.hpp"

Button::Button() { }

Button::Button(int voltage_low, int voltage_high, byte channel, byte pitch) {
  this->voltage_low = voltage_low;
  this->voltage_high = voltage_high;
  this->channel = channel;
  this->pitch = pitch;
  // this->pin = pin;
}

void Button::toggle(int voltage) {
  Serial.print("Voltage line in ");
  Serial.println(voltage);
  if ((voltage > this->voltage_low) & (voltage < this->voltage_high)) {
    if (this->pressed) {
      return;
    }
    this->pressed = true;
    Serial.print("Button pressed with voltage ");
    Serial.println(voltage);
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
  } else {
    this->pressed = false;
  }
}
