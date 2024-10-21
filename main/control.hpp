#ifndef CONTROL_H
#define CONTROL_H
#include "midi_controls.hpp"
#include <Arduino.h>

/**
 * The base Control class, describing an abstracted MIDI control.
 */
class Control
{
public:
  /// Byte representation of the channel.
  byte channel;

  /// Byte representation of the pitch.
  byte pitch;

  /// Unsigned 8b representation of the pin, using a #DEFINE.
  uint8_t pin;

  /// Default Control constructor.
  Control();

  /// Overloaded Control constructor, receiving the channel, pitch, and pin.
  /// @param  channel Byte representation of the channel.
  /// @param  pitch Byte representation of the pitch.
  /// @param  pin Unsigned 8b representation of the pin, using a #DEFINE.
  Control(byte, byte, uint8_t);

  /// Send a MIDI command to the receiver.
  /// @param  velocity Byte representation of the value to be sent to the receiver.
  void toggle(byte);

  /// Send a MIDI command, wait, and send another command. Effectively an on/off switch.
  /// @param  duration Byte representation of the time in ms to wait between sending the second signal.
  void momentary(byte);
};

#endif