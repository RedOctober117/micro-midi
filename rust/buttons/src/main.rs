#![no_std]
#![no_main]

use heapless::Vec;
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);
    // if you need adc, https://github.com/Rahix/avr-hal/blob/main/examples/arduino-leonardo/src/bin/leonardo-adc.rs

    let num_rows: u8 = 2;
    let num_cols: u8 = 2;
    let mut current_row: u8 = 0;

    // rows are initialized to output and then set to high, their default
    // state.
    // cols are initialized to a pullup state, their default state.
    let mut rows: Vec<_, 2> = Vec::new();
    let _ = rows.push(pins.a0.into_output().downgrade());
    let _ = rows.push(pins.a1.into_output().downgrade());

    for pin in &mut rows {
        pin.set_high();
    }

    let mut cols: Vec<_, 2> = Vec::new();
    let _ = cols.push(pins.a2.into_pull_up_input().downgrade());
    let _ = cols.push(pins.a3.into_pull_up_input().downgrade());

    // the four test leds, one for each button, top to bottom, left to right.
    let mut leds: Vec<_, 4> = Vec::new();
    let _ = leds.push(pins.d4.into_output().downgrade());
    let _ = leds.push(pins.d5.into_output().downgrade());
    let _ = leds.push(pins.d6.into_output().downgrade());
    let _ = leds.push(pins.d7.into_output().downgrade());

    loop {
        // set all leds to low. this effect is so fast to the human eye that
        // nothing visibily changes even if a button is still depressed.
        for led in &mut leds {
            led.set_low();
        }

        // set the current row to low, and see what columns get pulled down with it.
        // https://www.dribin.org/dave/keyboard/one_html/
        rows[current_row as usize].set_low();
        for i in 0..num_cols {
            if let Some(pin) = cols.get(i as usize) {
                if pin.is_low() {
                    if current_row == 0 {
                        leds[(current_row + i) as usize].set_high();
                    } else {
                        leds[(current_row + i + 1) as usize].set_high();
                    }
                }
            }
        }

        rows[current_row as usize].set_high();
        current_row = current_row + 1;
        if current_row >= num_rows {
            current_row = 0;
        }
    }
}
