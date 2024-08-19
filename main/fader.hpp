#ifndef FADER_H
#define FADER_H

#include "control.hpp"

class Fader : public Control{
  public:
    int current_voltage;
    Fader ();
    Fader (byte, byte);

    void toggle(int);
    void setVoltage(int);
    int getVoltage();
};


#endif