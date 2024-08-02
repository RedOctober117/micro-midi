#include <Arduino.h>
#include <HardwareSerial.h>
#include "vins.hpp"
#include "midi_controls.hpp"
#include "button.hpp"
#include "fader.hpp"
// #include <tuple>

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
uint8_t fader_pins[8];
int fader_voltages[8];

unsigned long delay_amount = 200;

void setup()
{
  solo_bank[0] = Button(BUTTON_1_LOWER, BUTTON_1_UPPER, 0, 51);
  solo_bank[1] = Button(BUTTON_2_UPPER, BUTTON_2_UPPER, 0, 52);
  solo_bank[2] = Button(BUTTON_3_UPPER, BUTTON_3_UPPER, 0, 53);
  solo_bank[3] = Button(BUTTON_4_UPPER, BUTTON_4_UPPER, 0, 54);
  solo_bank[4] = Button(BUTTON_5_UPPER, BUTTON_5_UPPER, 0, 55);
  solo_bank[5] = Button(BUTTON_6_UPPER, BUTTON_6_UPPER, 0, 56);
  solo_bank[6] = Button(BUTTON_7_UPPER, BUTTON_7_UPPER, 0, 57);
  solo_bank[7] = Button(BUTTON_8_UPPER, BUTTON_8_UPPER, 0, 58);

  mute_bank[0] = Button(BUTTON_9_LOWER, BUTTON_9_LOWER, 0, 59);
  mute_bank[1] = Button(BUTTON_10_LOWER, BUTTON_10_LOWER, 0, 60);
  mute_bank[2] = Button(BUTTON_11_LOWER, BUTTON_11_LOWER, 0, 62);
  mute_bank[3] = Button(BUTTON_12_LOWER, BUTTON_12_LOWER, 0, 63);
  mute_bank[4] = Button(BUTTON_13_LOWER, BUTTON_13_LOWER, 0, 64);
  mute_bank[5] = Button(BUTTON_14_LOWER, BUTTON_14_LOWER, 0, 65);
  mute_bank[6] = Button(BUTTON_15_LOWER, BUTTON_15_LOWER, 0, 66);
  mute_bank[7] = Button(BUTTON_16_LOWER, BUTTON_16_LOWER, 0, 67);

  fader_bank[0] = Fader(0, 41);  
  fader_bank[1] = Fader(0, 42);
  fader_bank[2] = Fader(0, 43);
  fader_bank[3] = Fader(0, 44);
  fader_bank[4] = Fader(0, 45);
  fader_bank[5] = Fader(0, 46);
  fader_bank[6] = Fader(0, 47);
  fader_bank[7] = Fader(0, 48);
  
  fader_pins[0] = FADER_1;  
  fader_pins[1] = FADER_2;
  fader_pins[2] = FADER_3;
  fader_pins[3] = FADER_4;
  fader_pins[4] = FADER_5;
  fader_pins[5] = FADER_6;
  fader_pins[6] = FADER_7;
  fader_pins[7] = FADER_8;

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
  int bank_1_voltage = analogRead(BUTTON_BANK_1);
  int bank_2_voltage = analogRead(BUTTON_BANK_2);
  for (int i = 0; i < 8; i++) {
    fader_voltages[i] = analogRead(fader_pins[i]) / 8;
  }

  for (int i = 0; i < 8; i++) {
    update_button_voltage(solo_bank[i], bank_1_voltage, delay_amount);
    update_button_voltage(mute_bank[i], bank_2_voltage, delay_amount);
    if (i == 0) {
      update_fader_voltage(fader_bank[i], fader_voltages[i]); 
    }
  }
}


// Without the `&`, a copy of the button or fader is passed, and so changes are
// lost each loop. With the `&`, the object itself is passed.
void update_button_voltage(Button& button, int voltage_in, int delay_amount) {
  button.toggle(voltage_in, delay_amount);
}

void update_fader_voltage(Fader& fader, int voltage_in) {
  fader.toggle(voltage_in);
}
