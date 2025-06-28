#ifndef EEPROM_PROGRAMMER_H_
#define EEPROM_PROGRAMMER_H_

#include <Arduino.h>
#include "SDManager.h"
#include "config.h"

class EEPROMProgrammer {
 private:
  void setDataPinsMode(uint8_t mode);
  void writeEnable();
  void readEnable();
  void setAddress(uint16_t address);
  SDManager sdManager_;

 public:
  EEPROMProgrammer();
  void begin();
  void writeByte(uint16_t address, uint8_t data);
  uint8_t readByte(uint16_t address);
  void programFromFile(uint16_t startAddress, const char* fileName);
  void eraseROM();
};

#endif  // EEPROM_PROGRAMMER_H_
