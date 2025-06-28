#ifndef SD_MANAGER_H_
#define SD_MANAGER_H_

#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include "config.h"

class SDManager {
  public:
    SDManager();
    File getFile();
    void openFile(const char* fileName);
    void printContent();
  private:
    File file_;
};

#endif //SD_MANAGER_H_
