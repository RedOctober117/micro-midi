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

// Fader pins.
// NOTE: The physical board labels pins A6-A9 as their digital label. See the
// micro documentation for more info.
#define FADER_1 A0
#define FADER_2 A1
#define FADER_3 A2
#define FADER_4 A3
#define FADER_5 A4
#define FADER_6 A5
#define FADER_7 A10
#define FADER_8 A11

#define BUTTON_ROW_0 2
#define BUTTON_ROW_1 3
#define BUTTON_ROW_2 4
#define BUTTON_ROW_3 5

#define BUTTON_COL_0 6
#define BUTTON_COL_1 7
#define BUTTON_COL_2 8
#define BUTTON_COL_3 9

#define MAX_DEBOUNCE 3

// https://cdn-shop.adafruit.com/datasheets/sn74hc595.pdf
#define DATA_PIN 11 // SER
#define CLOCK_PIN 0 // SRCLK
#define LATCH_PIN 1 // RCLK

// Initialize the arrays to store the Button and Fader objects, as well as the
// Fader pins and voltages.
Button buttons[4][4];
uint8_t button_pin_rows[4];
uint8_t button_pin_cols[4];
uint8_t debounce[4][4];

uint16_t leds[4][4];

Fader fader_bank[8];
uint8_t fader_pins[8];
int fader_voltages[8];

uint16_t current_depressed = 0x0000;

// My test board requires a delay to prevent the button from actuating twice
// per press. This will change depending on the quality of the final product.
unsigned long delay_amount = 200;

void setup()
{
  // physical layout of buttons:
  //  1  2  3  4 5  6  7  8
  //  9 10 11 12 13 14 15 16

  // logical and wired layout of buttons:
  //  1  2  3  4
  //  9 10 11 12
  //  5  6  7  8
  // 13 14 15 16

  // will use d4-d11:
  //   d4-d7  for row,
  //   d8-d11 for col
  // Construct all Buttons and Faders inside their respective arrays. The
  // 'pitch' is the command sent to the receiver, and is arbitrarily chosen.

  // solo button
  buttons[0][0] = Button(CHANNEL, 51);
  buttons[0][1] = Button(CHANNEL, 52);
  buttons[0][2] = Button(CHANNEL, 53);
  buttons[0][3] = Button(CHANNEL, 54);
  buttons[2][0] = Button(CHANNEL, 55);
  buttons[2][1] = Button(CHANNEL, 56);
  buttons[2][2] = Button(CHANNEL, 57);
  buttons[2][3] = Button(CHANNEL, 58);

  // mute button
  buttons[1][0] = Button(CHANNEL, 59);
  buttons[1][1] = Button(CHANNEL, 60);
  buttons[1][2] = Button(CHANNEL, 62);
  buttons[1][3] = Button(CHANNEL, 63);
  buttons[3][0] = Button(CHANNEL, 64);
  buttons[3][1] = Button(CHANNEL, 65);
  buttons[3][2] = Button(CHANNEL, 66);
  buttons[3][3] = Button(CHANNEL, 67);

  // solo led
  leds[1][0] = 0x0100; // 0b 0000 0001  0000 0000
  leds[1][1] = 0x0200; // 0b 0000 0010  0000 0000
  leds[1][2] = 0x0400; // 0b 0000 0100  0000 0000
  leds[1][3] = 0x0800; // 0b 0000 1000  0000 0000
  leds[3][0] = 0x1000; // 0b 0001 0000  0000 0000
  leds[3][1] = 0x2000; // 0b 0010 0000  0000 0000
  leds[3][2] = 0x4000; // 0b 0100 0000  0000 0000
  leds[3][3] = 0x8000; // 0b 1000 0000  0000 0000

  // mute led
  leds[0][0] = 0x0001; // 0b 0000 0000  0000 0001
  leds[0][1] = 0x0002; // 0b 0000 0000  0000 0010
  leds[0][2] = 0x0004; // 0b 0000 0000  0000 0100
  leds[0][3] = 0x0008; // 0b 0000 0000  0000 1000
  leds[2][0] = 0x0010; // 0b 0000 0000  0001 0000
  leds[2][1] = 0x0020; // 0b 0000 0000  0010 0000
  leds[2][2] = 0x0040; // 0b 0000 0000  0100 0000
  leds[2][3] = 0x0080; // 0b 0000 0000  1000 0000

  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  button_pin_rows[0] = BUTTON_ROW_0;
  button_pin_rows[1] = BUTTON_ROW_1;
  button_pin_rows[2] = BUTTON_ROW_2;
  button_pin_rows[3] = BUTTON_ROW_3;

  button_pin_cols[0] = BUTTON_COL_0;
  button_pin_cols[1] = BUTTON_COL_1;
  button_pin_cols[2] = BUTTON_COL_2;
  button_pin_cols[3] = BUTTON_COL_3;

  // initialize debounce
  for (uint8_t i = 0; i < 4; i++)
  {
    for (uint8_t j = 0; j < 4; j++)
    {
      debounce[i][j] = 0;
    }
  }

  for (uint8_t i = 0; i < 4; i++)
  {
    pinMode(button_pin_rows[i], OUTPUT);
    digitalWrite(button_pin_rows[i], HIGH);

    pinMode(button_pin_cols[i], INPUT_PULLUP);
  }

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
  // BREAKS DIGITAL BUTTONS! DO NOT USE IN PROD!
  // Serial.begin(9600);

  pinMode(FADER_1, INPUT);
  pinMode(FADER_2, INPUT);
  pinMode(FADER_3, INPUT);
  pinMode(FADER_4, INPUT);
  pinMode(FADER_5, INPUT);
  pinMode(FADER_6, INPUT);
  pinMode(FADER_7, INPUT);
  pinMode(FADER_8, INPUT);

  clear_buttons();
}

void loop()
{
  // Read the voltages on every pin sequentially, per tick. Fader pins are
  // truncated by 3 bits to adhere to the 0-127 range of MIDI controls.
  for (int i = 0; i < 8; i++)
  {
    fader_voltages[i] = analogRead(fader_pins[i]) / 8;
  }

  // Run the update functions for every Button and Fader.
  for (int i = 0; i < 8; i++)
  {
    update_fader_voltage(fader_bank[i], fader_voltages[i]);
  }

  scan_buttons();
}

// Without the `&`, a copy of the button or fader is passed, and so changes are
// lost each loop. With the `&`, the object itself is passed.

/**
 * Update the passed fader. This encapsulation is not strictly necessary, but is being kept for possible future changes.
 * @param fader The Fader to be updated.
 * @param voltage_in The voltage read by the associated pin.
 */
void update_fader_voltage(Fader &fader, int voltage_in)
{
  fader.toggle(voltage_in);
}

// physical layout of buttons
//  1  2  3  4
//  9 10 11 12
//  5  6  7  8
// 13 14 15 16
void scan_buttons()
{
  // Serial.println("Scanning. . .");
  static int current_row = 0;

  digitalWrite(button_pin_rows[current_row], LOW);

  for (int current_col = 0; current_col < 4; current_col++)
  {
    if (digitalRead(button_pin_cols[current_col]) == LOW && debounce[current_row][current_col] == MAX_DEBOUNCE)
    {
      debounce[current_row][current_col] = MAX_DEBOUNCE;
    }
    else if (digitalRead(button_pin_cols[current_col]) == LOW)
    {
      debounce[current_row][current_col]++;
      if (debounce[current_row][current_col] == MAX_DEBOUNCE)
      {
        buttons[current_row][current_col].toggle();
        current_depressed = current_depressed | leds[current_row][current_col];
        digitalWrite(LATCH_PIN, 0);
        shift_out(DATA_PIN, CLOCK_PIN, current_depressed, 16);
        digitalWrite(LATCH_PIN, 1);
        // if ((current_row == 0) || (current_row == 2))
        // {
        //   // write_register(leds[current_row][current_col], 0x00);
        // }
        // else
        // {
        //   digitalWrite(LATCH_PIN, 0);
        //   shift_out(DATA_PIN, CLOCK_PIN, leds[current_row][current_col]);
        //   digitalWrite(LATCH_PIN, 1);
        //   // write_register(0x00, leds[current_row][current_col]);
        // }
      }
    }
    else
    {
      if (debounce[current_row][current_col] > 0)
      {
        debounce[current_row][current_col]--;
        current_depressed = current_depressed ^ leds[current_row][current_col];
        digitalWrite(LATCH_PIN, 0);
        shift_out(DATA_PIN, CLOCK_PIN, current_depressed, 16);
        digitalWrite(LATCH_PIN, 1);
      }
    }
  }

  digitalWrite(button_pin_rows[current_row], HIGH);

  current_row++;
  if (current_row > 3)
  {
    current_row = 0;
  }
}

void shift_out(int data_pin, int clock_pin, uint16_t data_out, int data_size)
{
  int pin_state;
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  digitalWrite(data_pin, 0);
  digitalWrite(clock_pin, 0);

  for (int i = data_size - 1; i >= 0; i--)
  {
    digitalWrite(clock_pin, 0);
    if (data_out & (1 << i))
    {
      pin_state = 1;
    }
    else
    {
      pin_state = 0;
    }

    digitalWrite(data_pin, pin_state);
    digitalWrite(clock_pin, 1);
    digitalWrite(data_pin, 0);
  }
  digitalWrite(clock_pin, 0);
}

void clear_buttons()
{
  digitalWrite(LATCH_PIN, 0);
  shift_out(DATA_PIN, CLOCK_PIN, 0x0000, 16);
  digitalWrite(LATCH_PIN, 1);
}