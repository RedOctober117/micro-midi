#ifndef SHIFT_OUT_REGISTER_HPP
#define SHIFT_OUT_REGISTER_HPP

#include <Arduino.h>

struct ShiftOutRegister2
{
    uint16_t current_value;
    uint8_t total_registers;
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t latch_pin;
};

void shift_out(ShiftOutRegister2 reg, uint16_t outbound_data, uint8_t data_size);

void write(ShiftOutRegister2 &reg, uint8_t outbound_data, uint8_t target_reg);

void erase_bit(ShiftOutRegister2 &reg, uint8_t outbound_data, uint8_t target_reg);

void bits_to_serial(int bits, unsigned int size);
#endif