#ifndef FADER_H
#define FADER_H

#include "control.hpp"

/**
 * The Fader class, derived from Control.
 */
class Fader : public Control{
  public:
    /// Current voltage, as read by the board and passed to the Fader by setVoltage(int)
    int current_voltage;
<<<<<<< Updated upstream
    // int previous_voltage;
=======

    /// Default constructor for a Fader.
>>>>>>> Stashed changes
    Fader ();

    /// Overloaded constructor for Fader, receiving a channel and pitch.
    /// @param  channel Byte value denoting the channel of the Fader.
    /// @param  pitch Byte value denoting the pitch, or velocity, of the fader.
    Fader (byte, byte);

    /// Toggles the fader using super::toggle(), if conditions are met.
    /// @param  voltage Integer voltage read by the associated pin.
    void toggle(int);
<<<<<<< Updated upstream
    // void set_voltage(int);
=======
    
    /// Setter to update the voltage.
    /// @param  voltage Integer voltage read by the associated pin.
>>>>>>> Stashed changes
    void setVoltage(int);

    /// Getter to return the currently stored voltage.
    /// @return Integer voltage.
    int getVoltage();
};


#endif