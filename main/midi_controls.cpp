#include "midi_controls.hpp"

void momentary_command(byte channel, byte controller, byte duration)
{
  controlChange(channel, controller, 127);
  MidiUSB.flush();
  delay(duration);
  controlChange(channel, controller, 0);
  MidiUSB.flush();
}

void controlChange(byte channel, byte controller, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, controller, value};
  MidiUSB.sendMIDI(event);
}

void latch_command(byte channel, byte controller, byte value)
{
  controlChange(channel, controller, value);
  MidiUSB.flush();
}

// void noteOn(byte channel, byte pitch, byte velocity)
// {
//   midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
//   MidiUSB.sendMIDI(noteOn);
// }

// void noteOff(byte channel, byte pitch, byte velocity)
// {
//   midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
//   MidiUSB.sendMIDI(noteOff);
// }

// int calc_midi(int voltage_in) {
//   return (voltage_in * 10 / 127);
// }
// this could completely remove the need for OOP. just calc the midi value on
// the fly instead of associating a value with each button
