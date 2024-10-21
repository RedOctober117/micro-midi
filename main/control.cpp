#include "button.hpp"

Control::Control() {}

Control::Control(byte channel, byte pitch, uint8_t pin)
{
  this->channel = channel;
  this->pitch = pitch;
  this->pin = pin;
}

void Control::toggle(byte velocity)
{
  latch_command(channel, pitch, velocity);
}

void Control::momentary(byte duration)
{
  momentary_command(channel, pitch, duration);
}