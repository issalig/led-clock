/*
  file: weather.ino
  description: weather functions
  date: 25/05/2014
  author: Ismael Salvador
*/

//references
//http://grotjahn.ucdavis.edu/course%2fatm111/fcstnbk-v2.doc/
//http://wx.erau.edu/reference/text/WXElements_TW_01Dec99.pdf
//https://github.com/RobTillaart/Arduino/blob/master/libraries/Temperature/temperature.h
//http://www.freescale.com/files/sensors/doc/app_note/AN3914.pdf
//http://www.mysensors.org/build/pressure

//Forecast based on pressure
#define FC_P_UNSTABLE_HIGH 0
#define FC_P_STABLE_GOOD   1 //GOOD
#define FC_P_STABLE        2
#define FC_P_STABLE_RAINY  3 //BAD
#define FC_P_UNSTABLE_LOW  4

//Forecast based on pressure and temp
#define FC_PT_HEAVY_RAIN          0  //BAD
#define FC_PT_RAIN                1  //BAD
#define FC_PT_VARIABLE_WEATHER    2  //MEDIUM
#define FC_PT_LIKELY_RAIN         3  //MEDIUM
#define FC_PT_GOOD_WEATHER        4  //GOOD
#define FC_PT_COLD_WIND           5  //GOOD
#define FC_PT_DRY_WEATHER         6  //GOOD

//Pressure status
#define PRESS_RISING           0
#define PRESS_STABLE           1
#define PRESS_FALLING          2

//Temp status
#define TEMP_RISING            0
#define TEMP_STABLE            1
#define TEMP_FALLING           2

//I2C needed by BMP085
#include <Wire.h>
#include <Adafruit_BMP085.h>

//time functions
//#include <Time.h>
//software timer
//#include <SimpleTimer.h>

// Connect VCC to breakout board w pullups to 5V/ 3.3 if not level shifter included
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

Adafruit_BMP085 bmp;

int weather_update_period = 60; //in seconds

int millis_start, millis_stop;

int diff_temp, current_temp, last_temp;
int diff_pressure, current_pressure, last_pressure;
int diff_altitude, current_altitude, last_altitude;

time_t last_time;

//SimpleTimer timer_get_data, timer_forecast;

/*
  Gives weather forecast based on pressure and temperature
*/
int pressure_temperature_forecast(int diff_pressure, int diff_temperature, int diff_time) {

  /*
              dP/dt >  250Pa/h                     Unstable high pressure system
     50Pa/h < dP/dt <  250Pa/h for some time       Stable good weather
    -50Pa/h < dP/dt <   50Pa/h for some time       Stable weather
    -250Pa/h < dP/dt <  -50Pa/h for some time       Stable rainy weather
              dP/dt < -250Pa/h                     Unstable low pressure system
  */

  /*
    Pressure     Temperature    Forecast
    Falling      Falling        Heavy Rain
    Falling      Stable         Rain
    Falling      Rising         Variable Weather
    Stable       Falling        Rain
    Stable       Stable         Variable Weather
    Stable       Rising         Good weather
    Rising       Falling        Cold wind
    Rising       Stable         Good weather
    Rising       Rising         Dry and hot weather
  */

  int pt_forecast;
  int pressure_tendency;
  int pressure_gradient = diff_pressure / diff_time;

  //discretise pressure
  if (pressure_gradient > 250) {
    pressure_tendency = PRESS_RISING;
  } else if (pressure_gradient > 50) {
    pressure_tendency = PRESS_STABLE;
  } else if (pressure_gradient > -50) {
    pressure_tendency = PRESS_STABLE;
  } else if (pressure_gradient > -250) {
    pressure_tendency = PRESS_STABLE;
  } else {
    pressure_tendency = PRESS_FALLING;
  }

  int temperature_tendency;
  int temperature_gradient = diff_temperature / diff_time;

#define THR_TEMP_RISING 1
#define THR_TEMP_STABLE 2

  //discretise temperature
  if (temperature_gradient > THR_TEMP_RISING)
    temperature_tendency = TEMP_RISING;
  else if (temperature_gradient > THR_TEMP_STABLE)
    temperature_tendency = TEMP_STABLE;
  else
    temperature_tendency = TEMP_FALLING;

  //get forecast
  if      ((pressure_gradient == PRESS_FALLING) && (temperature_gradient == TEMP_FALLING)) pt_forecast = FC_PT_HEAVY_RAIN;
  else if ((pressure_gradient == PRESS_FALLING) && (temperature_gradient == TEMP_STABLE))  pt_forecast = FC_PT_RAIN;
  else if ((pressure_gradient == PRESS_FALLING) && (temperature_gradient == TEMP_RISING))  pt_forecast = FC_PT_VARIABLE_WEATHER;
  else if ((pressure_gradient == PRESS_STABLE)  && (temperature_gradient == TEMP_FALLING)) pt_forecast = FC_PT_RAIN;
  else if ((pressure_gradient == PRESS_STABLE)  && (temperature_gradient == TEMP_STABLE))  pt_forecast = FC_PT_VARIABLE_WEATHER;
  else if ((pressure_gradient == PRESS_STABLE)  && (temperature_gradient == TEMP_RISING))  pt_forecast = FC_PT_GOOD_WEATHER;
  else if ((pressure_gradient == PRESS_RISING)  && (temperature_gradient == TEMP_FALLING)) pt_forecast = FC_PT_COLD_WIND;
  else if ((pressure_gradient == PRESS_RISING)  && (temperature_gradient == TEMP_STABLE))  pt_forecast = FC_PT_GOOD_WEATHER;
  else if ((pressure_gradient == PRESS_RISING)  && (temperature_gradient == TEMP_RISING))  pt_forecast = FC_PT_DRY_WEATHER;

  return pt_forecast;
}


/*
  Gives weather forecast based on pressure tendency
  info from http://molbio.uoregon.edu/~remington/scp1000_barometer.pdf
*/
int pressure_forecast(int diff_pressure, int diff_time_sec) {

  /*
              dP/dt >  250Pa/h                     Unstable high pressure system
     50Pa/h < dP/dt <  250Pa/h for some time       Stable good weather
    -50Pa/h < dP/dt <   50Pa/h for some time       Stable weather
    -250Pa/h < dP/dt <  -50Pa/h for some time       Stable rainy weather
              dP/dt < -250Pa/h                     Unstable low pressure system
  */

  int pressure_forecast;
  int pressure_gradient = (3600 * diff_pressure) / diff_time_sec; //changes per hour

  if (pressure_gradient > 250) {
    pressure_forecast = FC_P_UNSTABLE_HIGH;
  } else if (pressure_gradient > 50) {
    pressure_forecast = FC_P_STABLE_GOOD;
  } else if (pressure_gradient > -50) {
    pressure_forecast = FC_P_STABLE;
  } else if (pressure_gradient > -250) {
    pressure_forecast = FC_P_STABLE_RAINY;
  } else {
    pressure_forecast = FC_P_UNSTABLE_LOW;
  }

  return pressure_forecast;
}

//http://www.freescale.com/files/sensors/doc/app_note/AN3914.pdf
//ph = p0*e^(-h/7990m)
//Another approach that is more direct and quicker in calculating the weather in 
//the simple approach is to know the current altitude.
//This cuts the need to wait and see a “trend"
//p0 = 101.3 kPa, pressure for good sunny weather at current altitude
//h is the current altitude

int pressure_forecast_simple(float sensor_pressure) {
  int altitude = 0;
  int weather;
  float p_weather, weather_diff;
  
  p_weather =  (101.3 * exp(((float)(altitude)) / (-7900))); //good weather pressure at current altitude
  weather_diff = sensor_pressure - p_weather;
  if (weather_diff > 0.25)
    weather = 0; //sun
  if ((weather_diff <= 0.25) || (weather_diff >= (-0.25)))
    weather = 1; //sun/cloud
  if (weather_diff < (-0.25))
    weather = 2; //rain

  return weather;
}

/*
  Updates pressure readings
*/
void update_pressure() {
}

int updateMeasures(time_t before, time_t seconds) {
  int val = 0;
  time_t time_now = now(); // get current time in seconds

  //if seconds passed after last time update measures
  if ((last_time + seconds) < time_now) {
    /*
        Serial.print(last_time);
        Serial.print(" + ");
        Serial.print(seconds);
        Serial.print(" = ");
        Serial.print(last_time + seconds);
        Serial.print(" > ");
        Serial.print(time_now);
        Serial.println(" ");
    */
    last_time = time_now;
    current_temp     = bmp.readTemperature();
    //current_pressure = bmp.readPressure();
    current_pressure = (bmp.readPressure() + bmp.readPressure()) / 2;
    //    current_altitude = (bmp.readAltitude(101500) + bmp.readAltitude(101500))/2;

    diff_temp     = current_temp - last_temp;
    diff_pressure = current_pressure - last_pressure;
    diff_altitude = current_altitude - last_altitude;

    last_temp = current_temp;
    last_pressure = current_pressure;
    last_altitude = current_altitude;

    val = 1;
  }

  return val;
}

/*
  warming up
*/
void weather_setup() {
  //timer_get_data.setInterval(15000, RepeatTask); //udpateMeasures
  //timer_get_forecast.setInterval(15000, RepeatTask); //

  last_time = now();

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    //disable readings
    //weather_available=0;
  }
}

/*
  let's go to work
*/
void weather_update() {

  if (updateMeasures(last_time, weather_update_period) == 1) {
    int p_forecast = pressure_forecast(diff_pressure, weather_update_period);
    Serial.print("Pressure Forecast = ");
    Serial.println(p_forecast);

    int pt_forecast = pressure_temperature_forecast(diff_pressure, diff_temp, weather_update_period);
    Serial.print("Pressure Temp Forecast = ");
    Serial.println(pt_forecast);

    /*
      Serial.print("Diff pressure = ");
      Serial.println(diff_pressure);

      Serial.print("Temperature = ");
      Serial.print(bmp.readTemperature());
      Serial.println(" *C");

      Serial.print("Pressure = ");
      Serial.print(bmp.readPressure());
      Serial.println(" Pa");

      // Calculate altitude assuming 'standard' barometric
      // pressure of 1013.25 millibar = 101325 Pascal
      Serial.print("Altitude = ");
      Serial.print(bmp.readAltitude());
      Serial.println(" meters");

      Serial.println();
    */

  }
}


//Celsius to Fahrenheit conversion
double Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

//Celsius to Kelvin conversion
double Kelvin(double celsius)
{
  return celsius + 273.15;
}

//humidity
//http://en.wikipedia.org/wiki/Dew_point

// dewPoint function NOAA
// reference: wahiduddin.net/calc/density_algorithms.htm
double dewPoint(double celsius, double humidity) {
  double a0 = 373.15 / (273.15 + celsius);
  double sum = -7.90298 * (a0 - 1);
  sum += 5.02808 * log10(a0);
  sum += -1.3816e-7 * (pow(10, (11.344 * (1 - 1 / a0))) - 1) ;
  sum += 8.1328e-3 * (pow(10, (-3.49149 * (a0 - 1))) - 1) ;
  sum += log10(1013.246);
  double vp = pow(10, sum - 3) * humidity;
  double t = log(vp / 0.61078); // temp var
  return (241.88 * t) / (17.558 - t);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity) {
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
}

//http://en.wikipedia.org/wiki/Humidex
float calculate_humidex(float temperature, float humidity) {
  float e;

  e = (6.112 * pow(10, (7.5 * temperature / (237.7 + temperature))) * humidity / 100); //vapor pressure
  float humidex = temperature + 0.55555555 * (e - 10.0); //humidex
  return humidex;
}

/*
  //  http://www.ccacac.com/wp-content/uploads/2010/06/Humidex-Graph.pdf -
  double humidex(double celsius, double DewPoint)
  {
    double e = 19.833625 - 5417.753 /(273.16 + DewPoint);
    double h = celsius + 3.3941 * exp(e) - 5.555;
    return h;
  }
*/

//returns humidex level 0 is good, 5 is bad
int get_humidex_level(float humidex)
{
  int level;
  if ((humidex >= 21 ) && (humidex < 27)) {
    //No discomfort
    level = 0;
  } else if ((humidex >= 27 ) && (humidex < 35)) {
    //Some discomfort
    level = 1;
  } else if ((humidex >= 35 ) && (humidex < 40)) {
    //Great discomfort
    level = 2;
  } else if ((humidex >= 40 ) && (humidex < 46)) {
    //Health risk
    level = 3;
  } else if ((humidex >= 46 ) && (humidex < 54)) {
    //Great health risk
    level = 4;
  } else if ((humidex >= 54 )) {
    //Heat stroke danger
    level = 5;
  }

  return level;
}

//heat index
// TF = temp in F
// R = humidity in %
double heatIndex(double TF, double R)
{
  const double c1 = -42.379;
  const double c2 =  2.04901523;
  const double c3 = 10.14333127;
  const double c4 = -0.22475541;
  const double c5 = -0.00683783;
  const double c6 = -0.05481717;
  const double c7 =  0.00122874;
  const double c8 =  0.00085282;
  const double c9 = -0.00000199;

  double A = (( c5 * TF) + c2) * TF + c1;
  double B = (((c7 * TF) + c4) * TF + c3) * R;
  double C = (((c9 * TF) + c8) * TF + c6) * R * R;

  return A + B + C;
}

// less constants => faster but slightly inaccurate
// TF = temp in F
// R = humidity in %
double heatIndexFast(double TF, double R)
{
  const double c1 = -42.379;
  const double c2 =  2.04901523;
  const double c3 = 10.14333127;
  const double c4 = -0.22475541;

  double A = c2 * TF + c1;
  double B = (c4 * TF + c3) * R;

  return A + B;
}

// integer version
// TF = temp in F
// R = humidity in %
int heatIndexFastInt(int TF, int R)
{
  // consts multiplied by 1024
  long c1 = -43396;
  long c2 = 2098;
  long c3 = 10387;
  long c4 = -230;

  long A = c2 * TF + c1;  // so A is x 1024
  long B = (c4 * TF + c3) * R;  // and B too

  return (A + B + 512) / 1024; // division becomes a shift; +512 is for rounding
}
