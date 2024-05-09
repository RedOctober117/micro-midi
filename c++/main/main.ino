#include <Arduino.h>
#include <HardwareSerial.h>
#include "vins.hpp"
#include "midi_controls.hpp"
#include "button.hpp"
#include "fader.hpp"

// Solo
#define BUTTON_BANK_1 A0
// Mute
#define BUTTON_BANK_2 A1

#define FADER_1 A2
#define FADER_2 A3
#define FADER_3 A4
#define FADER_4 A5
#define FADER_5 A6
#define FADER_6 A7
#define FADER_7 A8
#define FADER_8 A9

Button solo_bank[8];
Button mute_bank[8];
Fader fader_bank[8];

void setup()
{
  solo_bank[0] = Button(BUTTON_1, 0, 51);
  solo_bank[1] = Button(BUTTON_2, 0, 52);
  solo_bank[2] = Button(BUTTON_3, 0, 53);
  solo_bank[3] = Button(BUTTON_4, 0, 54);
  solo_bank[4] = Button(BUTTON_5, 0, 55);
  solo_bank[5] = Button(BUTTON_6, 0, 56);
  solo_bank[6] = Button(BUTTON_7, 0, 57);
  solo_bank[7] = Button(BUTTON_8, 0, 58);

  mute_bank[0] = Button(BUTTON_9, 0, 59);
  mute_bank[1] = Button(BUTTON_10, 0, 60);
  mute_bank[2] = Button(BUTTON_11, 0, 62);
  mute_bank[3] = Button(BUTTON_12, 0, 63);
  mute_bank[4] = Button(BUTTON_13, 0, 64);
  mute_bank[5] = Button(BUTTON_14, 0, 65);
  mute_bank[6] = Button(BUTTON_15, 0, 66);
  mute_bank[7] = Button(BUTTON_16, 0, 67);

  fader_bank[0] = Fader(FADER_1, 0, 41);  
  fader_bank[1] = Fader(FADER_2, 0, 42);
  fader_bank[2] = Fader(FADER_3, 0, 43);
  fader_bank[3] = Fader(FADER_4, 0, 44);
  fader_bank[4] = Fader(FADER_5, 0, 45);
  fader_bank[5] = Fader(FADER_6, 0, 46);
  fader_bank[6] = Fader(FADER_7, 0, 47);
  fader_bank[7] = Fader(FADER_8, 0, 48);

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
  for (int i = 0; i < 8; i++) {
    update_button_voltage(solo_bank[i], BUTTON_BANK_1);
    update_button_voltage(mute_bank[i], BUTTON_BANK_2);
  }

  update_faders();
}

void update_faders() {
  update_fader_voltage(fader_bank[0], FADER_1);
  update_fader_voltage(fader_bank[1], FADER_2);
  update_fader_voltage(fader_bank[2], FADER_3);
  update_fader_voltage(fader_bank[3], FADER_4);
  update_fader_voltage(fader_bank[4], FADER_5);
  update_fader_voltage(fader_bank[5], FADER_6);
  update_fader_voltage(fader_bank[6], FADER_7);
  update_fader_voltage(fader_bank[7], FADER_8);
}

void update_button_voltage(Button button, const uint8_t pin) {
  int current_voltage = analogRead(pin);
  if (button.previous_voltage != current_voltage) {
    switch (button.previous_velocity) {
      case 0:
        button.toggle(127);
        button.previous_velocity = 127;
        break;
      case 127:
        button.toggle(0);
        button.previous_velocity = 0;
        break;
      default:
        break;
    }
  }

  button.previous_voltage = current_voltage;
}

void update_fader_voltage(Fader fader, const uint8_t pin) {
  int current_voltage = analogRead(pin);
  if (fader.previous_voltage != current_voltage) {
    fader.toggle(current_voltage);
  }

  fader.previous_voltage = current_voltage;
}
