#ifndef BUTTON_H
#define BUTTON_H

#include "control.hpp"

class Button : public Control {
  public:
    boolean latched;
    int previous_velocity;
    Button ();
    Button (int, byte, byte);
};

#endif