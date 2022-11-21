# MS-Interlock-and-Inband-for-9a5y-
Simplest introduction of 2nd radio on RUN for Multi/Single , interlock of radios and sharing amplifier/tx antennas

PDF file provides 
- upper part - station layout
- bottom part - complete schematic of the electronic circuit

Based on Dasduino Core (ATmega328P board) which is Croatian product made in EU, a cheaper alternative to Arduino Nano.
(formerly Croduino)

Notes about Schematic:
- its important to properly filter any unwated RF in the shack that can come to the circuit from power supply - hence the input inductor and various ceramic capacitors around power supply circuit
- place all capacitors as near to LM7805 voltage regulator as possible.
- +12v feed point for ULN2004 & relays is after RF filtering!
- place 100 and 1 nF capacitor as close as you can to the VCC pins of Dasduino. Both VCC pins are connected in paralel.
- Russian REW-14 relays are powered by separate 27V power supply.

- more expensive version is done replacing the REW-14 with Tohtsu CX-600-N.
- cheaper version is done by replacing the CX120 with good DC relays (Schrack RT4012 or similar)

- there is example where to plug inhibit signal to the Yaesu FT-1000(MP, MarkV...) but that is done throught external 10K resistor !!


Notes about firmware:
- please read part about delays
- default delay without any action from switching relays and turning amplifier ptt is 30 msec (then from amplifier to radio 15msec)
- that delay can be adjusted during boot-up time with two footswitches connected to PTT input 1 and 2 to values of 40, 50 and 60ms.
- For CW setup an delay in N1MM, DX Log, QARtest or Win-Test to 47-50ms delay of CW after the PTT. Increment in steps of 10 if you increment sequencer delay to 40,50 or 60ms. 

- During operation BOTH radios have all the time RX ANT ON !
- Entering on low bands and listening additional Bevrages or various RX antenas means manually changing coaxial cable from main tx antennas to bevrage switch box for now (mail me and I can add automation switch/relay for that)

RX spliters should be basic Magic-T wounded around ferrite binocular cores material 73.



How to program Dasduino (Croduino) board:

DOWNLOAD ARDUINO IDE Installer version 2.0 or above:
https://www.arduino.cc/en/software

Install before pluging in Croduino board.

Download and install CH340 USB to UART converter drivers
https://e-radionica.com/productdata/CH34x_Install_Windows_v3_4.EXE

Install and reboot the PC.

Start Arduino IDE.

Go to File-> Preferences - add following URLs to field called Additiona Boards Manager URLs by clicking the box on the right (separate urls with Enter)

http://arduino.esp8266.com/stable/package_esp8266com_index.json 

https://downloads.arduino.cc/packages/package_avr_3.6.0_index.json

https://github.com/e-radionicacom/Dasduino-Board-Definitions-for-Arduino-IDE/raw/master/package_Dasduino_Boards_index.json


Confirm with OK.

Install offered drivers.

Go to Tools -> Boards -> Dasduino AVR boards and select
Dasduino Core (ATmega328P).

Plugin Dasduino board to USB-c type cable.

Load the code to IDE, Save and click Sketch->Verify/Compile, then Sketch->Upload.

Thats about it.



GL to all building this project & enjoy contesting

Please report back with pictures of builded circuit, it will be a pleasure to see it done.

Mirko, 9A6KX
November 2022.
