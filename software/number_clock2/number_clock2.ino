/*
  ========================
  Led Matrix Clock
  Inspired by a Word Clock
  ========================
  
  file: number_clock2.ino
  description: led-clock
  date: 25/05/2014
  author: Ismael Salvador
*/

#include "config.h"
 
//#include <Time.h>
#include "DHT.h"
#include "LedControl.h"

//RTC
#define USE_RTC 1
#include <Wire.h>
#include "RTClib.h"
RTC_Millis rtc;

#define DEBUG_SERIAL 1

//matrix size
#define MATRIX_ROWS 8
#define MATRIX_COLS 8

//clock type
#define WORD_CLOCK   1
#define NUMBER_CLOCK 0

//matrix type
#define USE_COLS_PINS   0
#define USE_COLS_595    0
#define USE_ROWS_4017   0
#define USE_MATRIX_7219 1

//common cathode or anode
#define USE_7219_C_CATHODE 0
#define USE_7219_C_ANODE   1

//I2C settings
#define USER_SOFT_I2C   1

//dht settings
#define USE_DHT11       1
#define DHTPIN          6
#define DHTTYPE         DHT11 

DHT dht(DHTPIN, DHTTYPE);

#define USE_BUTTONS 1

//columns driven by pins
const int colPins[] = {
  2, 3, 4, 5, 6, 7};  // LED matrix columns are assigned to digital pins
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
//LedControl lc=LedControl(12,11,10,1);
LedControl lc=LedControl(dataIn7219,clk7219,load7219,1);

//matrix buffer
char raster[MATRIX_ROWS][MATRIX_COLS];

//time
int cyear, cmonth, cday, chour, cminute, csecond;

//weather
double humidity, temperature, dew_point;

//moon
int moon;

/* ----------------------------------------
   warming up 
   ----------------------------------------*/
void setup() {
  
  if (USE_DHT11){
     Serial.println("Opening DHT");
    dht.begin();
  }
  
  init_matrix_pins();
  
  if (USE_BUTTONS){
      initButton(2);
      initButton(3);
      initButton(4);
      initButton(5);
      //pinMode(0, INPUT_PULLUP);    
      //pinMode(1, INPUT_PULLUP);  
  }
  
  Serial.begin(9600);
  
  //sets time
  //setTime(21, 7, 0,31,3,2014);
  
  //should be only done if not rtc
  rtc.begin(DateTime(__DATE__, __TIME__));
  
  //check if rtc is ok or not
  /*
  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(__DATE__, __TIME__));
  }
  */

}

/* ----------------------------------------
   let's go to work
   ----------------------------------------*/

void loop() {  
  
  //get data
  DateTime dnow;
  
  if (USE_RTC){
    dnow = rtc.now();
    chour   = dnow.hour();
    cminute = dnow.minute();

    cyear   = dnow.year();
    cmonth  = dnow.month();
    cday    = dnow.day();
    csecond = dnow.second();
    
  } else {/*
    time_t t = now(); // Store the current time
    chour = hour(t);
    cminute = minute(t);

    cyear = year(t);
    cmonth = month(t);
    cday = day(t);
    csecond = second(t);*/
  }
  
  //get data
  
  //draw data
  fill_matrix(0);
  
  if (NUMBER_CLOCK){
    set_led_number_clock();
  }  
  else if (WORD_CLOCK){
    set_led_word_clock();
  }    
    
  //write leds  
  draw_matrix(500);
  
  if (USE_BUTTONS){
    //if sleep mode then switch on
    //interrupt ???
    
    //if pressed for more than 1 second switch off
    //dimming?
    
    //one hour
    if (readDButton(2)){
      DateTime future = dnow.unixtime() + 3600L;
      rtc.adjust(future);    
    }
    if (readDButton(3)){
      DateTime future = dnow.unixtime() + 60L;
      rtc.adjust(future);    
    }
    
     if (readDButton(2)){
       Serial.print("button 2 pressed");
    }
    if (readDButton(3)){
       Serial.print("button 3 pressed");
    }
    
     if (readDButton(4)){
       Serial.print("button 4 pressed");
    }
    if (readDButton(5)){
       Serial.print("button 5 pressed");
    }


  if (DEBUG_SERIAL) 
  {

  humidity    = /*(int)*/ dht.readHumidity();
  temperature = /*(int)*/ dht.readTemperature();
       dew_point   = dewPoint(temperature, humidity);
  
  Serial.print(chour%12);
  Serial.print(" ");
  Serial.print(cminute);
  Serial.print(" ");
  Serial.print(csecond);
  Serial.print(" ");
  Serial.print(moon/2);
  Serial.print(" ");
  Serial.print(temperature);
  Serial.print(" ");
  Serial.print(humidity);
  Serial.print(" ");
  Serial.print(dew_point);
  Serial.print(" ");
  Serial.print(((csecond+7)/15)%4);
  Serial.print("\n");
  }

  }
  
  
}



