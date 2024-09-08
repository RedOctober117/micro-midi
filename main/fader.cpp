#include "fader.hpp"

Fader::Fader() { }

Fader::Fader(byte channel, byte pitch) {
  this->channel = channel;
  this->pitch = pitch;
  this->current_voltage = 0;
}

void Fader::toggle(int voltage) {
  if (getVoltage() == 0 && voltage < 19) {
    return;
  }

  if (voltage > getVoltage() + 1 || voltage < getVoltage() - 1) {
    if (voltage < 19) {
      setVoltage(0);
      Control::toggle(getVoltage());
    } else {
      setVoltage(voltage);
      Control::toggle(getVoltage());
      Serial.print("TOGGLED FADER: ");
      Serial.println(getVoltage());
    }
  }
}

int Fader::getVoltage() {
  return this->current_voltage;
}

void Fader::setVoltage(int voltage) {
  this->current_voltage = voltage;
}