#![no_std]
#![no_main]

use arduino_hal::*;
use heapless::Vec;
use panic_halt as _;
use port::mode::Output;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = Peripherals::take().unwrap();
    let pins = pins!(dp);

    /*
     * For examples (and inspiration), head to
     *
     *     https://github.com/Rahix/avr-hal/tree/main/examples
     *
     * NOTE: Not all examples were ported to all boards!  There is a good chance though, that code
     * for a different board can be adapted for yours.  The Arduino Uno currently has the most
     * examples available.
     */

    let mut leds: Vec<port::Pin<Output>, 4> = Vec::new();
    let _ = leds.push(pins.a0.into_output().downgrade());
    let _ = leds.push(pins.a1.into_output().downgrade());
    let _ = leds.push(pins.a2.into_output().downgrade());
    let _ = leds.push(pins.a3.into_output().downgrade());

    loop {
        for led in &mut leds {
            led.toggle();
            arduino_hal::delay_ms(250);
            led.toggle();
        }
    }
}
