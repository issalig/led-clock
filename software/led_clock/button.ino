/*
  file: button.ino
  description: button functions
  date: 25/05/2014
  author: Ismael Salvador
*/

void initButton(int num){
   pinMode(num, INPUT_PULLUP);
}

int readAButton(int num){
  int button = 1; 
  if (analogRead(num) > 16) 
      button = 0;

  return button;
}

int readDButton(int num){
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
      fill_matrix(1);
      draw_matrix(refresh_delay);
      fill_matrix(0);
      draw_matrix(refresh_delay);
      mode = MODE_OFF;
      Serial.print("LONG ");
      Serial.println(mode);
    }
  }
  //
  //if (readDButton(BUTTON_MODE)) {
  if (button_mode.wasPressed()) {
    mode = (mode + 1) % 4;
    //fill_matrix(0);
    //set_led_number(mode * 8);
    //draw_matrix(refresh_delay);
    Serial.print("M ");
    Serial.println(mode);
  }

  //if (readDButton(BUTTON_SET)) {
  if (button_set.wasPressed()) {
    set_led_number(mode * 8 + 7);
    draw_matrix(refresh_delay);
    if (mode == MODE_HOUR) {
      DateTime future = dnow.unixtime() + 3600L;
      rtc.adjust(future);
      read_time();
      Serial.print("+H ");
      Serial.print(chour);
      //Serial.println(mode);
      fill_matrix(0);
      set_led_hour_word_clock();
      draw_matrix(50);
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
      set_led_mins_word_clock();
      draw_matrix(50); //this delay sholud not exist
      //keep this while in set mode
      //exit mode after 5 seconds without activity
    }
  }

  if (button_mode.releasedFor(60000) && button_set.releasedFor(60000) && cmdTimeout(60000)) { //60 secs
    if (mode != MODE_OFF) {
      Serial.println(mode);
      fill_matrix(1);
      draw_matrix(refresh_delay);
      fill_matrix(0);
      draw_matrix(refresh_delay);
      mode = MODE_OFF;
      Serial.print("Auto off ");
      Serial.println(mode);
    }
  }

}

