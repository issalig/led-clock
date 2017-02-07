/*
  file: button.ino
  description: button functions
  date: 25/05/2014
  author: Ismael Salvador
*/

void initButton(int num) {
  pinMode(num, INPUT_PULLUP);
}

int readAButton(int num) {
  int button = 1;
  if (analogRead(num) > 16)
    button = 0;

  return button;
}

int readDButton(int num) {
  int button = 1;
  if (digitalRead(num) == HIGH)
    button = 0;
  return button;
}

void manage_buttons() {
  button_mode.read();
  button_set.read();

  //if pressed for more than 1 second switch off
  //dimming?
  if (button_mode.pressedFor(1000)) {
    if (mode != MODE_OFF) {
      for (int index = 0; index < lc.getDeviceCount(); index++) {
        for (int i = 15; i > 0; i--) {
          lc.setIntensity(index, i);
          delay(200);
        }
        lc.clearDisplay(index);
        lc.shutdown(index, true); //sleep
      }
      mode = MODE_OFF;
      Serial.print("LONG ");
      Serial.println(mode);

      sleepNow();
    }
  }
  //
  //if (readDButton(BUTTON_MODE)) {
  if (button_mode.wasPressed()) {
    mode = (mode + 1) % 4;

    if (mode == MODE_HOUR) {
      fill_matrix(0);
#if (WORD_CLOCK)
      set_led_hour_word_clock();
#elif (NUMBER_CLOCK)
      set_led_number_hour();
#endif
      draw_matrix(0, intensity);
    }
    else if (mode == MODE_MINUTE) {
      fill_matrix(0);
#if (WORD_CLOCK)
      set_led_mins_word_clock();
#elif (NUMBER_CLOCK)
      set_led_number_minute();
#endif
      draw_matrix(0, intensity);
    }
    //fill_matrix(0);
    //set_led_number(mode * 8);
    //draw_matrix(refresh_delay);
    for (int index = 0; index < lc.getDeviceCount(); index++)
      lc.shutdown(index, false);
    Serial.print("M ");
    Serial.println(mode);
  }

  //if (readDButton(BUTTON_SET)) {
  if (button_set.wasPressed()) {
    //set_led_number(mode * 8 + 7);
    draw_matrix(0, intensity);
    if (mode == MODE_HOUR) {
      DateTime future = dnow.unixtime() + 3600L;
      rtc.adjust(future);
      read_time();
      Serial.print("+H ");
      Serial.print(chour);
      //Serial.println(mode);
      fill_matrix(0);
#if (WORD_CLOCK)
      set_led_hour_word_clock();
#elif (NUMBER_CLOCK)
      set_led_number_hour();
#endif
      draw_matrix(0, intensity);
    } else if (mode == MODE_MINUTE) {
      DateTime future = dnow.unixtime() + 60L;
      rtc.adjust(future);
      read_time();
      Serial.print("+M");
      Serial.println(cminute);
      Serial.println((int)((cminute)) / 10);
      Serial.println(((cminute)) % 10);

      //Serial.println(mode);

      fill_matrix(0);
#if (WORD_CLOCK)
      set_led_mins_word_clock();
#elif (NUMBER_CLOCK)
      set_led_number_minute();
#endif
      draw_matrix(0, intensity);
      //keep this while in set mode
      //exit mode after 5 seconds without activity
    }
  }

  if (button_set.isPressed()) {       
    if (mode == MODE_ON) {
      fill_matrix(0);
      set_led_number_weather();
      set_led_number_moon();
      draw_matrix(0, intensity);
    }
  }

  //timeout mode_on after 5 sec
  if (button_mode.releasedFor(5000) && button_set.releasedFor(5000)) { //60 secs
    mode = MODE_ON;
  }

  //timeout switch off
  if (button_mode.releasedFor(60000) && button_set.releasedFor(60000) && cmdTimeout(60000)) { //60 secs
    if (mode != MODE_OFF) {

      for (int index = 0; index < lc.getDeviceCount(); index++) {
        for (int i = 15; i > 0; i--) {
          matrix_set_intensity(i, index); //lc.setIntensity(index, i);
          delay(200);
        }
        lc.clearDisplay(index);
        matrix_shutdown(index);//lc.shutdown(index, true); //sleep
      }
      mode = MODE_OFF;
      Serial.print("Auto off ");

    }
  }
}

//http://tae09.blogspot.com.es/2012/10/arduino-low-power-tutorial.html
void sleepNow()
{
  Serial.println("Good night");
#if defined(__AVR__)
  // Choose our preferred sleep mode:
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);//SAVE);
  //
  interrupts();
  // Set pin 2 as interrupt and attach handler:
  attachInterrupt(digitalPinToInterrupt(2), wakeMe, HIGH);
  //delay(100);
  //
  // Set sleep enable (SE) bit:

  sleep_enable();
  //
  // Put the device to sleep:
  digitalWrite(13, LOW);  // turn LED off to indicate sleep
  sleep_mode();
  //
  // Upon waking up, sketch continues from this point.
  sleep_disable();
  digitalWrite(13, HIGH);  // turn LED on to indicate awake
  
  lc.shutdown(0, false);
#elif defined(ESP8266)
//https://github.com/esp8266/Arduino/issues/1488
//https://learn.sparkfun.com/tutorials/esp8266-thing-hookup-guide/example-sketch-goodnight-thing-sleep-mode
  ESP.deepSleep(5 * 1000000); //us
#endif  
  Serial.println("Good morning");
  mode = MODE_ON;
}
void wakeMe()
{
  detachInterrupt(digitalPinToInterrupt(2));
  attachInterrupt(digitalPinToInterrupt(2), wakeMe, HIGH);
}


