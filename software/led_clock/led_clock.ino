/*
  ===================================
  Led Matrix Clock
  A word clock and whatever you want!
  https://github.com/issalig/ledclock
  ===================================

  file: led_clock.ino
  description: led clock
  date: 25/05/2014
  author: Ismael Salvador
*/

//includes
#include "config.h"


#if defined(__AVR__)
#include <avr/sleep.h>
// #elif defined(ESP8266)
// #include <sleep.h>
#endif



#include <ButtonJC.h>
#include <Time.h>
#include <TimeAlarms.h>

//#include <Adafruit_Sensor.h>
#include "DHT.h"

//#ifdef USE_MATRIX_7219
  #include "LedControl.h"
//#endif

#include <Wire.h>
#include "RTClib.h"

#include <Cmd.h>

#include "FastLED.h"

#define DEBUG_SERIAL 1//0

//use eeprom for mask (saves ram space)
#define USE_EEPROM

//clock type
#define WORD_CLOCK   0
#define NUMBER_CLOCK 1
//#define HEX_CLOCK    1  //HEX is a special case of NUMBER

//common cathode or anode led matrix
#define USE_7219_C_CATHODE 0
#define USE_7219_C_ANODE   0

#define USE_RTC         0//1
#define USE_BUTTONS     0//1
#define USE_DHT11       0//1
#define USER_SOFT_I2C   1


enum {MODE_OFF, MODE_ON, MODE_HOUR, MODE_MINUTE};
enum {SET_PLUS};

// global variables
int cyear, cmonth, cday, chour, cminute, csecond; //time
double humidity, temperature, dew_point; //weather
int moon; //moon
long int refresh_delay = 5000; //once a second 60000; //refresh once a minute
int mode;
int intensity = 8;
long int last_refresh = 0;

#if (USE_RTC)
RTC_DS1307 rtc;
#else
RTC_Millis rtc;
#endif

DHT dht(DHT_PIN, DHT11);

//#if USE_MATRIX_7219
LedControl lc = LedControl(9, 8, 7); //dataIn7219, clk7219, load7219, 4); //up to 4 devices
//#endif

//https://forum.mysensors.org/topic/2169/wall-mounted-mood-light/11
//Button button_mode = Button(BUTTON_MODE, PULLUP);
//Button button_set = Button(BUTTON_SET, PULLUP);
ButtonJC button_mode(BUTTON_MODE, true, true, 20);//, PULLUP, INVERT, DEBOUNCE_MS);
ButtonJC button_set(BUTTON_SET, true, true, 20);//, PULLUP, INVERT, DEBOUNCE_MS);

#define WS_NUM_LEDS 19
#define BRIGHTNESS 128
CRGB wsleds[WS_NUM_LEDS];

DateTime dnow;

//preparing the luggage
void setup() {

  Serial.begin(9600);
  cmd_help(0, NULL);

  if (USE_DHT11) {
    dht.begin();
  }

  init_matrix_pins();

  setup_time();
  setup_cmds();

  mode = MODE_ON;

  //read_time();
  //setTime(chour,cminute,csecond,cday,cmonth,cyear);
  //Alarm.timerRepeat(5, led_alarm);
  //Alarm.alarmRepeat(dowSaturday,8,30,30,WeeklyAlarm);  // 8:30:30 every Saturday
  weather_setup();
}

//let's go for a trip
void loop() {
  if (mode == MODE_ON) {
    //if (1){ 
    if (millis() > (last_refresh + refresh_delay)) {
      last_refresh = millis();
      read_time();
      fill_matrix(0);   //clear screen
      //if (!button_set.isPressed())
        draw_time();
       print_debug_info();
    }
  }
  #if USE_BUTTONS 
  manage_buttons();
  #endif
  cmdPoll();
  //print_debug_info();
  //weather_update();
}

