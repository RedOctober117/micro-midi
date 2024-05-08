#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>
#include "vins.h"

// #defined vars are pure constants
// VALID ANAOLGLUE IN:
// A0
// A1
// A2
// A3
// A4
// A5
// A6
// A7
// A8
// A9
// A10
// A11

// Solo mute
#define BUTTON_BANK_1 A0
// Focus
#define BUTTON_BANK_2 A1

#define FADER_1 A2
#define FADER_2 A3
#define FADER_3 A4
#define FADER_4 A5
#define FADER_5 A6
#define FADER_6 A7
#define FADER_7 A8
#define FADER_8 A9

// const int BUTTON_1 = 31;
// const int BUTTON_2 = 27;
// const int BUTTON_3 = 23;
// const int BUTTON_4 = 19;
// const int BUTTON_5 = 15;
// const int BUTTON_6 = 12;
// const int BUTTON_7 = 8;
// const int BUTTON_8 = 4;

// const int button_ranges[8] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8};

struct solo_mute {
  int number;
  int vin;
  void 
}

int fader_1_volt = 0;
int fader_2_volt = 0;
int fader_3_volt = 0;
int fader_4_volt = 0;
int fader_5_volt = 0;
int fader_6_volt = 0;
int fader_7_volt = 0;
int fader_8_volt = 0;

int fader_1_prev = 0;
int fader_2_prev = 0;
int fader_3_prev = 0;
int fader_4_prev = 0;
int fader_5_prev = 0;
int fader_6_prev = 0;
int fader_7_prev = 0;
int fader_8_prev = 0;

bool button_bank_1_pressed = false;
bool button_bank_2_pressed = false;

int button_bank_1_voltage;
int button_bank_1_voltage;
int previous_button_bank_1_voltage;
int previous_button_bank_1_voltage;

uint8_t muxed_buttons = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(BUTTON_BANK_1, INPUT);
  pinMode(BUTTON_BANK_2, INPUT);
  pinMode(FADER_1, INPUT);
  pinMode(FADER_2, INPUT);
  pinMode(FADER_3, INPUT);
  pinMode(FADER_4, INPUT);
  pinMode(FADER_5, INPUT);
  pinMode(FADER_6, INPUT);
  pinMode(FADER_7, INPUT);
  pinMode(FADER_8, INPUT);
}

void loop()
{
  button__bank_1_voltage = analogRead(BUTTON_BANK_1) / 32;
  button__bank_2_voltage = analogRead(BUTTON_BANK_2) / 32;
  read_faders();

  if (button_voltage != previous_button_voltage)
  {
    solo_mute();
  }

  if (fader_1_volt > fader_1_prev || fader_1_volt < fader_1_prev)
  {
    latch_command(0, 41, fader_1_volt);
  }

  set_fader_previous();
  set_button_previous();
  // Serial.print("FADER 1: ");
  // Serial.println(fader_1_volt);
  // Serial.print("FADER 2: ");
  // Serial.println(FADER_2);
  // Serial.print("FADER 3: ");
  // Serial.println(FADER_3);
  // Serial.print("FADER 4: ");
  // Serial.println(FADER_4);

  // for (int note = 24; note < 127; note += 2) {
  //   Serial.println("sending midi . . .");
  //   noteOn(1, note, 64);
  //   delay(1000);
  //   noteOff(1, note, 0);
  //   MidiUSB.flush();
  //   delay(1000);
  // }

  // controlChange(0, 51, 127);
  // MidiUSB.flush();
  // delay(3000);
  // controlChange(0, 51, 0);
  // delay(1000);
  // MidiUSB.flush();
  // delay(1000);

  // latch_command(0, 51, 127);
  // delay(3000);
  // latch_command(0, 51, 0);
  // delay(3000);

  // read_buttons_with_muxer();
  // Serial.print("muxed value: ");
  // Serial.println(muxed_buttons);
}

void momentary_command(byte channel, byte pitch, byte duration)
{
  controlChange(channel, pitch, 127);
  MidiUSB.flush();
  delay(duration);
  controlChange(channel, pitch, 0);
  MidiUSB.flush();
}

void latch_command(byte channel, byte pitch, byte velocity)
{
  controlChange(channel, pitch, velocity);
  MidiUSB.flush();
}

void noteOn(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity)
{
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value)
{
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void read_buttons_with_muxer()
{
  switch (button_voltage)
  {
  case BUTTON_1:
    muxed_buttons = muxed_buttons | (byte)00000001;
    break;
  case BUTTON_2:
    muxed_buttons = muxed_buttons | (byte)00000010;
    break;
  case BUTTON_3:
    muxed_buttons = muxed_buttons | (char)00000100;
    break;
  case BUTTON_4:
    muxed_buttons = muxed_buttons | (char)00001000;
    break;
  case BUTTON_5:
    muxed_buttons = muxed_buttons | (char)00010000;
    break;
  case BUTTON_6:
    muxed_buttons = muxed_buttons | (char)00100000;
    break;
  case BUTTON_7:
    muxed_buttons = muxed_buttons | (char)01000000;
    break;
  case BUTTON_8:
    muxed_buttons = muxed_buttons | (char)10000000;
    break;
  default:
    break;
  }
}

void test_read_buttons()
{
  if (button_voltage > BUTTON_1)
  {
    Serial.println("Button 1");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_2)
  {
    Serial.println("Button 2");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_3)
  {
    Serial.println("Button 3");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_4)
  {
    Serial.println("Button 4");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_5)
  {
    Serial.println("Button 5");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_6)
  {
    Serial.println("Button 6");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_7)
  {
    Serial.println("Button 7");
    Serial.println(button_voltage);
  }
  else if (button_voltage > BUTTON_8)
  {
    Serial.println("Button 8");
    Serial.println(button_voltage);
  }
}

void read_faders()
{
  fader_1_volt = analogRead(FADER_1) / 8;
  fader_2_volt = analogRead(FADER_2) / 8;
  fader_3_volt = analogRead(FADER_3) / 8;
  fader_4_volt = analogRead(FADER_4) / 8;
  fader_5_volt = analogRead(FADER_5) / 8;
  fader_6_volt = analogRead(FADER_6) / 8;
  fader_7_volt = analogRead(FADER_7) / 8;
  fader_8_volt = analogRead(FADER_8) / 8;
}

void set_fader_previous()
{
  fader_1_prev = fader_1_volt;
  fader_2_prev = fader_2_volt;
  fader_3_prev = fader_3_volt;
  fader_4_prev = fader_4_volt;
  fader_5_prev = fader_5_volt;
  fader_6_prev = fader_6_volt;
  fader_7_prev = fader_7_volt;
  fader_8_prev = fader_8_volt;
}

void set_button_previous()
{
  previous_button_voltage = button_voltage;
}

//
// B1 B2 ...
// B9 B10 ...
//

void focus()
{
  // B9
  if (button_bank_2_voltage > BUTTON_9_LOWER && button_bank_2_voltage < BUTTON_9_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B10
  else if (button_bank_2_voltage > BUTTON_10_LOWER && button_bank_2_voltage < BUTTON_10_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B11
  else if (button_bank_2_voltage > BUTTON_11_LOWER && button_bank_2_voltage < BUTTON_11_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B12
  else if (button_bank_2_voltage > BUTTON_12_LOWER && button_bank_2_voltage < BUTTON_12_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B13
  else if (button_bank_2_voltage > BUTTON_13_LOWER && button_bank_2_voltage < BUTTON_13_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B14
  else if (button_bank_2_voltage > BUTTON_14_LOWER && button_bank_2_voltage < BUTTON_14_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B15
  else if (button_bank_2_voltage > BUTTON_15_LOWER && button_bank_2_voltage < BUTTON_15_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
  // B16
  else if (button_bank_2_voltage > BUTTON_16_LOWER && button_bank_2_voltage < BUTTON_16_UPPER)
  {
    if (button_bank_2_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_2_pressed = false;
    }
  }
}

void solo_mute()
{
  // B1
  if (button_bank_1_voltage > BUTTON_1_LOWER && button_bank_1_voltage < BUTTON_1_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 51, 0);
      button_bank_1_pressed = false;
    }
  }
  // B2
  else if (button_bank_1_voltage > BUTTON_2_LOWER && button_bank_1_voltage < BUTTON_2_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_1_pressed = false;
    }
  }
  // B3
  else if (button_bank_1_voltage > BUTTON_3_LOWER && button_bank_1_voltage < BUTTON_3_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 53, 0);
      button_bank_1_pressed = false;
    }
  }
  // B4
  else if (button_bank_1_voltage > BUTTON_4_LOWER && button_bank_1_voltage < BUTTON_4_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 54, 0);
      button_bank_1_pressed = false;
    }
  }
  // B5
  else if (button_bank_1_voltage > BUTTON_5_LOWER && button_bank_1_voltage < BUTTON_5_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 55, 0);
      button_bank_1_pressed = false;
    }
  }
  // B6
  else if (button_bank_1_voltage > BUTTON_6_LOWER && button_bank_1_voltage < BUTTON_6_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 56, 0);
      button_bank_1_pressed = false;
    }
  }
  // B7
  else if (button_bank_1_voltage > BUTTON_7_LOWER && button_bank_1_voltage < BUTTON_7_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 57, 0);
      button_bank_1_pressed = false;
    }
  }
  // B8
  else if (button_bank_1_voltage > BUTTON_8_LOWER && button_bank_1_voltage < BUTTON_8_UPPER)
  {
    if (button_bank_1_pressed)
    {
      latch_command(0, 52, 0);
      button_bank_1_pressed = false;
    }
    // switch (button_voltage) {
    //   case BUTTON_1:
    //     if(button_1_pressed) {
    //       latch_command(0, 51, 0);
    //       button_1_pressed = false;
    //       break;
    //     }
    //     latch_command(0, 51, 127);
    //     button_1_pressed = true;
    //     break;
    //   case BUTTON_2:
    //     momentary_command(0, 52, 50);
    //     break;
    //   case BUTTON_3:
    //     momentary_command(0, 53, 50);
    //     break;
    //   case BUTTON_4:
    //     momentary_command(0, 54, 50);
    //     break;
    //   case BUTTON_5:
    //     momentary_command(0, 55, 50);
    //     break;
    //   case BUTTON_6:
    //     momentary_command(0, 56, 50);
    //     break;
    //   case BUTTON_7:
    //     momentary_command(0, 57, 50);
    //     break;
    //   case BUTTON_8:
    //     momentary_command(0, 58, 50);
    //     break;
    //   default:
    //     break;
  }
}
