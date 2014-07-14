//http://en.wikipedia.org/wiki/Dew_point

// dewPoint function NOAA
// reference: wahiduddin.net/calc/density_algorithms.htm
double dewPoint(double celsius, double humidity){
  double a0= 373.15/(273.15 + celsius);
  double sum = -7.90298 * (a0-1);
  sum += 5.02808 * log10(a0);
  sum += -1.3816e-7 * (pow(10, (11.344*(1-1/a0)))-1) ;
  sum += 8.1328e-3 * (pow(10,(-3.49149*(a0-1)))-1) ;
  sum += log10(1013.246);
  double vp = pow(10, sum-3) * humidity;
  double t = log(vp/0.61078); // temp var
  return (241.88 * t) / (17.558-t);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
double dewPointFast(double celsius, double humidity){
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity/100);
  double Td = (b * temp) / (a - temp);
  return Td;
}

//http://en.wikipedia.org/wiki/Humidex
float calculate_humidex(float temperature,float humidity) {
  float e;

  e = (6.112 * pow(10,(7.5 * temperature/(237.7 + temperature))) * humidity/100); //vapor pressure
  float humidex = temperature + 0.55555555 * (e - 10.0); //humidex
  return humidex;
}

//returns humidex level 0 is good, 5 is bad
int get_humidex_level(float humidex)
{
  if ((humidex >= 21 )&&(humidex < 27))
  {
    //No discomfort
    level=0;
  }
  else if ((humidex >= 27 )&&(humidex < 35))
  {
    //Some discomfort
    level=1;
  }
  else if ((humidex >= 35 )&&(humidex < 40))
  {
    //Great discomfort
    level=2;
  }
  else if ((humidex >= 40 )&&(humidex < 46))
  {
    //Health risk
    level=3;
  }
  else if ((humidex >= 46 )&&(humidex < 54))
  {
    //Great health risk
    level=4;
  }
  else if ((humidex >= 54 ))
  {
    //Heat stroke danger
    level=5;
  }
  
  return level;
}
