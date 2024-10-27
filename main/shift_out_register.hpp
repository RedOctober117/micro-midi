#ifndef SHIFT_OUT_REGISTER_HPP
#define SHIFTOUT_REGISTER_HPP

#include <Arduino.h>

struct ShiftOutRegister
{
    uint8_t current_values;
    uint8_t total_registers;
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t latch_pin;
};

ShiftOutRegister new_register(uint8_t total_registers, uint8_t data_pin, uint8_t clock_pin, uint8_t latch_pin);

void shift_out(ShiftOutRegister reg, uint8_t &outbound_data, uint8_t &data_size);

void write(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg);

void erase_bit(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg);

void bits_to_serial(int bits, unsigned int size);
#endif