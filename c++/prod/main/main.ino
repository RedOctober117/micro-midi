#include <Arduino.h>
#include "vins.hpp"
#include "midi.hpp"
#include <HardwareSerial.h>

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

class Control {
  public:
    int target_voltage;
    int previous_voltage;
    byte channel;
    byte pitch;

  Control ();
  Control (int, byte, byte);

  void toggle(byte);
  void momentary(byte);
};

Control::Control() { }

Control::Control(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}

void Control::toggle(byte velocity) {
  latch_command(channel, pitch, velocity);
}

void Control::momentary(byte duration) {
  momentary_command(channel, pitch, duration);
}

class Button : public Control {
  public:
    boolean latched;
    int previous_velocity;
    Button ();
    Button (int, byte, byte);
};

Button::Button() { }

Button::Button(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}

class Fader : public Control{
  public:
    Fader ();
    Fader (int, byte, byte);
};

Fader::Fader() { }

Fader::Fader(int voltage, byte channel, byte pitch) {
  this->target_voltage = voltage;
  this->channel = channel;
  this->pitch = pitch;
}

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

// const int BUTTON_1 = 31;
// const int BUTTON_2 = 27;
// const int BUTTON_3 = 23;
// const int BUTTON_4 = 19;
// const int BUTTON_5 = 15;
// const int BUTTON_6 = 12;
// const int BUTTON_7 = 8;
// const int BUTTON_8 = 4;

// const int button_ranges[8] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8};

// int fader_1_volt = 0;
// int fader_2_volt = 0;
// int fader_3_volt = 0;
// int fader_4_volt = 0;
// int fader_5_volt = 0;
// int fader_6_volt = 0;
// int fader_7_volt = 0;
// int fader_8_volt = 0;

// int fader_1_prev = 0;
// int fader_2_prev = 0;
// int fader_3_prev = 0;
// int fader_4_prev = 0;
// int fader_5_prev = 0;
// int fader_6_prev = 0;
// int fader_7_prev = 0;
// int fader_8_prev = 0;

// bool button_bank_1_pressed = false;
// bool button_bank_2_pressed = false;

// int button_bank_1_voltage;
// int button_bank_2_voltage;
// int previous_button_bank_1_voltage;
// int previous_button_bank_2_voltage;

// uint8_t muxed_buttons = 0;
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
  // button__bank_1_voltage = analogRead(BUTTON_BANK_1) / 32;
  // button__bank_2_voltage = analogRead(BUTTON_BANK_2) / 32;
  // read_faders();

  // if (button_voltage != previous_button_voltage)
  // {
  //   solo_mute();
  // }

  // if (fader_1_volt > fader_1_prev || fader_1_volt < fader_1_prev)
  // {
  //   latch_command(0, 41, fader_1_volt);
  // }

  // set_fader_previous();
  // set_button_previous();
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



// void read_buttons_with_muxer()
// {
//   switch (button_voltage)
//   {
//   case BUTTON_1:
//     muxed_buttons = muxed_buttons | (byte)00000001;
//     break;
//   case BUTTON_2:
//     muxed_buttons = muxed_buttons | (byte)00000010;
//     break;
//   case BUTTON_3:
//     muxed_buttons = muxed_buttons | (char)00000100;
//     break;
//   case BUTTON_4:
//     muxed_buttons = muxed_buttons | (char)00001000;
//     break;
//   case BUTTON_5:
//     muxed_buttons = muxed_buttons | (char)00010000;
//     break;
//   case BUTTON_6:
//     muxed_buttons = muxed_buttons | (char)00100000;
//     break;
//   case BUTTON_7:
//     muxed_buttons = muxed_buttons | (char)01000000;
//     break;
//   case BUTTON_8:
//     muxed_buttons = muxed_buttons | (char)10000000;
//     break;
//   default:
//     break;
//   }
// }

// void test_read_buttons()
// {
//   if (button_voltage > BUTTON_1)
//   {
//     Serial.println("Button 1");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_2)
//   {
//     Serial.println("Button 2");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_3)
//   {
//     Serial.println("Button 3");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_4)
//   {
//     Serial.println("Button 4");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_5)
//   {
//     Serial.println("Button 5");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_6)
//   {
//     Serial.println("Button 6");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_7)
//   {
//     Serial.println("Button 7");
//     Serial.println(button_voltage);
//   }
//   else if (button_voltage > BUTTON_8)
//   {
//     Serial.println("Button 8");
//     Serial.println(button_voltage);
//   }
// }

// void set_button_previous()
// {
//   previous_button_voltage = button_voltage;
// }

//
// B1 B2 ...
// B9 B10 ...
//

// void focus()
// {
//   // B9
//   if (button_bank_2_voltage > BUTTON_9_LOWER && button_bank_2_voltage < BUTTON_9_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B10
//   else if (button_bank_2_voltage > BUTTON_10_LOWER && button_bank_2_voltage < BUTTON_10_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B11
//   else if (button_bank_2_voltage > BUTTON_11_LOWER && button_bank_2_voltage < BUTTON_11_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B12
//   else if (button_bank_2_voltage > BUTTON_12_LOWER && button_bank_2_voltage < BUTTON_12_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B13
//   else if (button_bank_2_voltage > BUTTON_13_LOWER && button_bank_2_voltage < BUTTON_13_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B14
//   else if (button_bank_2_voltage > BUTTON_14_LOWER && button_bank_2_voltage < BUTTON_14_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B15
//   else if (button_bank_2_voltage > BUTTON_15_LOWER && button_bank_2_voltage < BUTTON_15_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
//   // B16
//   else if (button_bank_2_voltage > BUTTON_16_LOWER && button_bank_2_voltage < BUTTON_16_UPPER)
//   {
//     if (button_bank_2_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_2_pressed = false;
//     }
//   }
// }

// void solo_mute()
// {
//   // B1
//   if (button_bank_1_voltage > BUTTON_1_LOWER && button_bank_1_voltage < BUTTON_1_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 51, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B2
//   else if (button_bank_1_voltage > BUTTON_2_LOWER && button_bank_1_voltage < BUTTON_2_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B3
//   else if (button_bank_1_voltage > BUTTON_3_LOWER && button_bank_1_voltage < BUTTON_3_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 53, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B4
//   else if (button_bank_1_voltage > BUTTON_4_LOWER && button_bank_1_voltage < BUTTON_4_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 54, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B5
//   else if (button_bank_1_voltage > BUTTON_5_LOWER && button_bank_1_voltage < BUTTON_5_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 55, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B6
//   else if (button_bank_1_voltage > BUTTON_6_LOWER && button_bank_1_voltage < BUTTON_6_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 56, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B7
//   else if (button_bank_1_voltage > BUTTON_7_LOWER && button_bank_1_voltage < BUTTON_7_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 57, 0);
//       button_bank_1_pressed = false;
//     }
//   }
//   // B8
//   else if (button_bank_1_voltage > BUTTON_8_LOWER && button_bank_1_voltage < BUTTON_8_UPPER)
//   {
//     if (button_bank_1_pressed)
//     {
//       latch_command(0, 52, 0);
//       button_bank_1_pressed = false;
//     }
//     // switch (button_voltage) {
//     //   case BUTTON_1:
//     //     if(button_1_pressed) {
//     //       latch_command(0, 51, 0);
//     //       button_1_pressed = false;
//     //       break;
//     //     }
//     //     latch_command(0, 51, 127);
//     //     button_1_pressed = true;
//     //     break;
//     //   case BUTTON_2:
//     //     momentary_command(0, 52, 50);
//     //     break;
//     //   case BUTTON_3:
//     //     momentary_command(0, 53, 50);
//     //     break;
//     //   case BUTTON_4:
//     //     momentary_command(0, 54, 50);
//     //     break;
//     //   case BUTTON_5:
//     //     momentary_command(0, 55, 50);
//     //     break;
//     //   case BUTTON_6:
//     //     momentary_command(0, 56, 50);
//     //     break;
//     //   case BUTTON_7:
//     //     momentary_command(0, 57, 50);
//     //     break;
//     //   case BUTTON_8:
//     //     momentary_command(0, 58, 50);
//     //     break;
//     //   default:
//     //     break;
//   }
// }
