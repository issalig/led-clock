/*
  file: clock.ino
  description: clock functions
  date: 21/11/2015
  author: Ismael Salvador
*/


void setup_time(){
  
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
  //rtc.begin(DateTime(F(__DATE__), F(__TIME__)));
  
#endif


}

void read_time() {
  //get data

  if (USE_RTC) {
    dnow = rtc.now();
    chour   = dnow.hour();
    cminute = dnow.minute();

    cyear   = dnow.year();
    cmonth  = dnow.month();
    cday    = dnow.day();
    csecond = dnow.second();

  }
  
    time_t t = now(); // Store the current time
    chour = hour(t);
    cminute = minute(t);

    cyear = year(t);
    cmonth = month(t);
    cday = day(t);
    csecond = second(t);

}

void draw_time() {
  if (mode != MODE_OFF) {
    
      #if (NUMBER_CLOCK)
        //set_led_number_clock();
        set_led_hex_clock();
      #endif
      #if (WORD_CLOCK)
        set_led_word_clock();
      #endif          
    
    //set_led_word_clock();

    //write leds for an amount of time
    /*
    if (NUMBER_CLOCK)
      refresh_delay = 50;
    else if (WORD_CLOCK)
      refresh_delay = 50;
    */
    
    draw_matrix(0, intensity);
  }
}

void print_debug_info() {

  if  (DEBUG_SERIAL)
  {

    humidity    = /*(int)*/ dht.readHumidity();
    temperature = /*(int)*/ dht.readTemperature();
    dew_point   = dewPoint(temperature, humidity);

    if (chour < 10)
      Serial.print("0");
    Serial.print(chour, DEC);
    Serial.print(":");
    if (cminute < 10)
      Serial.print("0");
    Serial.print(cminute, DEC);
    Serial.print(":");
     if (csecond < 10)
      Serial.print("0");
    Serial.print(csecond, DEC);
    Serial.print(" Moon: ");
    Serial.print(moon / 2);
    Serial.print(" Temp: ");
    Serial.print(temperature);
    Serial.print(" Hum: ");
    Serial.print(humidity);
    Serial.print(" Dew point: ");
    Serial.print(dew_point);
    //Serial.print(" ");
    //Serial.print(((csecond + 7) / 15) % 4);
    Serial.print("\n");
  }
}
