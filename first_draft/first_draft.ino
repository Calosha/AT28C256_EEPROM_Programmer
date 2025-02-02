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
    uint8_t data = 0b10101010;
    uint16_t address = 0x00;
    programmer.writeByte(address, data);
    uint8_t result = programmer.readByte(address);
    Serial.print("Address: ");
    Serial.println(address, HEX);
    Serial.print("byte from programmer: ");
    Serial.println(result, BIN);
    delay(5);
    data = 0b10101011;
    address = 0x01;
    programmer.writeByte(address, data);
    uint8_t result1 = programmer.readByte(address);
    Serial.print("Address: ");
    Serial.println(address, HEX);
    Serial.print("byte from programmer: ");
    Serial.println(result1, BIN);
    delay(2000);
    address = 0x02;
    
    uint8_t data2 = 0b10011000;
    programmer.writeByte(address, data2);



    uint8_t result2 = programmer.readByte(address);
    Serial.print("Address: ");
    Serial.println(address, HEX);
    Serial.print("byte from programmer: ");
    Serial.println(result2, BIN);
    delay(2000);
    uint8_t result3 = programmer.readByte(address);
    Serial.print("Address: ");
    Serial.println(address, HEX);
    Serial.print("byte from programmer: ");
    Serial.println(result3, BIN);

    while(1);
}

