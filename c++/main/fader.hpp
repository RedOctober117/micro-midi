#ifndef FADER_H
#define FADER_H

#include "control.hpp"

class Fader : public Control{
  public:
    int current_voltage;
    // int previous_voltage;
    Fader ();
    Fader (byte, byte);

    void toggle(int);
    // void set_voltage(int);
    void setVoltage(int);
    int getVoltage();
};


#endif