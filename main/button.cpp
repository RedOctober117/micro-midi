#include "button.hpp"
#include "midi_controls.hpp"

void toggle_button(Button &btn)
{
  switch (btn.previous_velocity)
  {
  case 0:
    btn.previous_velocity = 127;
    toggle(btn.channel, btn.pitch, btn.previous_velocity);
    break;
  case 127:
    btn.previous_velocity = 0;
    toggle(btn.channel, btn.pitch, btn.previous_velocity);
    break;
  }
}
