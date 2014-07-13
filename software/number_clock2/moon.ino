//new; 0% illuminated               ** 0
//Waxing crescent; 25% illuminated     1
//First quarter; 50% illuminated    ** 2
//Waxing gibbous; 75% illuminated      3
//Full; 100% illuminated            ** 4
//Waning gibbous; 75% illuminated      5
//Last quarter; 50% illuminated     ** 6
//Waning crescent; 25% illuminated     7 
//default to new; 0% illuminated    ** 8

/*
http://www.nano-reef.com/topic/217305-a-lunar-phase-function-for-the-arduino/
http://en.wikipedia.org/wiki/Lunar_phase
*/

int moon_phase(int nYear, int nMonth, int nDay) // calculate the current phase of the moon
{
  float phase, phase2;
  double AG, IP;
  long YY, MM, K1, K2, K3, JD;
  YY = nYear - floor((12 - nMonth) / 10);
  MM = nMonth + 9;
  if (MM >= 12)
  {
    MM = MM - 12;
  }
  K1 = floor(365.25 * (YY + 4712));
  K2 = floor(30.6 * MM + 0.5);
  K3 = floor(floor((YY / 100) + 49) * 0.75) - 38;
  JD = K1 + K2 + nDay + 59;
  if (JD > 2299160)
  {
    JD = JD - K3;
  }
  //IP = MyNormalize2((JD - 2451550.1) / 29.530588853);
  
  IP=(JD - 2451550.1) / 29.530588853;
  IP = IP - floor(IP);
  if (IP < 0)
    IP = IP + 1;
  
  AG = IP*29.53;
  phase = 0;
  if ((AG < 1.84566) && (phase == 0))
  {
    phase = 0; //new; 0% illuminated
  }
  if ((AG < 5.53699) && (phase == 0))
  {
    phase = 1; //Waxing crescent; 25% illuminated
  }
  if ((AG < 9.922831) && (phase == 0))
  {
    phase = 2; //First quarter; 50% illuminated
  }
  if ((AG < 12.91963) && (phase == 0))
  {
    phase = 3; //Waxing gibbous; 75% illuminated
  }
  if ((AG < 16.61096) && (phase == 0))
  {
    phase = 4; //Full; 100% illuminated
  }
  if ((AG < 20.30228) && (phase == 0))
  {
    phase = 5; //Waning gibbous; 75% illuminated
  }
  if ((AG < 23.99361) && (phase == 0))
  {
    phase = 6; //Last quarter; 50% illuminated
  }
  if ((AG < 27.68493) && (phase == 0))
  {
    phase = 7; //Waning crescent; 25% illuminated
  }
  if (phase == 0)
  {
    phase = 8; //default to new; 0% illuminated
  }
  return phase;
}

double MyNormalize2(double v)
{
  v = v - floor(v);
  if (v < 0)
    v = v + 1;
  return v;
} 

