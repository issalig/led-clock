/*
  ========================
  Led Matrix Clock
  A word clock and whatever you want
  ========================
  
  file: led_clock.ino
  description: led-clock
  date: 25/05/2014
  author: Ismael Salvador
*/

//#include "config.h" 
//#include "matrix.h" 
//#include "button.h" 
//#include <Time.h>
#include "DHT.h"
#include "LedControl.h"

#include <Wire.h>
#include "RTClib.h"

#define DEBUG_SERIAL 1

//clock type
#define WORD_CLOCK   1
#define NUMBER_CLOCK 0

//common cathode or anode
#define USE_7219_C_CATHODE 0
#define USE_7219_C_ANODE   1

//RTC
#define USE_RTC 1

//I2C settings
#define USER_SOFT_I2C   1

#define USE_BUTTONS 1

//dht settings
#define USE_DHT11       1

#define DHT_PIN 6
#define DHT_TYPE         DHT11 

#define LDR     A2

#define BUTTON_0 2
#define BUTTON_1 4
#define LED_R 3
#define LED_G 5
#define LED_B 6

//7219
#define DIN_7219 A0
#define LOAD_7219 7
#define CLK_7219  8

//dht
#define DHT_PIN 6
//nokia
#define RST_NK 7
#define CLK_NK 8
#define LIGHT_NK 9
#define CE_NK 10
#define DIN_NK 11
#define CE_NK 10

//ir
#define IR1838 12

// global variables
int cyear, cmonth, cday, chour, cminute, csecond; //time
double humidity, temperature, dew_point; //weather
int moon; //moon

#if (USE_RTC)
  RTC_DS1307 rtc;
#else
  RTC_Millis rtc;
#endif

DHT dht(6,DHT11);

/* ----------------------------------------
   warming up 
   ----------------------------------------*/
void setup() {

  Serial.begin(9600);
  if (USE_DHT11){
     Serial.println("Opening DHT");
    
    dht.begin();
  }
  
  init_matrix_pins();
  
  if (USE_BUTTONS){
      initButton(BUTTON_0);
      initButton(BUTTON_1);
      //pinMode(0, INPUT_PULLUP);    
      //pinMode(1, INPUT_PULLUP);  
  }
  
  
  //sets time
  //setTime(21, 7, 0,31,3,2014);  
  
#if (USE_RTC)
  //check if rtc is ok or not
    if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
    }

    //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
    if (! rtc.isrunning()) {
      Serial.println("RTC is NOT running!");
      // following line sets the RTC to the date & time this sketch was compiled
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    } else {    
      Serial.println("RTC is running!");      
    }
#else
    //should be only done if not rtc
    rtc.begin(DateTime(__DATE__, __TIME__));
#endif
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
    if (readDButton(BUTTON_0)){
      DateTime future = dnow.unixtime() + 3600L;
      //rtc.adjust(future);    
    }
    if (readDButton(BUTTON_1)){
      DateTime future = dnow.unixtime() + 60L;
      //rtc.adjust(future);    
    }
    
     if (readDButton(BUTTON_0)){
       Serial.print("button 1 pressed");
    }
    if (readDButton(BUTTON_1)){
       Serial.print("button 2 pressed");
    }

  if (DEBUG_SERIAL) 
  {

  humidity    = /*(int)*/ dht.readHumidity();
  temperature = /*(int)*/ dht.readTemperature();
       dew_point   = dewPoint(temperature, humidity);
  
  Serial.print(chour,DEC);
  Serial.print(":");
  Serial.print(cminute,DEC);
  Serial.print(":");
  Serial.print(csecond,DEC);
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



