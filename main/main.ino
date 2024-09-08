#include <Arduino.h>
#include <HardwareSerial.h>
#include "vins.hpp"
#include "midi_controls.hpp"
#include "button.hpp"
#include "fader.hpp"

// Define the default channel for all controls to operate on. There will
// eventually be a macro or something to change this on the fly.
#define CHANNEL 0


// Both button banks function identically, but are labeled as 'solo' and 'mute'
// to keep track of which pin takes what bank on the physical board.

// Solo bank pin
#define BUTTON_BANK_1 A0
// Mute bank pin
#define BUTTON_BANK_2 A1

// Fader pins.
// NOTE: The physical board labels pins A6-A9 as their digital label. See the
// micro documentation for more info.
#define FADER_1 A2
#define FADER_2 A3
#define FADER_3 A4
#define FADER_4 A5
#define FADER_5 A6
#define FADER_6 A7
#define FADER_7 A8
#define FADER_8 A9

// Initialize the arrays to store the Button and Fader objects, as well as the
// Fader pins and voltages.
Button solo_bank[8];
Button mute_bank[8];
Fader fader_bank[8];
uint8_t fader_pins[8];
int fader_voltages[8];

// My test board requires a delay to prevent the button from actuating twice
// per press. This will change depending on the quality of the final product.
unsigned long delay_amount = 200;

void setup()
{
  // Construct all Buttons and Faders inside their respective arrays. The 
  // 'pitch' is the command sent to the receiver, and is arbitrarily chosen.
  solo_bank[0] = Button(BUTTON_1_LOWER, BUTTON_1_UPPER, CHANNEL, 51);
  solo_bank[1] = Button(BUTTON_2_LOWER, BUTTON_2_UPPER, CHANNEL, 52);
  solo_bank[2] = Button(BUTTON_3_LOWER, BUTTON_3_UPPER, CHANNEL, 53);
  solo_bank[3] = Button(BUTTON_4_LOWER, BUTTON_4_UPPER, CHANNEL, 54);
  solo_bank[4] = Button(BUTTON_5_LOWER, BUTTON_5_UPPER, CHANNEL, 55);
  solo_bank[5] = Button(BUTTON_6_LOWER, BUTTON_6_UPPER, CHANNEL, 56);
  solo_bank[6] = Button(BUTTON_7_LOWER, BUTTON_7_UPPER, CHANNEL, 57);
  solo_bank[7] = Button(BUTTON_8_LOWER, BUTTON_8_UPPER, CHANNEL, 58);

  mute_bank[0] = Button(BUTTON_9_LOWER, BUTTON_9_UPPER, CHANNEL, 59);
  mute_bank[1] = Button(BUTTON_10_LOWER, BUTTON_10_UPPER, CHANNEL, 60);
  mute_bank[2] = Button(BUTTON_11_LOWER, BUTTON_11_UPPER, CHANNEL, 62);
  mute_bank[3] = Button(BUTTON_12_LOWER, BUTTON_12_UPPER, CHANNEL, 63);
  mute_bank[4] = Button(BUTTON_13_LOWER, BUTTON_13_UPPER, CHANNEL, 64);
  mute_bank[5] = Button(BUTTON_14_LOWER, BUTTON_14_UPPER, CHANNEL, 65);
  mute_bank[6] = Button(BUTTON_15_LOWER, BUTTON_15_UPPER, CHANNEL, 66);
  mute_bank[7] = Button(BUTTON_16_LOWER, BUTTON_16_UPPER, CHANNEL, 67);

  fader_bank[0] = Fader(CHANNEL, 41);  
  fader_bank[1] = Fader(CHANNEL, 42);
  fader_bank[2] = Fader(CHANNEL, 43);
  fader_bank[3] = Fader(CHANNEL, 44);
  fader_bank[4] = Fader(CHANNEL, 45);
  fader_bank[5] = Fader(CHANNEL, 46);
  fader_bank[6] = Fader(CHANNEL, 47);
  fader_bank[7] = Fader(CHANNEL, 48);
  
  fader_pins[0] = FADER_1;  
  fader_pins[1] = FADER_2;
  fader_pins[2] = FADER_3;
  fader_pins[3] = FADER_4;
  fader_pins[4] = FADER_5;
  fader_pins[5] = FADER_6;
  fader_pins[6] = FADER_7;
  fader_pins[7] = FADER_8;

  // Start the serial interface for debugging and set all pins to INPUT, using 
  // 0 as v_ref.
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
  // Read the voltages on every pin sequentially, per tick. Fader pins are
  // truncated by 3 bits to adhere to the 0-127 range of MIDI controls.
  int bank_1_voltage = analogRead(BUTTON_BANK_1);
  int bank_2_voltage = analogRead(BUTTON_BANK_2);
  for (int i = 0; i < 8; i++) {
    fader_voltages[i] = analogRead(fader_pins[i]) / 8;
  }

  // Run the update functions for every Button and Fader.
  for (int i = 0; i < 8; i++) {
    update_button_voltage(solo_bank[i], bank_1_voltage, delay_amount);
    update_button_voltage(mute_bank[i], bank_2_voltage, delay_amount);
    if (i != 7) {
      update_fader_voltage(fader_bank[i], fader_voltages[i]);     
    }
  }
}

// Without the `&`, a copy of the button or fader is passed, and so changes are
// lost each loop. With the `&`, the object itself is passed.
/**
 * Update the passed button. This encapsulation is not strictly necessary, but is being kept for possible future changes.
 * @param button The Button to be updated.
 * @param voltage_in The voltage read by the associated pin.
 * @param delay_amount The time in ms to delay after updating the pin.
 */
void update_button_voltage(Button& button, int voltage_in, int delay_amount) {
  button.toggle(voltage_in);
  // delay(delay_amount);
}

/**
 * Update the passed fader. This encapsulation is not strictly necessary, but is being kept for possible future changes.
 * @param fader The Fader to be updated.
 * @param voltage_in The voltage read by the associated pin.
 */
void update_fader_voltage(Fader& fader, int voltage_in) {
  fader.toggle(voltage_in);
}
