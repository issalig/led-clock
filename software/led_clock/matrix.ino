/*
  file: matrix.ino
  description: led matrix access for different methods
  date: 25/05/2014
  author: Ismael Salvador
*/

//matrix size
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

//matrix type
#define USE_COLS_PINS   0 //cols driven by pins
#define USE_COLS_595    0 //cols driven by a 555
#define USE_ROWS_4017   0 //rows with a 4017
#define USE_MATRIX_7219 1

//columns driven by pins
const int colPins[] = {
  2, 3, 4, 5, 6, 7
};  // LED matrix columns are assigned to digital pins

const int clockPin4017 = 9;  // Connected to Clock pin 14 in 4017
const int resetPin4017 = 8;  // Connected to Reset pin 15 in 4017

//columns driven by 595
const int latchPin595 =  7;  // Connected to ST_CP pin 12 in 74HC595
const int clockPin595 =  6;  // Connected to SH_CP pin 11 in 74HC595
const int dataPin595  =  5;  // Connected to DS    pin 14 in 74HC595

//7219
const int dataIn7219 = 9;  //Connected to DIN  pin 12 in 7219
const int clk7219    = 8;  //Connected to CLK  pin 11 in 7219
const int load7219   = 7;  //Connected to LOAD pin 10 in 7219

//7219 object
//LedControl lc = LedControl(dataIn7219, clk7219, load7219, 1);

//led status will be stored in raster matrix
char raster[MATRIX_ROWS][MATRIX_COLS];

/* init pins connected to matrix */
void init_matrix_pins() {
  if (USE_COLS_PINS) {
    //pins for rows
    for (int i = 0; i < MATRIX_COLS; i++)
      pinMode(colPins[i], OUTPUT);
  }

  if (USE_COLS_595) {
    //pins for 595
    pinMode(latchPin595, OUTPUT);
    pinMode(clockPin595, OUTPUT);
    pinMode(dataPin595,  OUTPUT);
  }

  if (USE_ROWS_4017) {
    //pins for rows managed by 4017
    pinMode(clockPin4017, OUTPUT);
    pinMode(resetPin4017, OUTPUT);
    reset_4017();
  }

  if (USE_MATRIX_7219) {
    Serial.print("Num devices: ");
    Serial.println(lc.getDeviceCount());
    for (int index = 0; index < lc.getDeviceCount(); index++) {
      lc.shutdown(index, false); //wake up from saving mode
      lc.setIntensity(index, 8); //medium intensity
      lc.clearDisplay(index);   //clear display
    }
  }
}

/*
  reset 4017
*/
void reset_4017() {
  digitalWrite(resetPin4017, HIGH);
  delayMicroseconds(5);
  digitalWrite(resetPin4017, LOW);
}

/*
  send pulse on clock pin
*/
void clock_4017() {
  digitalWrite(clockPin4017, HIGH);  // Move to next row and repeat for all eight rows
  //delayMicroseconds(5);
  digitalWrite(clockPin4017, LOW);
}

/*
  set row performing or
*/
void set_or_row(byte row, byte val) {
  byte x;
  for (x = 0; x < MATRIX_COLS; x++)
    if (val & (1 << x))
      raster[row][MATRIX_COLS - x - 1] = 1;
}


/*
  fill a row
*/
void fill_row(int row, int val) {
  int x;
  for (x = 0; x < MATRIX_COLS; x++)
    raster[row][x] = val;
}

/*
  fill a column
*/
void fill_col(int col, int val) {
  int y;
  for (y = 0; y < MATRIX_ROWS; y++)
    raster[y][col] = val;
}

/*
  fill matrix
*/
void fill_matrix(int val) {
  int x, y;
  for (y = 0; y < MATRIX_ROWS; y++)
    for (x = 0; x < MATRIX_COLS; x++)
      raster[y][x] = val;
}

/*
  transpose matrix
*/
void transpose_matrix() {
  int x, y;
  char val;
  char raster2[MATRIX_ROWS][MATRIX_ROWS];
  for (y = 0; y < MATRIX_ROWS; y++)
    for (x = y + 1; x < MATRIX_ROWS; x++) {
      val = raster[y][x];
      raster[y][x] = raster[x][y];
      raster[x][y] = val;
    }
}

/*
  fill a centered square
*/
void fill_square(int radius, int val) {
  int x, y;
  for (y = 0; y < MATRIX_ROWS; y++)
    for (x = 0; x < MATRIX_COLS; x++)
      if ((y >= radius) && ( y < (MATRIX_COLS - radius)) &&
          (x >= radius) && ( x < (MATRIX_ROWS - radius)))
        raster[y][x] = val;
}

/*
  sqaure animation
*/
void square_animation() {
  for (int repeat = 0; repeat < 3; repeat++) {
    for (int radius = 0; radius < 3; radius++) {
      fill_matrix(0);
      fill_square(radius, 1);

      draw_matrix_4017_595(300);

    }
    for (int radius = 2; radius >= 0; radius--) {
      fill_matrix(1);
      fill_square(radius, 0);
      draw_matrix_4017_595(300);

    }
  }
  fill_matrix(0);
}

/*
  fill random matrix
*/
void random_matrix() {
  int x, y;

  for (y = 0; y < MATRIX_ROWS; y++)
    for (x = 0; x < MATRIX_COLS; x++)
      raster[y][x] = random(0, 2 );

}

/*
  fill a column
*/
void set_led_number(int number) {
  int x, y;

  if (number > 0) {
    y = number % MATRIX_COLS;
    x = number - y * MATRIX_COLS;
  }

  raster[y][x] = 1;
}


/*
  draws matrix for a period of time using 4017 for rows and cols in digital ports
*/
void draw_matrix_4017_port(int wait) {
  int x, y;
  unsigned long time1;

  time1 = millis();

  while (millis() < time1 + wait) {

    //draw leds
    //pulse_clock();

    //rows
    for (y = 0; y < MATRIX_ROWS; y++) {
      //columns
      for (x = 0; x < MATRIX_COLS; x++)
        if (raster[y][x]) digitalWrite(colPins[x], HIGH);  // Light appropriate column LEDs

      delayMicroseconds(300);  // Wait a bit, or else they'll be too dim

      for (x = 0; x < MATRIX_COLS; x++)
        digitalWrite(colPins[x], LOW);  // Turn off all row

      clock_4017();
    }
    reset_4017();

  }
}

void shiftOut2(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, int val, uint8_t bits = 8, uint8_t del = 0)
{
  uint8_t i;
  for (i = 0; i < bits; i++)  {
    if (bitOrder == LSBFIRST)
      digitalWrite(dataPin, !!(val & (1 << i)));
    else
      digitalWrite(dataPin, !!(val & (1 << ((bits - 1 - i)))));
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(del);
    digitalWrite(clockPin, LOW);
  }
}

/*
  draws matrix for a period of time using 4017 for rows and 595 for columns
*/
void draw_matrix_4017_595(int wait) {
  int x, y;
  unsigned long time1;

  time1 = millis();

  while (millis() < time1 + wait) {

    //draw leds
    //pulse_clock();

    //rows
    for (y = 0; y < MATRIX_ROWS; y++) {

      //columns
      int row = 0;
      for (x = 0; x < MATRIX_COLS; x++)
        //if (raster[y][x]) bitSet(row,x);
        bitWrite(row, x, raster[y][x]);
      //row = row + (raster[y][x] << x);

      // the LEDs don't change while you're sending in bits:
      digitalWrite(latchPin595, LOW);
      // shift out the bits:
      shiftOut(dataPin595, clockPin595, MSBFIRST, row);
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin595, HIGH);

      delayMicroseconds(300);  // Wait a bit, or else they'll be too dim 300 ok

      for (x = 0; x < MATRIX_COLS; x++)
        digitalWrite(colPins[x], LOW);  // Turn off all row

      // the LEDs don't change while you're sending in bits:
      digitalWrite(latchPin595, LOW);
      // shift out the bits:
      shiftOut(dataPin595, clockPin595, MSBFIRST, 0);
      //take the latch pin high so the LEDs will light up:
      digitalWrite(latchPin595, HIGH);

      //clock and go to next row
      clock_4017();
    }
    //reset to go for first row
    reset_4017();

  }
}

/*
  draws matrix for a period of time using a 7219
*/
void draw_matrix_7219(int index) {
  int x, y;
  unsigned long time1;

    lc.clearDisplay(index);

    //rows
    for (y = 0; y < MATRIX_ROWS; y++) {
      //columns
      for (x = 0; x < MATRIX_COLS; x++)
        if (raster[y][x]) {
          lc.setLed(index, y, x, true);
        }
    }

    //time1 = millis();
    //while (millis() < time1 + wait);
  
}

/*
  //switch on rows ascending
  for (y = 0; y < MATRIX_ROWS; y++) {
  fill_row(y,1);
  draw_matrix(100);
  }*/

/*
  //switch off rows descending
  for (y = MATRIX_ROWS-1; y>=0; y--) {
  fill_row(y,0);
  draw_matrix(100);
  }

  for (y = MATRIX_ROWS-1; y>=0; y--) {
  random_matrix();
  draw_matrix(200);
  }
*/

void draw_matrix_4017x(int wait) {
  if (USE_COLS_PINS)
    draw_matrix_4017_port(wait);
  else if (USE_COLS_595)
    draw_matrix_4017_595(wait);
}

void draw_matrix(int index, int intensity) {
  if (USE_MATRIX_7219) {
    if (USE_7219_C_ANODE)
      transpose_matrix();
    lc.setIntensity(index, intensity);
    draw_matrix_7219(0);
  }
}

void set_led_mask(const byte *mask, byte b) {
  int i;
  for (i = 0; i < MATRIX_ROWS; i++) {
    set_or_row(i, mask[i + (b * MATRIX_COLS)]);
    //set_or_row(i,pgm_read_word_near(mask + i+(b*MATRIX_COLS)));
  }
}

