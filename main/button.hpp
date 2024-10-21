#ifndef BUTTON_H
#define BUTTON_H

#include "control.hpp"

/// Button class, derived from Control.
class Button : public Control
{
public:
  /// The previous velocity the button sent.
  uint8_t previous_velocity;

  /// Default button constructor.
  Button();

  /// Overloaded Button constructor, receiving the voltage bounds, channel, and pitch.

  /// @param  channel Byte channel on which to send commands.
  /// @param  pitch Byte pitch, or velocity, that defines the MIDI command sent.
  Button(byte, byte);

  /// Toggles the button using super::toggle(), if conditions are met.
  void toggle();
};

#endif