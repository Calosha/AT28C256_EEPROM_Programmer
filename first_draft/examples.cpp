// #include <Arduino.h>

// #include "EEPROMProgrammer.h"

// void programSimpleTest() {
//   Serial.println("Programming simple test ROM...");

//   // Even simpler: Just infinite loop with NOP instructions
//   programmer.writeByte(0x0000, 0xEA);  // NOP
//   delay(15);
//   programmer.writeByte(0x0001, 0xEA);  // NOP
//   delay(15);
//   programmer.writeByte(0x0002, 0xEA);  // NOP
//   delay(15);
//   programmer.writeByte(0x0003, 0x4C);  // JMP $8000
//   delay(15);
//   programmer.writeByte(0x0004, 0x00);  // Low byte
//   delay(15);
//   programmer.writeByte(0x0005, 0xC0);  // High byte
//   delay(15);

//   // Reset vectors (same as above)
//   programmer.writeByte(0x3FFC, 0x00);  // Low byte
//   delay(15);
//   programmer.writeByte(0x3FFD, 0xC0);  // High byte → points to $C000
//   delay(15);

//   Serial.println("Simple test: Just NOPs and JMP in ROM range");
//   Serial.println("A15 should stay HIGH (all activity in ROM)");
//   Serial.println("A0-A2 should show address activity");
// }

// // Verification function to read back and confirm programming
// void verifyROM() {
//   Serial.println("Verifying ROM contents...");

//   Serial.println("Program area:");
//   for (int i = 0; i < 8; i++) {
//     Serial.print("Address ");
//     Serial.print(i, HEX);
//     Serial.print(": ");
//     Serial.println(programmer.readByte(i), HEX);
//   }

//   Serial.println("Reset vectors:");
//   Serial.print("Address 3FFC: ");
//   Serial.println(programmer.readByte(0x3FFC), HEX);
//   Serial.print("Address 3FFD: ");
//   Serial.println(programmer.readByte(0x3FFD), HEX);
// }

// // skatch for command recognition using serial
// Serial.println("ROM Programmer Ready!");
// Serial.println("Commands:");
// Serial.println("  WRITE <addr> <data>  - Write byte");
// Serial.println("  READ <addr>          - Read byte");
// Serial.println("  UPLOAD <start> <len> - Upload binary data");
// Serial.println("  VERIFY <start> <len> - Verify ROM");

// void processCommand(String cmd) {
//   Serial.println(cmd);
//   String writeCmd = "WRITE ";
//   String bytesToWirte = "";
//   if (cmd.startsWith(writeCmd)) {
//     bytesToWirte = cmd.substring(writeCmd.length());
//     Serial.println("Writing bytes:");
//     Serial.print(bytesToWirte);
//     Serial.println("Done");

//   } else if (cmd.startsWith("READ ")) {
//     Serial.println("Reading...");

//   } else if (cmd.startsWith("UPLOAD ")) {
//     // Parse: UPLOAD 0x0000 1024
//     Serial.println("UPLOAD");

//   } else {
//     Serial.println("ERROR: Unknown command");
//   }
// }
