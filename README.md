led-clock
=========

Clock adventures with a led matrix.

After thinking about the simplest way to build a word clock I experimented with hand-soldered led matrices, 74HC595, 7219 and others to end up with the mighty 7219 and 8x8 led matrices.

7219 works with common cathode displays but a nice workaround to make it work with common anode matrices is to interchange rows by cols (transposing the matrix) and do the same (transposing it again) from software. Anyway, the PCB has been designed to support both c.c. and c.a. as well as 3mm matrices.

In order to make it richer, led-clock supports a humidity sensor and a pressure sensor. Additional sensors are also supported via I2C or SPI.

Hardware list
-------------

  - Arduino Pro Mini
  - Max7219
  - Led matrix 8x8 5mm/3mm common cathode or anode
  - Humidity sensor DHT11
  - Pressure sensor BMP180
  - 4 buttons

Board features
--------------

  - Small factor 5cmx5cm (fits in cheap PCB manufacturing)
  - Exported I2C, SPI and Analog pins
  - Stackable (1 or more matrices)
  - Support for 5mm and 3mm matrices
  - Support for common cathode and common anode

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

  - New PCB for the beginning of 2015 (SMD)
    - Correct GND mask from previous version 0.3
    - Remove DS1307 circuitry and substitute it for a module
    - Correct button footprint holes
	- Documentation for pinout
	- Support for radio TEA5767
	- Possibility of adding capes
    - Pinout assignment and reserved pins
	- Pass also I2C, SPI pins on stackable horizontal
	
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
	- stackable capes: nokia screen, communication, motor, radio TEA5767 / TDA7330 ...
	