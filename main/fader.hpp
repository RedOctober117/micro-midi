#ifndef FADER_H
#define FADER_H

struct Fader
{
  char channel;
  char pitch;
  char current_voltage;
};

void toggle_fader(Fader &fader, int voltage);

#endif
