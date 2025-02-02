# AT28C256 EEPROM Programmer on Arduino Nano Every
I've decided to make a simple programmer for the AT28C256 EEPROM chip using an Arduino Nano Every and two 74HC595 shift registers. The code is written in C++ and is based on the Arduino IDE.

## Hardware

### Overview
Physically the programmer was build on a 5x7 cm prototyping board. With all address lines connected to Arduino through two daizy-chained 74HC595 shift registers. The data lines are connected directly to the Arduino. The control lines are connected to the Arduino as well. 0.1 ceramic capacitors are used on the VCC and GND lines of the EEPROM chip and the shift registers. The Arduino is powered through the USB port with 10uF electrolytic capacitor on the VCC and GND lines.

### Connections
The connections are as follows:
- Arduino Nano Every
#### Data Lines:

| EEPROM Pin | Arduino Pin |
|------------|-------------|
| I/O0       | D2          |
| I/O1       | D3          |
| I/O2       | D4          |
| I/O3       | D5          |
| I/O4       | D6          |
| I/O5       | D7          |
| I/O6       | D8          |
| I/O7       | D9          |



### Pictures
![IMG_5254](https://github.com/user-attachments/assets/9bf1a01c-dc04-4eea-81e0-fb3c717c173a)
![IMG_5201](https://github.com/user-attachments/assets/68d43b7f-3256-40c3-8b09-4e684e87eca6)
![IMG_5256](https://github.com/user-attachments/assets/6ea304b2-9421-4532-9459-ff62fc29092c)

## Parts List
- Arduino Nano Every x1  
- [74HC595 Shift Register](https://www.mouser.com/ProductDetail/595-SN74HC595NE4) x2  
- [AT28C256 EEPROM](https://www.mouser.com/ProductDetail/556-AT28C25615PU) x1  
- [0.1uF Ceramic Capacitors](https://www.mouser.com/ProductDetail/594-K104K15X7RF5UH5) x2  
- [10uF Electrolytic Capacitor](https://www.mouser.com/ProductDetail/80-ESK106M050AC3DA) x1  
- [Prototyping Kit](https://www.amazon.com/Miuzei-Including-Prototype-Connector-Terminal/dp/B07PS4VCDD) x1  
- [Jumper Wires](https://www.amazon.com/dp/B08DCK6HCC) x1  
- Push-down resistor - cheap Chinese 10kΩ resistor x2  
