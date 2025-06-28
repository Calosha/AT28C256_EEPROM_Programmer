#include "SDManager.h"

SDManager::SDManager() {
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("initialization failed!");
    while (1);
  }
}

void SDManager::openFile(const char* fileName) {
  File openedFile = SD.open(fileName);
  if (openedFile) {
    this->file_ = openedFile;
  } else {
    Serial.print("Cannot open file:");
    Serial.print(fileName);
    Serial.print("\n");
    while(1); // Critical stop execution
  }
}

File SDManager::getFile() {
  return this->file_;
}

void SDManager::printContent() {
  if (this->file_) {
    while (this->file_.available()) {
      uint8_t byte = this->file_.read();
      Serial.print("0x");
      if (byte < 0x10) Serial.print("0");
      Serial.print(byte, HEX);
      Serial.print(" ");
    }
  }
}
