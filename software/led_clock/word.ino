/*
  file: word.ino
  description: functions for time words
  date: 25/05/2014
  author: Ismael Salvador
*/

//#if (WORD_CLOCK)
#include "word.h"

void led_alarm(){//int arg_cnt, char **args){
  fill_matrix(1);
  draw_matrix(0, intensity);
  delay(1);
  fill_matrix(0);
  draw_matrix(0, intensity);
}


//mainly used to set time
//display mins in tens and units using hour numbers
//a special symbol is reserved for 0
void set_led_mins_word_clock(){ 
  int ten, unit;
  ten = (int)(cminute/10);
  if (ten > 0)
    set_led_mask(w_hour, ten);
  
  unit =(cminute)%10;
  if (unit == 0)
    set_led_mask(w_symbol, 0);
  else
    set_led_mask(w_hour, unit);
}

//mainly used to set time
//display hours using special symbol for PM
void set_led_hour_word_clock(){    
  if (chour > 12) //if PM use symbol to indicate it
    set_led_mask(w_symbol, 0);
  set_led_mask(w_hour, chour%12);
   
}

//word clock gives time in "human" way
//using hours and reference to the quarter

void set_led_word_clock(){ 
    //show next hour if minutes over 37
    if (cminute > 37)
      set_led_mask(w_hour, (chour+1)%12);
    else 
      set_led_mask(w_hour, (chour)%12);

  //[52.7,7.5]   o'clock
  //[8,22.5]     quarter past
  //[22.5,37.5]  half
  //[37.5-52.5]  quarter to
      
  int q=((cminute+7)/15)%4;
  set_led_mask(w_quarter, q);
}

//#endif
