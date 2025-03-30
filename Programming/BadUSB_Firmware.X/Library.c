#include <stdint.h>
#include "Comms.h"

// Function to convert character to HID keycode
uint8_t get_keycode(char key) {
    if (key >= 0 && key < 128) {
        return keycodes[(uint8_t)key];
    }
    return 0x00; // Return 0x00 if key is outside the printable range
}

// HID Keycodes (some common ones as an example)
const uint8_t keycodes[128] = { 
    0x00, // NUL
    0x00, // SOH
    0x00, // STX
    0x00, // ETX
    0x00, // EOT
    0x00, // ENQ
    0x00, // ACK
    0x00, // BEL
    0x2A, // Backspace (HID keycode for backspace)
    0x2B, // Tab
    0x28, // Enter
    0x00, // (Reserved)
    0x00, // (Reserved)
    0x00, // (Reserved)
    0x00, // (Reserved)
    0x2F, // Space
    0x1E, // '1' key
    0x1F, // '2' key
    0x20, // '3' key
    0x21, // '4' key
    0x22, // '5' key
    0x23, // '6' key
    0x24, // '7' key
    0x25, // '8' key
    0x26, // '9' key
    0x27, // '0' key
    0x04, // 'a' key
    0x05, // 'b' key
    0x06, // 'c' key
    0x07, // 'd' key
    0x08, // 'e' key
    0x09, // 'f' key
    0x0A, // 'g' key
    0x0B, // 'h' key
    0x0C, // 'i' key
    0x0D, // 'j' key
    0x0E, // 'k' key
    0x0F, // 'l' key
    0x10, // 'm' key
    0x11, // 'n' key
    0x12, // 'o' key
    0x13, // 'p' key
    0x14, // 'q' key
    0x15, // 'r' key
    0x16, // 's' key
    0x17, // 't' key
    0x18, // 'u' key
    0x19, // 'v' key
    0x1A, // 'w' key
    0x1B, // 'x' key
    0x1C, // 'y' key
    0x1D, // 'z' key
    0x2D, // '-' key
    0x2E, // '=' key
    0x2F, // '[' key
    0x30, // '\\' key
    0x31, // ']' key
    0x32, // ';' key
    0x33, // '\'' key
    0x34, // '`' key
    0x35, // ',' key
    0x36, // '.' key
    0x37, // '/' key
    0x38, // Space
    0xE3, // Left Windows Key
    0x04 | 0x02, // 'A' -> Shift + 'a'
    0x05 | 0x02, // 'B' -> Shift + 'b'
    // Add the remaining keys here...
};
