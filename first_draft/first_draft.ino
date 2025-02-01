// TODO: write protection to make sure that our programmer is writeEnabled when using write operation
// TODO: play with binary operations and uint8 to see hex, mask, & , >> stuff
#include <Arduino.h>

#include "config.h"
namespace ProgrammerUtils {
  // void prepareInputPins() {
  //   for (int i = 0; i < 8; i++) {
  //       pinMode(DATA_PINS[i], OUTPUT); // Temporarily set as output
  //       digitalWrite(DATA_PINS[i], LOW); // Drive pin to LOW
  //       pinMode(DATA_PINS[i], INPUT); // Set back to input
  //   }
  // }
}

class EEPROMProgrammer {
  private:
    const int DATA_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    const int SHIFT_DATA = 11;
    const int SHIFT_CLK = 13;
    const int SHIFT_LATCH = 10;
    const int CE_PIN = A0;
    const int OE_PIN = A1;
    const int WE_PIN = A2;

    void setDataPinsMode(uint8_t mode);
    void shiftOut(uint16_t address);
    void writeEnable();
    void readEnable();
    void setAddress(uint16_t address);

  public:
    EEPROMProgrammer();
    void begin();
    void writeByte(uint16_t address, uint8_t data);
    uint8_t readByte(uint16_t address);
    void verifyByte(uint16_t address, uint8_t expected);

};
  EEPROMProgrammer::EEPROMProgrammer() {
    // Nothing here yet
  }

  void EEPROMProgrammer::begin() {
    // setup shift registers:
    pinMode(SHIFT_LATCH, OUTPUT);
    pinMode(SHIFT_DATA, OUTPUT);
    pinMode(SHIFT_CLK, OUTPUT);

    // Add these in begin()
    //setup controls
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
    //Prepere address on both shift registers
    uint8_t lowByte = address & 0xFF;         // get bottom 8 bits
    uint8_t highByte = (address >> 8) & 0x7F; // get top 7 bits

    // Send data to shift registers
    digitalWrite(SHIFT_LATCH, LOW);  // prepare to receive data
    ::shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, highByte);  // send high byte
    ::shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, lowByte);   // send low byte
    digitalWrite(SHIFT_LATCH, HIGH); // latch the data

    // 1. Set programmer into wrtire mode
    this->writeEnable();

    // 2. Put data on data pins (English is not my first language =) )
    for(int i = 0; i < 8; i++) {
      digitalWrite(DATA_PINS[i], (data >> i) & 1);
    }
    //3. Trigger a write pulse //TODO: read about how it works!
    digitalWrite(WE_PIN, LOW);
    delayMicroseconds(1);  // Write pulse duration (min 100 ns)
    //3. WE goes high to complete write 
    digitalWrite(WE_PIN, HIGH);
    delay(10); //TODO: Enable poll D7 for completion (have no idea how it works now)
  }

  uint8_t EEPROMProgrammer::readByte(uint16_t address) {
    // set programmer into read mode
    this->readEnable();
    
    delayMicroseconds(5); // Let signals stabilize (critical!)
    //Prepere address on both shift registers
    uint8_t lowByte = address & 0xFF;         // get bottom 8 bits
    uint8_t highByte = (address >> 8) & 0x7F; // get top 7 bits

    // Send data to shift registers
    digitalWrite(SHIFT_LATCH, LOW);  // prepare to receive data
    ::shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, highByte);  // send high byte
    ::shiftOut(SHIFT_DATA, SHIFT_CLK, MSBFIRST, lowByte);   // send low byte
    digitalWrite(SHIFT_LATCH, HIGH); // latch the data

    // Reading data (correct for D2 = I/O0, D9 = I/O7)
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
      data |= (digitalRead(DATA_PINS[i]) << i); // LSB first
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
    digitalWrite(CE_PIN, LOW);  // Disable chip
    digitalWrite(OE_PIN, HIGH);  // Disable output

    // set data as output
    // TODO: put me into function:
    this->setDataPinsMode(OUTPUT);

  }

  void EEPROMProgrammer::readEnable() {
    digitalWrite(WE_PIN, HIGH);  // Ensure WE is HIGH during reads
    digitalWrite(CE_PIN, LOW);   // Enable chip
    digitalWrite(OE_PIN, LOW);   // Enable output
    this->setDataPinsMode(INPUT);      // Data pins as inputs
  }


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
    
    uint8_t data2 = 0b00000000;
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

