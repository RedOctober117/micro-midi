#ifndef FADER_H
#define FADER_H

#include "control.hpp"

class Fader : public Control{
  public:
    Fader ();
    Fader (int, byte, byte);
};


#endif