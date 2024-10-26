#include "fader.hpp"
#include "midi_controls.hpp"

void toggle_fader(Fader &fader, int voltage)
{
  if (voltage > fader.current_voltage + 1 || voltage < fader.current_voltage - 1)
  {
    fader.current_voltage = voltage;
    toggle(fader.channel, fader.pitch, voltage);
  }
}
