/*
  file: number.h
  description: led masks for number-clock mode
  date: 08/11/2015
  author: Ismael Salvador
*/

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

const byte m_day_ten[]={
//0
B00100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//1
B10000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//2
B01000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//3
B00000000,
B00000000,
B00000000,
B10000000,
B00000000,
B00000000,
B00000000,
B00000000
};
const byte m_day_unit[]={
//0
B00100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//1
B00000000,
B10000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//2
B00000000,
B00000000,
B10000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//3
B00000000,
B00000000,
B00000000,
B10000000,
B00000000,
B00000000,
B00000000,
B00000000,
//4
B00000000,
B00000000,
B00000000,
B00000000,
B10000000,
B00000000,
B00000000,
B00000000,
//5
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B10000000,
B00000000,
B00000000,
//6
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B10000000,
B00000000,
//7
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B10000000,
//8
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01000000,
//9
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00100000
};
const byte m_month[]={
//0
B00010000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//1
B00001000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//2
B00000100,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//3
B00000010,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//4
B00000001,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//5
B00000000,
B00000001,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//6
B00000000,
B00000000,
B00000001,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//7
B00000000,
B00000000,
B00000000,
B00000001,
B00000000,
B00000000,
B00000000,
B00000000,
//8
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000000,
B00000000,
B00000000,
//9
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000000,
B00000000,
//10
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000001,
B00000000,
//11
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000001
};
const byte m_hour[]={
//0
B00000000,
B00000000,
B00000010,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//1
B00000000,
B01000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//2
B00000000,
B00100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//3
B00000000,
B00010000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//4
B00000000,
B00001000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//5
B00000000,
B00000100,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//6
B00000000,
B00000010,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//7
B00000000,
B00000000,
B01000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//8
B00000000,
B00000000,
B00100000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//9
B00000000,
B00000000,
B00010000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//10
B00000000,
B00000000,
B00001000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
//11
B00000000,
B00000000,
B00000100,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000
};
const byte m_min[]={
//0
B00000000,
B00000000,
B00000000,
B01000000,
B00000000,
B00000000,
B00000000,
B00000000,
//1
B00000000,
B00000000,
B00000000,
B00100000,
B00000000,
B00000000,
B00000000,
B00000000,
//2
B00000000,
B00000000,
B00000000,
B00010000,
B00000000,
B00000000,
B00000000,
B00000000,
//3
B00000000,
B00000000,
B00000000,
B00001000,
B00000000,
B00000000,
B00000000,
B00000000,
//4
B00000000,
B00000000,
B00000000,
B00000100,
B00000000,
B00000000,
B00000000,
B00000000,
//5
B00000000,
B00000000,
B00000000,
B00000010,
B00000000,
B00000000,
B00000000,
B00000000
};
const byte m_min_unit[]={
//0
B00000000,
B00000000,
B00000000,
B00000000,
B01000000,
B00000000,
B00000000,
B00000000,
//1
B00000000,
B00000000,
B00000000,
B00000000,
B00100000,
B00000000,
B00000000,
B00000000,
//2
B00000000,
B00000000,
B00000000,
B00000000,
B00010000,
B00000000,
B00000000,
B00000000,
//3
B00000000,
B00000000,
B00000000,
B00000000,
B00001000,
B00000000,
B00000000,
B00000000,
//4
B00000000,
B00000000,
B00000000,
B00000000,
B00000100,
B00000000,
B00000000,
B00000000,
//5
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01000000,
B00000000,
B00000000,
//6
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00100000,
B00000000,
B00000000,
//7
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00010000,
B00000000,
B00000000,
//8
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001000,
B00000000,
B00000000,
//9
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000100,
B00000000,
B00000000
};
const byte m_weather[]={
//0
B00000000,
B00000000,
B00000000,
B00000000,
B00000010,
B00000000,
B00000000,
B00000000,
//1
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000010,
B00000000,
B00000000,
//2
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000010,
B00000000
};
const byte m_arrow[]={
//0
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B01000000,
B00000000,
//1
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00100000,
B00000000,
//2
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00010000,
B00000000,
//3
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001000,
B00000000
};
const byte m_pulse[]={
//0
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000100,
B00000000
};
const byte m_moon[]={
//0
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00010000,
//1
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00001000,
//2
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000100,
//3
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000000,
B00000010
};

