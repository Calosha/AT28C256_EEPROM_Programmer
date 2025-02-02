// TODO: write protection to make sure that our programmer is writeEnabled when using write operation
// TODO: play with binary operations and uint8 to see hex, mask, & , >> stuff
#include <Arduino.h>
#include "EEPROMProgrammer.h"

EEPROMProgrammer programmer;
void setup() {
  // Start serial monitor on port 9600
  Serial.begin(9600);
  // Setup shift regisers
  programmer.begin();
}

void loop() {
      // write first 32 addresses 0x00 to 0x1F
      uint16_t address = 0;
      uint8_t data = 0;
      for (int i = 0; i < 32; i++) {
        Serial.print("Address: ");
        Serial.println(address, HEX);
        Serial.print("Writing byte to ROM: ");
        Serial.println(data, BIN);
        programmer.writeByte(address, data);
        address++;
        data++;
      }

    delay(10);
    Serial.println("~~~~~~~~~~~~~~~~~~~~");
    Serial.println("Validating data:");
    // verify the data
    address = 0;
    data = 0;
    uint8_t result = 0b00000000;
    for (int i = 0; i < 32; i++) {
        
        result = programmer.readByte(address);
        Serial.print("ROM data at address: ");
        Serial.print(address, HEX);
        Serial.print(" is: ");
        Serial.print(result, BIN);
        Serial.print(" (Expected: ");
        Serial.print(data, BIN);
        Serial.println(")");
        if (result != data) {
          Serial.println("INVALID DATA!");
        }
        address++;
        data++;
    }
    while(1);
}

