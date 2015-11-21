/*
  ===================================
  Led Matrix Clock
  A word clock and whatever you want!
  ===================================

  file: led_clock.ino
  description: led-clock
  date: 25/05/2014
  author: Ismael Salvador
*/

#include "config.h"

//#include <Button.h>
#include <ButtonJC.h>
#include <Time.h>
#include <TimeAlarms.h>

#include "DHT.h"
#include "LedControl.h"

#include <Wire.h>
#include "RTClib.h"

#include <Cmd.h>

#define DEBUG_SERIAL 0

//clock type
#define WORD_CLOCK   1
#define NUMBER_CLOCK 0

//common cathode or anode led matrix
#define USE_7219_C_CATHODE 0
#define USE_7219_C_ANODE   1

#define USE_RTC 1
#define USE_BUTTONS 1
#define USE_DHT11       1
#define USER_SOFT_I2C   1


enum {MODE_OFF, MODE_ON, MODE_HOUR, MODE_MINUTE};
enum {SET_PLUS};

// global variables
int cyear, cmonth, cday, chour, cminute, csecond; //time
double humidity, temperature, dew_point; //weather
int moon; //moon
int refresh_delay;
int mode;

#if (USE_RTC)
RTC_DS1307 rtc;
#else
RTC_Millis rtc;
#endif

DHT dht(DHT_PIN, DHT11);

//Button button_mode = Button(BUTTON_MODE, PULLUP);
//Button button_set = Button(BUTTON_SET, PULLUP);
ButtonJC button_mode(BUTTON_MODE, true, true, 20);//, PULLUP, INVERT, DEBOUNCE_MS);
ButtonJC button_set(BUTTON_SET, true, true, 20);//, PULLUP, INVERT, DEBOUNCE_MS);

DateTime dnow;

//preparing the luggage
void setup() {

  Serial.begin(9600);
  cmd_help(0, NULL);
  
  if (USE_DHT11) {    
    dht.begin();
  }

  if (USE_BUTTONS) {
    //configure pullups
    initButton(BUTTON_0);
    initButton(BUTTON_1);
  }

  init_matrix_pins();

  setup_time();
  setup_cmds();
  
  mode = MODE_ON;
  
  //read_time();
  //setTime(chour,cminute,csecond,cday,cmonth,cyear);  
  //Alarm.timerRepeat(5, led_alarm);  
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday 
}

//let's go for a trip
void loop() {
  if (mode == MODE_ON) {
    read_time();
    fill_matrix(0);   //clear screen
    draw_time();
  }
  manage_buttons();
  cmdPoll();
  //print_debug_info();

}

