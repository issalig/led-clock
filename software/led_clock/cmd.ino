/*
  file: cmd.ino
  description: serial cmd functions
  date: 21/11/2015
  author: Ismael Salvador
*/

void setup_cmds() {
  cmdInit(&Serial);
  cmdAdd("date", cmd_date);
  cmdAdd("minute", cmd_minute);
  cmdAdd("hour", cmd_hour);

  //cmdAdd("alarm", cmd_date);
  cmdAdd("help", cmd_help);
  cmdAdd("off", cmd_off);
  cmdAdd("on", cmd_on);
}

void cmd_date(int arg_cnt, char **args)
{
  if (arg_cnt > 1) {
    read_time();
    Serial.println("Changing hour");
    cday = cmdStr2Num(args[3], 10);
    cmonth = cmdStr2Num(args[2], 10);
    cyear = cmdStr2Num(args[1], 10);
    chour = cmdStr2Num(args[4], 10);
    cminute = cmdStr2Num(args[5], 10);
    csecond = cmdStr2Num(args[6], 10);
    //sets time
    rtc.adjust(DateTime(cyear, cmonth, cday, chour, cminute, csecond));
  }

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
}

void cmd_minute(int arg_cnt, char **args)
{

  if (arg_cnt == 1)
  {
    Serial.println(cminute, DEC);
  }
  else
  {
    read_time();
    cminute = cmdStr2Num(args[1], 10);
    //sets time
    rtc.adjust(DateTime(cyear, cmonth, cday, chour, cminute, csecond));
  }
  print_debug_info();
}

void cmd_hour(int arg_cnt, char **args)
{

  if (arg_cnt == 1)
  {
    Serial.println(chour, DEC);
  }
  else
  {
    read_time();
    chour = cmdStr2Num(args[1], 10);
    //sets time
    rtc.adjust(DateTime(cyear, cmonth, cday, chour, cminute, csecond));
  }
  print_debug_info();
}

void cmd_on(int arg_cnt, char **args) {
  mode = MODE_ON;
  lc.shutdown(0, false); //sleep
  lc.shutdown(1, false); //sleep
}

void cmd_off(int arg_cnt, char **args) {
  //fill_matrix(0);
  //draw_matrix(refresh_delay);

  for (int i = 15; i > 0; i--) {
    lc.setIntensity(0, i); //medium intensity
    lc.setIntensity(1, i); //medium intensity
    delay(100);
  }
  lc.clearDisplay(0);   //clear display(0);
  lc.clearDisplay(1);   //clear display(0);
  lc.shutdown(0, true); //sleep
  lc.shutdown(1, true); //sleep

  mode = MODE_OFF;
}

void cmd_alarm() { //int arg_cnt, char **args){
  Serial.println("Alarm");
  fill_matrix(1);
  draw_matrix(0, intensity);
  delay(5);
  fill_matrix(0);
  draw_matrix(0, intensity);
}


void cmd_help(int arg_cnt, char **args) {
  Serial.println("LED CLOCK v.0.3 htpps://github.com/issalig/led-clock");
  Serial.print("Compiled on ");
  Serial.print(F(__DATE__));  Serial.print(" ");
  Serial.println(F(__TIME__));
  Serial.println("----------------------------------------------------\n");
  Serial.println("on: Switch on");
  Serial.println("off: Switch off");
  Serial.println("date [YYYY MM DD hh mm ss]: Get/Set date");
  Serial.println("hour [number]: Get/Set hour");
  Serial.println("minute [number]: Get/Set minute");
  Serial.println("help: This help");
}

