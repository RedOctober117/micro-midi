#include "fader.hpp"

Fader::Fader() { }

Fader::Fader(byte channel, byte pitch) {
  this->channel = channel;
  this->pitch = pitch;
  this->previous_voltage = 0;
}

void Fader::set_voltage(int voltage) {
  this->previous_voltage = voltage;
}

// void Fader::toggle() {
//   if (this->current_voltage != this->previous_voltage) {
//     Control::toggle(this->current_voltage);
//     Serial.print("PREVIOUS VOLTAGE: ");
//     Serial.println(this->previous_voltage);
//     Serial.print("CURRENT VOLTAGE: ");
//     Serial.println(this->current_voltage);
//     // this->previous_voltage = this->current_voltage;
//   }
// }