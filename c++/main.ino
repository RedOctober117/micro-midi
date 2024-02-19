#include <frequencyToNote.h>
#include <MIDIUSB_Defs.h>
#include <MIDIUSB.h>
#include <pitchToFrequency.h>
#include <pitchToNote.h>

// #defined vars are pure constants
#define BUTTONS A0

#define FADER_1 A1
#define FADER_2 A2
#define FADER_3 A3
#define FADER_4 A4

const int BUTTON_1 = 31;
const int BUTTON_2 = 27;
const int BUTTON_3 = 23;
const int BUTTON_4 = 19;
const int BUTTON_5 = 15;
const int BUTTON_6 = 12;
const int BUTTON_7 = 8;
const int BUTTON_8 = 4;

// const int button_ranges[8] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8};

int fader_1_volt = 0;
int fader_2_volt = 0;
int fader_3_volt = 0;
int fader_4_volt = 0;

int fader_1_prev = 0;
int fader_2_prev = 0;
int fader_3_prev = 0;
int fader_4_prev = 0;

bool button_1_pressed = false;
int button_voltage;
int previous_button_voltage;

uint8_t muxed_buttons = 0;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTONS, INPUT);
  pinMode(FADER_1, INPUT);
  pinMode(FADER_2, INPUT);
  pinMode(FADER_3, INPUT);
  pinMode(FADER_4, INPUT);
}

void loop() {
  button_voltage = analogRead(BUTTONS) / 32;
  read_faders();

  if(button_voltage != previous_button_voltage) {
    solo_mute();
  }

  if (fader_1_volt > fader_1_prev || fader_1_volt < fader_1_prev) {
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

void momentary_command(byte channel, byte pitch, byte duration) {
  controlChange(channel, pitch, 127);
  MidiUSB.flush();
  delay(duration);
  controlChange(channel, pitch, 0);
  MidiUSB.flush();
}

void latch_command(byte channel, byte pitch, byte velocity) {
  controlChange(channel, pitch, velocity);
  MidiUSB.flush();
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void read_buttons_with_muxer() {
  switch (button_voltage) {
    case BUTTON_1:
      muxed_buttons = muxed_buttons | (byte) 00000001;
      break;
    case BUTTON_2:
      muxed_buttons = muxed_buttons | (byte) 00000010;
      break;
    case BUTTON_3:
      muxed_buttons = muxed_buttons | (char) 00000100;
      break;
    case BUTTON_4:
      muxed_buttons = muxed_buttons | (char) 00001000;
      break;
    case BUTTON_5:
      muxed_buttons = muxed_buttons | (char) 00010000;
      break;
    case BUTTON_6:
      muxed_buttons = muxed_buttons | (char) 00100000;
      break;
    case BUTTON_7:
      muxed_buttons = muxed_buttons | (char) 01000000;
      break;
    case BUTTON_8:
      muxed_buttons = muxed_buttons | (char) 10000000;
      break;
    default:
      break;
  }
}

void read_buttons() {
  if (button_voltage > BUTTON_1) {
    Serial.println("Button 1");
    Serial.println(button_voltage);

  } else if(button_voltage > BUTTON_2) {
    Serial.println("Button 2");
    Serial.println(button_voltage);

  } else if(button_voltage > BUTTON_3) {
    Serial.println("Button 3");
    Serial.println(button_voltage);

  }  else if(button_voltage > BUTTON_4) {
    Serial.println("Button 4");
    Serial.println(button_voltage);

  }  else if(button_voltage > BUTTON_5) {
    Serial.println("Button 5");
    Serial.println(button_voltage);

  }  else if(button_voltage > BUTTON_6) {
    Serial.println("Button 6");
    Serial.println(button_voltage);

  }  else if(button_voltage > BUTTON_7) {
    Serial.println("Button 7"); 
    Serial.println(button_voltage);

  }  else if(button_voltage > BUTTON_8) {
    Serial.println("Button 8");
    Serial.println(button_voltage);
  }
  // if (button_voltage < BUTTON_1) {
  //   Serial.println("Button 1");
  //   Serial.println(button_voltage);

  // } else if(button_voltage < BUTTON_2) {
  //   Serial.println("Button 2");
  //   Serial.println(button_voltage);

  // } else if(button_voltage < BUTTON_3) {
  //   Serial.println("Button 3");
  //   Serial.println(button_voltage);

  // }  else if(button_voltage < BUTTON_4) {
  //   Serial.println("Button 4");
  //   Serial.println(button_voltage);

  // }  else if(button_voltage < BUTTON_5) {
  //   Serial.println("Button 5");
  //   Serial.println(button_voltage);

  // }  else if(button_voltage < BUTTON_6) {
  //   Serial.println("Button 6");
  //   Serial.println(button_voltage);

  // }  else if(button_voltage < BUTTON_7) {
  //   Serial.println("Button 7"); 
  //   Serial.println(button_voltage);

  // }  else if(button_voltage < BUTTON_8) {
  //   Serial.println("Button 8");
  //   Serial.println(button_voltage);
  // }

}

void read_faders() {
  fader_1_volt = analogRead(FADER_1) / 8;
  fader_2_volt = analogRead(FADER_2) / 8;
  fader_3_volt = analogRead(FADER_3) / 8;
  fader_4_volt = analogRead(FADER_4) / 8;
}

void set_fader_previous() {
  fader_1_prev = fader_1_volt;
  fader_2_prev = fader_2_volt;
  fader_3_prev = fader_3_volt;
  fader_4_prev = fader_4_volt;
}

void set_button_previous() {
  previous_button_voltage = button_voltage;
}

void solo_mute() {
  switch (button_voltage) {
    case BUTTON_1:
      if(button_1_pressed) {
        latch_command(0, 51, 0);
        button_1_pressed = false;
        break;
      }
      latch_command(0, 51, 127);
      button_1_pressed = true;
      break;
    case BUTTON_2:
      momentary_command(0, 52, 50);
      break;
    case BUTTON_3:
      momentary_command(0, 53, 50);
      break;
    case BUTTON_4:
      momentary_command(0, 54, 50);
      break;
    case BUTTON_5:
      momentary_command(0, 55, 50);
      break;
    case BUTTON_6:
      momentary_command(0, 56, 50);
      break;
    case BUTTON_7:
      momentary_command(0, 57, 50);
      break;
    case BUTTON_8:
      momentary_command(0, 58, 50);
      break;
    default:
      break;
  }
}