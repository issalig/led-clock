/*
  file: number.ino
  description: led masks for number-clock
  date: 25/05/2014
  author: Ismael Salvador
*/

//number clock
//leds are numbered sequentially from topleft
const byte Hled[]={
//  11,0,1,2,3,4,5,6,7,8,9,10}; //hours from 1-12
  9,10,11,12,13,14,17,18,19,20,21,22};
const byte Mled[]={
//  12,13,14,15,16,17}; // tens for minutes 0-5
25,26,27,28,29,30};
const byte mled[]={
//  18,19,20,21,22,24,25,26,27,28}; // units for minutes
33,34,35,36,37,  41,42,43,44,45};

const byte Dled[]={
 0,1,2,24 //tens of days 0-2
};
const byte dled[]={
 0,8,16,24,32,36,48,56,57,58, //units of days 0-9
};

const byte moonled[]={
//  30,31,32,33};
59,60,61,62};
const byte weatherled[]={ //good, normal, bad
  38,46,54};

const byte pulseled=53;//34;

const byte arrowled[]={ //up, right, down, left
49,50,51,52};


void set_led_hour(int hour){
  //set hour
  int led_hour= Hled[hour%12];
  set_led_number(led_hour);
}

void set_led_minute(int minute){
  //set tens
  int led_ten_min= Mled[minute/10];
  set_led_number(led_ten_min);

  //set units
  int led_unit_min= mled[minute%10];
  set_led_number(led_unit_min);  
}

void set_led_day(int day){
  //set tens
  set_led_number(Dled[day/10]);

  //set units
  set_led_number(dled[day%10]);  
}

void set_led_moon(int phase){
  //new; 0% illuminated ** 
  //Waxing crescent; 25% illuminated
  //First quarter; 50% illuminated **
  //Waxing gibbous; 75% illuminated
  //Full; 100% illuminated  **
  //Waning gibbous; 75% illuminated
  //Last quarter; 50% illuminated **
  //Waning crescent; 25% illuminated
  //default to new; 0% illuminated **
  set_led_number(moonled[phase/2]);

}

void set_led_arrow(){
  set_led_number(arrowled[csecond/15]);
}

void set_led_weather(){
  if (USE_DHT11) {      
     //refresh measures every half minute, it takes sometime in DHT11
     if ((csecond % 30) == 0) {
       humidity    = (int) dht.readHumidity();
       temperature = (int) dht.readTemperature();
       dew_point   = dewPoint(temperature, humidity);
     }
               
     //show it for 2 seconds every half minute or pressed button
     if (((csecond % 30) < 5) || (LOW == digitalRead(A0))) {
      fill_matrix(0);
      set_led_hour(humidity/10);
      set_led_minute(temperature);     
     }
     
     //show dew point
     if (dew_point > 18)
       set_led_number(weatherled[2]); //humid
     else if (dew_point > 10 )
        set_led_number(weatherled[1]); //confortable
     else 
        set_led_number(weatherled[0]); //dry
  }
  
}

void set_led_number_clock(){ 
  set_led_hour(chour);     
  set_led_minute(cminute);
  
  if(csecond%2)
    set_led_number(pulseled);
   
  //set_led_weather();
  
  moon = moon_phase(cyear, cmonth, cday);
  set_led_moon(moon);

  set_led_arrow();
  set_led_day(cday);
}
