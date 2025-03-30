#include <xc.h>
#include "Comms.h"

// Function to create a microsecond delay
void delay_us(uint16_t us) {
    while (us--) {
        __delay_us(1);  // 1 microsecond delay
    }
}

// Function to send a single bit via USB (bit-banging)
void usb_send_bit(uint8_t bit) {
    if (bit == 1) {
        DPLUS = 1;  // Set D+ high
        DMINUS = 0; // Set D- low
    } else {
        DPLUS = 0;  // Set D+ low
        DMINUS = 1; // Set D- high
    }
    delay_us(1);  // Bit duration (1 bit = 640 ns at 1.5 Mbps)
}

// Function to send one byte via USB (8 bits)
void usb_send_byte(uint8_t data) {
    for (uint8_t i = 0; i < 8; i++) {
        usb_send_bit((data >> i) & 1);  // Send bits LSB first
    }
}

// Function to send a full USB HID report (8 bytes)
void usb_send_report(uint8_t *report) {
    for (uint8_t i = 0; i < 8; i++) {
        usb_send_byte(report[i]);  // Send each byte of the report
    }
}
