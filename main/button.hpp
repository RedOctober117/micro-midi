#ifndef BUTTON_H
#define BUTTON_H

#include "control.hpp"

/// Button class, derived from Control.
class Button : public Control {
  public:
    /// The top bound voltage for the button.
    int voltage_high;

    /// The lower bound voltage for the button.
    int voltage_low;

    /// The previous velocity the button sent.
    int previous_velocity;

    /// Default button constructor.
    Button ();
    
    /// Overloaded Button constructor, receiving the voltage bounds, channel, and pitch.
    /// @param  voltage_low Integer lower bound voltage.
    /// @param  voltage_high Integer upper bound voltage.
    /// @param  channel Byte channel on which to send commands.
    /// @param  pitch Byte pitch, or velocity, that defines the MIDI command sent.
    Button (int, int, byte, byte);

    /// Toggles the button using super::toggle(), if conditions are met.
    /// @param  voltage Integer voltage read by the associated pin. 
    /// @param delay_amount Integer time in ms to wait before allowing another update.
    void toggle(int, int);
};

#endif