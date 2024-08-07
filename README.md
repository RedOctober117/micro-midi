# Button

For the purposes of this project, buttons have a single function: send an on or off signal. This iteration does not know the state of the program, and so each button is set to an `off` state. The first press of a button will send the on signal. 

## State

The state of the button is checked every loop. Because every button in a given bank lives on the same data line, buttons are assigned voltage highs and lows. If the voltage of the line is between those bounds at the start of a loop, that button is toggled. 

## Effect

When a button is toggled, a signal is sent via the MIDI command set, and its internal state variable is NOT-ed.

# Fader

Faders send a signal every time there position (and thus, their voltage) changes. Faders will automatically send the position they're in as soon as the board is booted.

## State
The only state relevant to a fader is its last voltage. Every loop, if the voltage has changed, the state is updated to that voltage BEFORE the command is sent.

## Effect

When a fader is moved, its internal voltage state is updated, and a signal is sent with that new state.