/*
  file: number.ino
  description: led masks for number-clock mode
  date: 08/11/2015
  author: Ismael Salvador
*/

#if (NUMBER_CLOCK)

#include "DHT.h"
extern DHT dht;
extern int weather;

#include "number.h"

//m_day_ten
//m_day_unit
//m_month
//m_hour
//m_min
//m_min_unit
//m_weather
//m_arrow
//m_pulse
//m_moon

void set_led_number_dew_point() {
  int weather;
  //show dew point
  if (dew_point > 18)
    weather = 2; //humid
  else if (dew_point > 10 )
    weather = 1; //confortable
  else
    weather = 0; //dry

  set_led_mask(m_weather, weather);
}
/*
void set_led_number_pressure_fc() {
  float sensor_pressure = (bmp.readPressure() + bmp.readPressure()) / 2;
  int pressure_fc = pressure_forecast_simple(sensor_pressure);

  set_led_mask(m_weather, weather);
}
*/

void set_led_number_weather() {
  int weather;
  if (USE_DHT11) {
    //refresh measures every half minute, it takes sometime in DHT11
    //if ((csecond % 30) == 0) {
    humidity    = (int) dht.readHumidity();
    temperature = (int) dht.readTemperature();
    dew_point   = dewPoint(temperature, humidity);
    //}

    //show it for 10 seconds every half minute or pressed button
    //if (((csecond % 30) < 10) || (LOW == digitalRead(BUTTON_1))) {
    fill_matrix(0);
    set_led_mask(m_hour, (int)(humidity / 10)); //use hour to display humidity
    set_led_mask(m_min, (int)temperature / 10); //use mins to display temperature
    set_led_mask(m_min_unit, (int)temperature % 10);
    //}

    set_led_number_dew_point();
  }
  //int press_fc = pressure_forecast(int diff_pressure, int diff_time_sec);
  //if (press_fc > 3) press_fc = 0;
  //set_led_mask(m_arrow, press_fc);


}

void set_led_number_hour() {
  if (chour > 11)
    set_led_mask(m_pulse, 0);
  set_led_mask(m_hour, chour % 12);
}

void set_led_number_minute() {
  set_led_mask(m_min, cminute / 10);
  set_led_mask(m_min_unit, cminute % 10);
}

void set_led_number_moon() {
  int moon = moon_phase(cyear, cmonth, cday);
  set_led_mask(m_moon, moon / 2); //0-7 phases
}

//main function
void set_led_number_clock() {
  set_led_mask(m_hour, chour % 12);
  set_led_mask(m_min, cminute / 10);
  set_led_mask(m_min_unit, cminute % 10);

  if (csecond % 2)
    set_led_mask(m_pulse, 0);

  //set_led_number_weather();
  set_led_number_dew_point();

  moon = moon_phase(cyear, cmonth, cday);
  set_led_mask(m_moon, moon / 2); //0-7 phases

  //set_led_mask(m_arrow, csecond / 15);

  if ((cday / 10) > 0)
    set_led_mask(m_day_ten, cday / 10);
  set_led_mask(m_day_unit, cday % 10);

  set_led_mask(m_month, cmonth - 1);
}

void set_led_hex_clock() {
  set_led_mask(hx_hour, chour % 12);
  set_led_mask(hx_min, (cminute-5) % 10);

  if (csecond % 2)
    set_led_mask(hx_symbol, 2); //central point

  //set_led_number_weather();
  //set_led_number_dew_point();

  //moon = moon_phase(cyear, cmonth, cday);
  //set_led_mask(m_moon, moon / 2); //0-7 phases

  //set_led_mask(m_arrow, csecond / 15);
}
#endif




