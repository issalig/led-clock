led-clock
=========

Clock adventures with a led matrix and many more.

After thinking about the simplest way to build a word clock I experimented with hand-soldered led matrices, 74HC595, 7219 and others to end up with the mighty 7219 and 8x8 led matrices.

7219 works with common cathode displays but a nice workaround to make it work with common anode matrices is to interchange rows by cols (transposing the matrix) and do the same (transposing it again) from software. Anyway, the PCB has been designed to support both c.c. and c.a. as well as 3mm matrices.

As led matrices did not seemed the only thing to play with in 5x5 cm2, the board now includes weather sensors, FM radio and I2C, SPI connectivity, servo connectors, ...

Board features
--------------

  - Led matrix 8x8 5mm common cathode or anode
  - 2 buttons
  - Small factor 5cmx5cm (fits in cheap PCB manufacturing)
  - Exported I2C, SPI and Analog pins
  - Chainable (1 or more matrices)
  - Support for common cathode and common anode
  - Arduino Nano
  - Max7219
  - RTC DS1307
  - Nokia LCD
  - TFT
  - Humidity sensor DHT11
  - Pressure sensor BMP180
  - TEA5767 FM Radio
  - LDR sensor
  - RGB Led
  - IR 1838
  - Exported servo-like connectors.

Software
--------

  Arduino has been chosen as the development environment due to the available libraries and its simplicity. MSP430 has been also considered but I was not able to make it work. Any volunteer?

  Operation modes:
  -Sleep. Wake up when button is touched
  -Alarm.

Clock layout
------------

  The idea is to have different interchangeable covers allowing the clock to easily change its appearance (and behaviour).
  By default two types of clock are designed:
  
- word clock
      Consists of a grid of characters that contain the words for telling the time in natural language.
      
- number/symbol clock
      Consists of a grid with digits and some extra symbols to indicate weather, moon, etc, ...
      
- calendar
	  Consists of a grid with days of week, month, weather, ... (mark first of month to calculate number of day)
	  
- anyclock
    Feel free to design your own clock, just represent your info in 64 elements (or more)

TODO
----
  - Checklist
	- 3.3v and 5v on board (OK)
		(boost for 5v even with batt)
		(3.3v with logic level or dedicated?)
		http://lowpowerlab.com/blog/2014/03/13/moteino-power-shield-now-available/
    - Lipo battery or 3xAAA???
	- Boost??
	- Jumper for A or K (OK)
	- datain for 5219 on not pwm??
	- 2 button
		1 is mode: sleep, set hour, 
		1 is set:  +1, next option
	- 3 button	
    - buzzer connection  //1M resistor ??? just servo/generic connector (-+S)
	- remote connection // risk, interference with voltage, just connector(-+S)
	- xronos clock (how they manage buttons, eeprom)
  - Wishlist
	 
	 
  - New PCB for the beginning of 2015 (SMD)
    - Correct GND mask from previous version 0.3
    - Remove DS1307 circuitry and substitute it for a module
    - Correct button footprint holes
	- Documentation for pinout
	- (OK) Support for radio TEA5767
	- (OK) Possibility of adding capes
    - (OK) Pinout assignment and reserved pins
	- Pass also I2C, SPI pins on stackable horizontal	
	- (OK) Remote IR 1838
	
  - Software  
    - Grid data structure for symbols    
    - Grid editor (http://jsfiddle.net/AAg8e/4/)
    
  - Case
    - Carboard, bands and needles. Easy to change front mask cover
    - Wood. (Anyone with a laser cutter/CNC?)
 
 - Masks
    - word, temperature, humidex, calendar, spectrum analyzer
    - rotating wheel and servo?
 - Capes
	
	
