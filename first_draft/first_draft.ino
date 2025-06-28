// TODO: write protection to make sure that our programmer is writeEnabled when
// using write operation
// TODO: play with binary operations and uint8 to see hex, mask, & , >> stuff
#include <Arduino.h>

#include "EEPROMProgrammer.h"
#include "SDManager.h"

EEPROMProgrammer programmer;

void setup() {
  // Start serial monitor @9600 baud
  Serial.begin(9600);
  // Setup shift registers
  programmer.begin();
  programmer.programFromFile(0x00, "counter.bin");
  //cleanFront();
  verifyROM();
}

void cleanFront() {
  for (int i = 0; i < 19; i++) {
    programmer.writeByte(i, 0xFF);
  }
}

void setResetVector(){
    // Reset vectors (same as above)
  programmer.writeByte(0x7FFC, 0x00);  // Low byte
  delay(15);
  programmer.writeByte(0x7FFD, 0x80);  // High byte → points to $8000
  delay(15);
}


void verifyROM() {
  Serial.println("Verifying ROM contents...");

  Serial.println("Program area:");
  for (int i = 0; i < 8; i++) {
    Serial.print("Address ");
    Serial.print(i, HEX);
    Serial.print(": ");
    Serial.println(programmer.readByte(i), HEX);
  }

  Serial.println("Reset vectors:");
  Serial.print("Address 7FFC: ");
  Serial.println(programmer.readByte(0x7FFC), HEX);
  Serial.print("Address 7FFD: ");
  Serial.println(programmer.readByte(0x7FFD), HEX);
}


void loop() { while (1); }
