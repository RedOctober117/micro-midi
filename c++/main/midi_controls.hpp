#ifndef MIDI_CONTROLS_H
#define MIDI_CONTROLS_H
#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>


void controlChange(byte channel, byte control, byte value);

void momentary_command(byte channel, byte pitch, byte duration);

void latch_command(byte channel, byte pitch, byte velocity);

void noteOn(byte channel, byte pitch, byte velocity);

void noteOff(byte channel, byte pitch, byte velocity);

#endif