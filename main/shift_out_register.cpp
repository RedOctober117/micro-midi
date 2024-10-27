#include "shift_out_register.hpp"

ShiftOutRegister new_register(uint8_t total_registers, uint8_t data_pin, uint8_t clock_pin, uint8_t latch_pin)
{
    ShiftOutRegister reg = {
        {0},
        total_registers,
        data_pin,
        clock_pin,
        latch_pin};

    return reg;
}

void shift_out(ShiftOutRegister reg, uint8_t &outbound_data, uint8_t &data_size)
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
        // Serial.print(pin_state);

        digitalWrite(reg.data_pin, pin_state);
        digitalWrite(reg.clock_pin, 1);
        digitalWrite(reg.data_pin, 0);
    }
    // Serial.println();
    digitalWrite(reg.clock_pin, 0);
}

/// @brief writes data to registers, preserving current state of all other registers
/// @param reg
/// @param outbound_data
/// @param target_reg
void write(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg)
{
    int offset = target_reg * 8;
    uint16_t offset_outbound_data = outbound_data << offset;

    // bits_to_serial(offset_outbound_data, (8 * sizeof(offset_outbound_data)));

    reg.current_values[target_reg] = reg.current_value | offset_outbound_data;

    uint8_t size = (8 * sizeof(reg.current_value));

    digitalWrite(reg.latch_pin, 0);
    shift_out(reg, reg.current_value, size);
    digitalWrite(reg.latch_pin, 1);
}

void erase_bit(ShiftOutRegister &reg, uint8_t outbound_data, uint8_t target_reg)
{

    int offset = target_reg * 8;
    uint16_t offset_outbound_data = outbound_data << offset;

    // bits_to_serial(offset_outbound_data, (8 * sizeof(offset_outbound_data)));

    reg.current_value = reg.current_value ^ offset_outbound_data;
    // bits_to_serial(reg.current_value, (8 * sizeof(reg.current_value)));

    digitalWrite(reg.latch_pin, 0);
    shift_out(reg, reg.current_value, (8 * sizeof(reg.current_value)));
    digitalWrite(reg.latch_pin, 1);
}

/// @brief Prints bits to serial in BE.
/// @param bits
/// @param size
void bits_to_serial(int bits, unsigned int size)
{
    for (int i = size - 1; i >= 0; i--)
    {
        Serial.print((bits & (1 << i)));
    }
    Serial.println();
}