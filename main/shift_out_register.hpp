#ifndef SHIFT_OUT_REGISTER_HPP
#define SHIFTOUT_REGISTER_HPP

#include <Arduino.h>

struct ShiftOutRegister
{
    unsigned int current_value;
    uint8_t total_registers;
    uint8_t data_pin;
    uint8_t clock_pin;
    uint8_t latch_pin;
};

void shift_out(ShiftOutRegister reg, unsigned long outbound_data, unsigned int data_size);

void write(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg);

void erase_bit(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg);
#endif