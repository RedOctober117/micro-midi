#ifndef BUTTON_H
#define BUTTON_H

#include "control.hpp"

class Button : public Control {
  public:
    int voltage_high;
    int voltage_low;
    boolean latched;
    int previous_velocity;
    Button ();
    Button (int, int, byte, byte);

    void toggle(int, int);
};

#endif