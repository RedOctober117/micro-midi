#include "fader.hpp"

Fader::Fader() { }

Fader::Fader(byte channel, byte pitch) {
  this->channel = channel;
  this->pitch = pitch;
  this->current_voltage = 0;
}

void Fader::toggle(int voltage) {
  // Serial.println(getVoltage());
  if (voltage != getVoltage()) {
    setVoltage(voltage);
    toggle(getVoltage());
    Serial.print("TOGGLED FADER: ");
    Serial.println(getVoltage());
  }
}

int Fader::getVoltage() {
  return this->current_voltage;
}

void Fader::setVoltage(int voltage) {
  this->current_voltage = voltage;
}