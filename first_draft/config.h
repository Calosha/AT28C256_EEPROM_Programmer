#ifndef CONFIG_H
#define CONFIG_H

// Pin definitions for the shift register
#define SHIFT_LATCH_PIN 10
#define SHIFT_DATA_PIN 17
#define SHIFT_CLK_PIN 19

// Pin definitions for AT28C256 EEPROM
// Control
#define CE_PIN 14  // Chip Enable
#define OE_PIN 15  // Output Enable
#define WE_PIN 16  // Write Enable

// Pin definitions for SD card reader
#define SD_CS_PIN 18

// Data pins
static const int DATA_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};

#define ROM_SIZE 32768 // Using size instead of last address to be able to put > (strictly less)
#endif  // CONFIG_H
