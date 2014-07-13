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
