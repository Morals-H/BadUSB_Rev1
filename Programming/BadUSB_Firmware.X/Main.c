#include <xc.h>
#include "Comms.h"

#define RAM_START_ADDR 0x20
#define RAM_END_ADDR   0xFF
#define RESERVED_START 0x20
#define RESERVED_END   0x30
#define ROM_START_ADDR 0x00
#define ROM_END_ADDR   0xFF

volatile uint8_t* ram_ptr = (uint8_t*)0x20;  // Pointer to the current RAM location
volatile uint8_t* rom_ptr = (uint8_t*)0x21;  // Pointer to the current ROM location

void main() {
    // Initialize write protection on the ROM Chip
    i2c_wp_start();
    
    while (1) {
        // Main loop here
    }
}

// Read ROM and pass the data to write_ram
void read_rom() {
    uint8_t data[8];  // Buffer to hold 8 bytes at a time
    uint16_t i;
    for (i = ROM_START_ADDR; i < ROM_END_ADDR; i += 8) {
        for (uint8_t j = 0; j < 8; j++) {
            data[j] = *(volatile uint8_t*) i + j;
        }
        write_ram(data, 0x22);  // Write to RAM starting at address 0x22
    }
}
// Write to ROM
void write_rom() {
    i2c_wp_stop();
    eeprom_write_string(0x00, "Hello");
}

// Reads data from RAM
void read_ram(uint8_t start, uint8_t range) {
    uint8_t i;
    for (i = start; i < (start + range); i++) {
        if (*(volatile uint8_t*)(i) != 0x00) {  // Dereference address correctly
            *(volatile uint8_t*)0x2B = *(volatile uint8_t*)(i);  // Copy value to address 0x2B
            send_keystroke();  // Call the keystroke function
        }
    }
    read_rom();  // Call read_rom after loop
}

// Writes to reserved RAM, handling overflow if needed
void write_ram(uint8_t* data, uint8_t start_addr) {
    uint8_t i;
    for (i = 0; i < 8; i++) {
        *(volatile uint8_t*)(start_addr + i) = data[i];
    }

    // If RAM is getting full, check and handle overflow
    check_ram();
}
// Checks if the usable RAM is getting full
void check_ram() {
    uint8_t* temp_ptr;
    for (temp_ptr = (uint8_t*)RAM_START_ADDR; temp_ptr <= (uint8_t*)RAM_END_ADDR; temp_ptr++) {
        if (*temp_ptr == 0xFF) {
            clear_ram();
            break;
        }
    }
}
// Clears usable RAM safely
void clear_ram() {
    uint8_t i;
    for (i = RAM_START_ADDR; i <= RAM_END_ADDR; i++) {
        if (i < RESERVED_START || i > RESERVED_END) {
            *(volatile uint8_t*) (uintptr_t)i = 0x00;  // Cast i to a pointer correctly
        }
    }
}



// Preparing and sending the keystroke
void send_keystroke() {
    uint8_t report[8] = {0};  // Initialize with 0s

    char key = *(volatile uint8_t*) 0x2B;  // Get the key stored at 0x2B in RAM
    uint8_t keycode = get_keycode(key);

    if (keycode != 0x00) {
        report[2] = keycode;
    }

    // Check if the Windows key is held down
    if (*(volatile uint8_t*) 0x2C == 1) {
        report[0] = 0xE3;
    } else {
        report[0] = 0x00;
    }

    usb_send_report(report);
    check_ram();
    read_ram(0x22, 8);
}
