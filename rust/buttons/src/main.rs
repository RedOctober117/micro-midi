#![no_std]
#![no_main]

use heapless::Vec;
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    let num_rows: u8 = 2;
    let num_cols: u8 = 2;
    let mut current_row: u8 = 0;

    // row: high
    // col: low
    let mut rows: Vec<_, 2> = Vec::new();
    let _ = rows.push(pins.a0.into_output().downgrade());
    let _ = rows.push(pins.a1.into_output().downgrade());

    for pin in &mut rows {
        pin.set_high();
    }

    let mut cols: Vec<_, 2> = Vec::new();
    let _ = cols.push(pins.a2.into_pull_up_input().downgrade());
    let _ = cols.push(pins.a3.into_pull_up_input().downgrade());

    let mut leds: Vec<_, 4> = Vec::new();
    let _ = leds.push(pins.d4.into_output().downgrade());
    let _ = leds.push(pins.d5.into_output().downgrade());
    let _ = leds.push(pins.d6.into_output().downgrade());
    let _ = leds.push(pins.d7.into_output().downgrade());

    loop {
        for led in &mut leds {
            led.set_low();
        }

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
