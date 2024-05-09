#include "button.hpp"

Control::Control() { }

Control::Control(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}

void Control::toggle(byte velocity) {
  latch_command(channel, pitch, velocity);
}

void Control::momentary(byte duration) {
  momentary_command(channel, pitch, duration);
}