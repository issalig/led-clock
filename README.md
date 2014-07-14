led-clock
=========

Clock adventures with a led matrix.

After thinking about the simplest way to build a word clock, I experimented with hand-soldered matrices, 74HC595 and ULN's to end up with the mighty 7219 and 8x8 led matrices.

7219 works with common cathode displays but a nice workaround to make it work with common anode is to interchange rows by cols (transposing the matrix) and do the same (transposing it again) from software. Anyway the PCB supports both c.c. and c.a. as well as 3mm matrices.

In order to make it richer, the clock supports a humidity sensor and a pressure sensor. Additional sensors are also supported via I2C or SPI.

- Hardware
  - Arduino Pro Mini
  - Max7219
  - Led matrix 8x8 5mm/3mm common cathode or anode
  - Humidity sensor DHT11
  - Pressure sensor BMP180
  - 4 buttons

- Software
 
  Arduino has been chosen as the development environment due to the available libraries and its simplicity. MSP430 has been also considered but I was not able to make it work.

- Clock layout

  By default two types of clock are designed:
    - word clock
      
      Consists of a grid of characters that contain the words for telling the time in natural language.
    - number clock
      
      Consists of a grid with digits and some extra symbols to indicate weather, moon, etc, ...
