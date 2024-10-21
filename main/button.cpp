#include "button.hpp"

Button::Button() {}

Button::Button(byte channel, byte pitch)
{
  this->channel = channel;
  this->pitch = pitch;
  this->previous_velocity = 0;
}

void Button::toggle()
{

  // Serial.print("Previous velocity ");
  // Serial.println(this->previous_velocity);
  switch (previous_velocity)
  {
    // Serial.println(this->previous_velocity);
  case 0:
    this->previous_velocity = 127;
    Control::toggle(this->previous_velocity);
    break;
  case 127:
    this->previous_velocity = 0;
    Control::toggle(this->previous_velocity);
    break;
  }
}
