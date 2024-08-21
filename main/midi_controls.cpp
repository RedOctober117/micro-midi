#include "midi_controls.hpp"

void momentary_command(byte channel, byte pitch, byte duration)
{
  controlChange(channel, pitch, 127);
  MidiUSB.flush();
  delay(duration);
  controlChange(channel, pitch, 0);
  MidiUSB.flush();
}
void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void latch_command(byte channel, byte pitch, byte velocity)
{
  controlChange(channel, pitch, velocity);
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

