#ifndef COMMS_H
#define COMMS_H
#define _XTAL_FREQ 8000000  // 8 MHz clock for delay calculation

// Pin definitions for USB communication
#define WP RA0   // Set high to lock
#define SDA RA1  // Serial data
#define SCL RA2  // Serial clock
#define MCLR RA3 // Ignore
#define DPLUS RA4  // D+ (RA4)
#define DMINUS RA5 // D- (RA5)

// Main function prototypes
void send_keystroke(void);
void write_rom(void);
void read_rom(void);
void write_ram(uint8_t* data, uint8_t start_addr);
void read_ram(uint8_t start, uint8_t range);
void check_ram(void);
void clear_ram(void);

// I2C function prototypes
void i2c_delay(void);            // I2C delay function for proper timing
void i2c_start(void);            // Generate I2C Start condition
void i2c_stop(void);
void i2c_send_byte(uint8_t data); // Send one byte of data via I2C
uint8_t i2c_receive_byte(void);  // Receive one byte of data via I2C
void i2c_wp_start(void);         // Declare i2c_wp_start function
void i2c_wp_stop(void);         // Declare i2c_wp_stop function
void eeprom_write(uint8_t mem_addr, uint8_t data);
void eeprom_write_string(uint8_t start_addr, const char* str);          // Generate I2C Stop condition

// USB function prototypes
void delay_us(uint16_t us);            // USB delay function in microseconds
void usb_send_bit(uint8_t bit);        // Send one bit of data via USB
void usb_send_byte(uint8_t data);      // Send one byte of data via USB
void usb_send_report(uint8_t *report); // Send a USB HID report

// Function prototypes for keycode and RAM functions
uint8_t get_keycode(char key);  // Declare get_keycode function

// External declarations for global variables
extern const uint8_t keycodes[]; // Declare keycodes as an external array

#endif // COMMS_H
