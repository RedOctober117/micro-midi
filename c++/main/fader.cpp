#include "fader.hpp"

Fader::Fader() { }

Fader::Fader(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}

void Fader::toggle() {
  if (this->current_voltage != this->previous_voltage) {
    Control::toggle(this->current_voltage);
  }
  this->previous_voltage = this->current_voltage;
}
