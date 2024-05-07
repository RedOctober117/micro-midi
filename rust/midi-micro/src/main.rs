// This project uses the "arduino-leonardo" feature because the leonardo uses the same architecture as the micro, ATmega32u4.
// using https://github.com/btrepp/usbd-midi

#![no_std]
#![no_main]

use arduino_hal::hal::delay;
use panic_halt as _;
use usbd_midi::midi_device::MidiClass;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    // let usb = dp.USB_DEVICE;

    // let mut midi = MidiClass::new(usb);

    let mut led = pins.led_rx.into_output();
    // let mut buttons = pins.a0.into_analog_input(adc);
    // let mut fader_1 = pins.a1.into_analog_input(adc);
    // let mut fader_2 = pins.a2.into_analog_input(adc);
    // let mut fader_3 = pins.a3.into_analog_input(adc);
    // let mut fader_4 = pins.a4.into_analog_input(adc);

    loop {
        led.set_high();
        // delay(500);
        // led.set_low();
        // delay(500);
    }
}

// fn momentary_command(midi: MidiClass, channel: u8, pitch: u8, duration: u8) {

// }