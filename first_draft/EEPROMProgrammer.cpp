#include "EEPROMProgrammer.h"

EEPROMProgrammer::EEPROMProgrammer() {
  // Nothing here yet
}

void EEPROMProgrammer::begin() {
  // setup shift registers:
  pinMode(SHIFT_LATCH_PIN, OUTPUT);
  pinMode(SHIFT_DATA_PIN, OUTPUT);
  pinMode(SHIFT_CLK_PIN, OUTPUT);

  // Add these in begin()
  // setup controls
  pinMode(CE_PIN, OUTPUT);
  pinMode(OE_PIN, OUTPUT);
  pinMode(WE_PIN, OUTPUT);

  // Set initial control states
  digitalWrite(CE_PIN, HIGH);  // Disable chip
  digitalWrite(OE_PIN, HIGH);  // Disable output
  digitalWrite(WE_PIN, HIGH);  // Disable write

  for (int i = 0; i < 8; i++) {
    pinMode(DATA_PINS[i], INPUT);
  }
}
void EEPROMProgrammer::setDataPinsMode(uint8_t mode) {
  for (int i = 0; i < 8; i++) {
    pinMode(DATA_PINS[i], mode);
  }
}

void EEPROMProgrammer::writeByte(uint16_t address, uint8_t data) {
  this->setAddress(address);
  // 1. Set programmer into wrtire mode
  this->writeEnable();

  // 2. Put data on data pins (English is not my first language =) )
  for (int i = 0; i < 8; i++) {
    digitalWrite(DATA_PINS[i], (data >> i) & 1);
  }
  // 3. Trigger a write pulse //TODO: read about how it works!
  digitalWrite(WE_PIN, LOW);
  delayMicroseconds(1);  // Write pulse duration (min 100 ns)
  // 3. WE goes high to complete write
  digitalWrite(WE_PIN, HIGH);
  delay(13);  // TODO: Enable poll D7 for completion (have no idea how it works
              // now)
}

uint8_t EEPROMProgrammer::readByte(uint16_t address) {
  // set programmer into read mode
  this->readEnable();

  delayMicroseconds(5);  // Let signals stabilize (critical!)
  // Prepere address on both shift registers

  this->setAddress(address);
  uint8_t data = 0;
  for (int i = 0; i < 8; i++) {
    data |= (digitalRead(DATA_PINS[i]) << i);  // LSB first
  }
  return data;
}

void EEPROMProgrammer::writeEnable() {
  /*
    For writing:

    CE goes low (activate chip)
    WE goes low (enable write)
    Hold data stable for required time
    WE goes high to complete write
    Wait for write cycle to complete
    __________________________________________________
    Data Setup Time             |	tDS	| 50 ns minimum
    Data Hold Time	            | tDH	| 0 ns minimum
    Write Cycle Time (complete) | tWC	| 10 ms maximum
    __________________________________________________
  */
  digitalWrite(CE_PIN, LOW);   // Disable chip
  digitalWrite(OE_PIN, HIGH);  // Disable output

  // set data as output
  this->setDataPinsMode(OUTPUT);
}

void EEPROMProgrammer::readEnable() {
  digitalWrite(WE_PIN, HIGH);    // Ensure WE is HIGH during reads
  digitalWrite(CE_PIN, LOW);     // Enable chip
  digitalWrite(OE_PIN, LOW);     // Enable output
  this->setDataPinsMode(INPUT);  // Data pins as inputs
}

void EEPROMProgrammer::setAddress(uint16_t address) {
  // Prepere address on both shift registers
  uint8_t lowByte = address & 0xFF;          // get bottom 8 bits
  uint8_t highByte = (address >> 8) & 0x7F;  // get top 7 bits

  // Send data to shift registers
  digitalWrite(SHIFT_LATCH_PIN, LOW);  // prepare to receive data
  ::shiftOut(SHIFT_DATA_PIN, SHIFT_CLK_PIN, MSBFIRST,
             highByte);  // send high byte
  ::shiftOut(SHIFT_DATA_PIN, SHIFT_CLK_PIN, MSBFIRST,
             lowByte);                  // send low byte
  digitalWrite(SHIFT_LATCH_PIN, HIGH);  // latch the data
}

void EEPROMProgrammer::programFromFile(uint16_t startAddress, const char* filename) {
  // Open file from SD card
  // TODO: print details size etc
  Serial.print("Opening file: ");
  Serial.println(filename);
  this->sdManager_.openFile(filename);
  File file = this->sdManager_.getFile();
  Serial.print("File size is: ");
  Serial.println(file.size());
  uint16_t address = startAddress;
  Serial.print("Starting to write at address: 0x");
  Serial.println(startAddress, HEX);
  while (file.available()) {
    uint8_t byte = file.read();

    this->writeByte(address, byte);
    address++;

    // Print status every 256 bytes
    if (address % 256 == 0) {
      Serial.print("Programmed up to address: 0x");
      Serial.println(address, HEX);
    }

    // Safety check to prevent overflow
    if (address >= ROM_SIZE) {
        Serial.println("Warning: Reached EEPROM capacity limit");
        break;
    }
  }
    Serial.print("Programming complete. Wrote ");
    Serial.print(address - startAddress);
    Serial.println(" bytes.");

    file.close();
    //TODO: Add validation
}

void EEPROMProgrammer::eraseROM() {
  for (int i = 0; i < ROM_SIZE; i++) {
    this->writeByte(i, 0xFF);
  }
}
