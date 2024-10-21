#ifndef MIDI_CONTROLS_H
#define MIDI_CONTROLS_H

#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

/// Sends a MIDI ON, waits, and sends a MIDI off.
/// @param channel Byte channel to send the command on.
/// @param controller Byte pitch sent.
/// @param duration Time between sending the first signal and the second.
void momentary_command(byte channel, byte controller, byte duration);

/// Function to send a new command to a control, using MIDI events.
/// @param channel Byte channel to send the command on.
/// @param controller Byte control to separate one control from another.
/// @param value Byte value to be sent.
void controlChange(byte channel, byte controller, byte value);

/// @brief Sends a MIDI command and flushes the MIDI buffer.
/// @param channel Byte channel to send the command on.
/// @param pitch Byte pitch to separate one control from another.
/// @param velocity Byte velocity to be sent.
void latch_command(byte channel, byte pitch, byte velocity);

// ///
// /// @param channel
// /// @param pitch
// /// @param velocity
// void noteOn(byte channel, byte pitch, byte velocity);

// void noteOff(byte channel, byte pitch, byte velocity);

// int calc_midi(int voltage_in);

#endif
