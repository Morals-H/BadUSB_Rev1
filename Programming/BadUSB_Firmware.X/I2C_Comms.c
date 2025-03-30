#include <xc.h>
#include "Comms.h"

// I2C Delay function for proper timing
void i2c_delay() {
    __delay_us(5);  // Adjust this delay for proper timing (5 microseconds)
}

// I2C Start condition
void i2c_start() {
    SDA = 1;     // Ensure SDA is high
    SCL = 1;     // Ensure SCL is high
    i2c_delay(); // Small delay
    SDA = 0;     // Generate Start condition
    i2c_delay(); 
    SCL = 0;     // Pull clock low
}

// I2C Stop condition
void i2c_stop() {
    SDA = 0;     // Ensure SDA is low
    SCL = 1;     // Generate Stop condition
    i2c_delay();
    SDA = 1;     // Release SDA
    i2c_delay();
}

// Send one byte of data (8 bits)
void i2c_send_byte(uint8_t data) {
    for (int8_t i = 7; i >= 0; i--) {
        if (data & (1 << i)) {
            SDA = 1;  // Set SDA for '1'
        } else {
            SDA = 0;  // Set SDA for '0'
        }
        i2c_delay();
        SCL = 1;    // Clock pulse
        i2c_delay();
        SCL = 0;    // Pull clock low
    }
}

// Enable write protection of the ROM Chip
void i2c_wp_start() 
{
    WP = 1;
}

// Disable write protection of the ROM Chip
void i2c_wp_stop() 
{
    WP = 0;
}

// Read one byte from the I2C bus
uint8_t i2c_receive_byte() {
    uint8_t received_data = 0;
    SDA = 1;  // Release SDA for input
    for (int8_t i = 7; i >= 0; i--) {
        i2c_delay();
        SCL = 1;    // Clock pulse
        i2c_delay();
        if (SDA) {
            received_data |= (1 << i);  // Read bit and store it
        }
        SCL = 0;    // Pull clock low
    }
    return received_data;
}

// Write one byte to the EEPROM
void eeprom_write(uint8_t mem_addr, uint8_t data) {
    i2c_start();  // Start I2C communication

    // Send EEPROM device address + write command
    i2c_send_byte(0xA0);  // 0xA0 is the 7-bit device address with write bit

    // Send the memory address where we want to write (high byte)
    i2c_send_byte(mem_addr);  // Memory address

    // Send the data to be written
    i2c_send_byte(data);  // Data byte to write

    i2c_stop();  // Stop I2C communication

    __delay_ms(5);  // Small delay to ensure EEPROM has time to write
}

// Write a string of data to the EEPROM
void eeprom_write_string(uint8_t start_addr, const char* str) {
    uint8_t i = 0;
    while (str[i] != '\0') {  // Loop until we reach the null-terminator
        eeprom_write(start_addr + i, str[i]);  // Write each character
        i++;
    }
}
