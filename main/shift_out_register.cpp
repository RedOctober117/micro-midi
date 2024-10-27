#include "shift_out_register.hpp"

void shift_out(ShiftOutRegister reg, unsigned long outbound_data, unsigned int data_size)
{
    int pin_state;
    pinMode(reg.clock_pin, OUTPUT);
    pinMode(reg.data_pin, OUTPUT);

    digitalWrite(reg.data_pin, 0);
    digitalWrite(reg.clock_pin, 0);

    for (int i = data_size - 1; i >= 0; i--)
    {
        digitalWrite(reg.clock_pin, 0);
        if (outbound_data & (1 << i))
        {
            pin_state = 1;
        }
        else
        {
            pin_state = 0;
        }
        Serial.print(pin_state);

        digitalWrite(reg.data_pin, pin_state);
        digitalWrite(reg.clock_pin, 1);
        digitalWrite(reg.data_pin, 0);
    }
    Serial.println();
    digitalWrite(reg.clock_pin, 0);
}

/// @brief writes data to registers, preserving current state of all other registers
/// @param reg
/// @param outbound_data
/// @param target_reg
void write(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg)
{
    int offset = target_reg * 8;
    unsigned int offset_outbound_data = outbound_data;
    for (int i = offset - 1; i >= 0; i--)
    {
        offset_outbound_data = offset_outbound_data << 1;
    }
    Serial.println(reg.current_value);
    reg.current_value = reg.current_value | offset_outbound_data;
    Serial.println(reg.current_value);
    digitalWrite(reg.latch_pin, 0);

    shift_out(reg, offset_outbound_data, (8 * sizeof(offset_outbound_data)));

    digitalWrite(reg.latch_pin, 1);
}

void erase_bit(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg)
{
    int offset = target_reg * 8;
    unsigned int offset_outbound_data = outbound_data;
    for (int i = offset - 1; i >= 0; i--)
    {
        offset_outbound_data = offset_outbound_data << 1;
    }

    reg.current_value = reg.current_value ^ offset_outbound_data;
    digitalWrite(reg.latch_pin, 0);

    shift_out(reg, reg.current_value, (8 * sizeof(reg.current_value)));

    digitalWrite(reg.latch_pin, 1);
}