  /*

 Led Matrix Clock
 Inspired by a Word Clock
 by Ismael Salvador
 25/05/2014
 
 */

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

//I2C settings
#define USER_SOFT_I2C   1

//dht settings
#define USE_DHT11       1
#define DHTPIN          6
#define DHTTYPE         DHT11 
DHT dht(DHTPIN, DHTTYPE);

#define USE_BUTTONS 1

//leds are numbered sequentially from topleft
const byte H[]={
//  11,0,1,2,3,4,5,6,7,8,9,10}; //hours from 1-12
  9,10,11,12,13,14,17,18,19,20,21,22};
const byte M[]={
//  12,13,14,15,16,17}; // tens for minutes 0-5
25,26,27,28,29,30};
const byte m[]={
//  18,19,20,21,22,24,25,26,27,28}; // units for minutes
33,34,35,36,37,  41,42,43,44,45};

const byte D[]={
 0,1,2,24 //tens of days 0-2
};
const byte d[]={
 0,8,16,24,32,36,48,56,57,58, //units of days 0-9
};

const byte moon[]={
//  30,31,32,33};
59,60,61,62};
const byte weather[]={ //good, normal, bad
  38,46,54};

const byte pulse=53;//34;

const byte arrow[]={ //up, right, down, left
49,50,51,52};

//pins
const int colPins[] = {
  2, 3, 4, 5, 6, 7};  // LED matrix columns are assigned to digital pins
const int clockPin4017 = 9;  // Connected to Clock pin 14 in 4017
const int resetPin4017 = 8;  // Connected to Reset pin 15 in 4017

//595
const int latchPin595 =  7;  // Connected to ST_CP pin 12 in 74HC595
const int clockPin595 =  6;  // Connected to SH_CP pin 11 in 74HC595
const int dataPin595  =  5;  // Connected to DS    pin 14 in 74HC595

//switch
const int switchPin1=1;

//7219 stuff
const int dataIn7219 = 9;  //Connected to DIN  pin 12 in 7219
const int clk7219    = 8;  //Connected to CLK  pin 11 in 7219
const int load7219   = 7;  //Connected to LOAD pin 10 in 7219
//LedControl lc=LedControl(12,11,10,1);
LedControl lc=LedControl(dataIn7219,clk7219,load7219,1);


//matrix buffer
char raster[MATRIX_ROWS][MATRIX_COLS];

int cyear, cmonth, cday, chour, cminute, csecond;
double humidity, temperature, dew_point;

void set_led_hour(int hour){
  //set hour
  int led_hour= H[hour%12];
  set_led_number(led_hour);
}

void set_led_minute(int minute){
  //set tens
  int led_ten_min= M[minute/10];
  set_led_number(led_ten_min);

  //set units
  int led_unit_min= m[minute%10];
  set_led_number(led_unit_min);  
}

void set_led_day(int day){
  //set tens
  set_led_number(D[day/10]);

  //set units
  set_led_number(d[day%10]);  
}

void set_led_moon(int phase){
  //new; 0% illuminated ** 
  //Waxing crescent; 25% illuminated
  //First quarter; 50% illuminated **
  //Waxing gibbous; 75% illuminated
  //Full; 100% illuminated  **
  //Waning gibbous; 75% illuminated
  //Last quarter; 50% illuminated **
  //Waning crescent; 25% illuminated
  //default to new; 0% illuminated **
  set_led_number(moon[phase/2]);

}

void set_led_arrow(){
  set_led_number(arrow[csecond/15]);
}

void set_led_weather(){
  if (USE_DHT11) {      
     //refresh measures every half minute, it takes sometime in DHT11
     if ((csecond % 30) == 0) {
       humidity    = (int) dht.readHumidity();
       temperature = (int) dht.readTemperature();
       dew_point   = dewPoint(temperature, humidity);
     }
               
     //show it for 2 seconds every half minute or pressed button
     if (((csecond % 30) < 5) || (LOW == digitalRead(A0))) {
      fill_matrix(0);
      set_led_hour(humidity/10);
      set_led_minute(temperature);     
     }
     
     //show dew point
     if (dew_point > 18)
       set_led_number(weather[2]); //humid
     else if (dew_point > 10 )
        set_led_number(weather[1]); //confortable
     else 
        set_led_number(weather[0]); //dry
  }
  
}

/*
warming up
 */
void setup() {

  pinMode(switchPin1, INPUT);
  
  if (USE_DHT11){
     Serial.println("Opening DHT");
    dht.begin();
  }
  
  if (USE_COLS_PINS){
    //pins for rows
    for (int i = 0; i < MATRIX_COLS; i++)
    pinMode(colPins[i], OUTPUT);
  }

  if (USE_COLS_595){
    //pins for 595
    pinMode(latchPin595, OUTPUT);
    pinMode(clockPin595, OUTPUT);
    pinMode(dataPin595,  OUTPUT);
  }
  
  if (USE_ROWS_4017){  
    //pins for rows managed by 4017  
    pinMode(clockPin4017, OUTPUT);
    pinMode(resetPin4017, OUTPUT);
    reset_4017();
  }
  
  if (USE_MATRIX_7219){
    lc.shutdown(0,false); //wake up from saving mode
    lc.setIntensity(0,8); //medium intensity
    lc.clearDisplay(0);   //clear display
  }
  
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

/*
let's go to work
 */
void loop() {  
  int y;

  //clean matrix
  fill_matrix(0);
  /*
   //switch on rows ascending
   for (y = 0; y < MATRIX_ROWS; y++) {
   fill_row(y,1);
   draw_matrix(100);
   }*/

  //switch off rows descending
  /*
   for (y = MATRIX_ROWS-1; y>=0; y--) {  
   fill_row(y,0);
   draw_matrix(100);
   }
   
   for (y = MATRIX_ROWS-1; y>=0; y--) {  
   random_matrix();      
   draw_matrix(200);
   }
   */

  //minute = total % 60;
  //hour = (total/60)%12;

  //clear matrix
  fill_matrix(0);
  
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
  
  set_led_hour(chour);     
  set_led_minute(cminute);
  
  if(csecond%2)
    set_led_number(pulse);
    
//  if (LOW == digitalRead(A0))
//    set_led_number(doughnut);
  
//  Serial.print(analogRead(A0));
//  Serial.print(" ");
    
  //set_led_weather();
  
  int moon = moon_phase(cyear, cmonth, cday);
  set_led_moon(moon);

  set_led_arrow();
  set_led_day(cday);

  //if (DEBUG_SERIAL) 
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

  //write matrix
  if (WORD_CLOCK){
    //clean matrix
    fill_matrix(0);
    //show next hour if minutes over 37
    if (cminute > 37)
      set_led_word_hour(chour+1);
    else 
      set_led_word_hour(chour);
      
    set_led_word_quarter(cminute);
  }

  //write mode
  if (USE_COLS_PINS)
    draw_matrix(500);
  else if (USE_COLS_595)
    draw_matrix_595(500);
  else if (USE_MATRIX_7219){
    //IF (ANODE_V3)
    trans_matrix();
    draw_matrix_7219(500);    
  }
  
  if (USE_BUTTONS){
    //if sleep mode then switch on
    
    //if pressed for more than 1 second switch off
    //dimming?
    
    //one hour
    if (readButton(2)){
      DateTime future = dnow.unixtime() + 3600L;
      rtc.adjust(future);    
    }
    if (readButton(3)){
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


  }
  
  
}



