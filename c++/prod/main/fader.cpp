#include "fader.hpp"

Fader::Fader() { }

Fader::Fader(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}