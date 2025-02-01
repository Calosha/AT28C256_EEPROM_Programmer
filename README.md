# AT28C256 EEPROM Programmer on Arduino Nano Every
I've decided to make a simple programmer for the AT28C256 EEPROM chip using an Arduino Nano Every and two 74HC595 shift registers. The code is written in C++ and is based on the Arduino IDE.

## Hardware

### Overview
Physically the programmer was build on a 5x7 cm prototyping board. With all address lines connected to Arduino through two daizy-chained 74HC595 shift registers. The data lines are connected directly to the Arduino. The control lines are connected to the Arduino as well. 0.1 ceramic capacitors are used on the VCC and GND lines of the EEPROM chip and the shift registers. The Arduino is powered through the USB port with 10uF electrolytic capacitor on the VCC and GND lines.

### Connections
The connections are as follows:

### Pictures