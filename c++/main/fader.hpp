#ifndef FADER_H
#define FADER_H

#include "control.hpp"

class Fader : public Control{
  public:
    int current_voltage;
    int previous_voltage;
    Fader ();
    Fader (int, byte, byte);

    void toggle();
};


#endif