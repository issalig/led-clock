/*
  file: word.h
  description: masks for word mode
  date: 12/11/2015
  author: Ismael Salvador
*/


//MODIFY this file according to your word mask

//PROGMEM
//pgm_read_word_near(charSet + k);

const  byte w_hour[] /*PROGMEM*/ ={    
  B00000000, //0 == 12
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00001111,
  B00000000,
  B00000000,
  
  B11100000, //1
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000, 
  B00000000,
  
  B00000000, //2
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11100000, 
  B00000000,
  
  B00000000, //3
  B00000000,
  B00000000,
  B00000000,
  B00001111,
  B00000000,
  B00000000,
  B00000000,  
  
  B00000000, //4
  B00000111,
  B00000111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //5
  B00000000,
  B11111000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //6
  B00000000,
  B00000000,
  B11110000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00011111, //7
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //8
  B00000000,
  B00000000,
  B00001111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //9
  B11111000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //10
  B00000000,
  B00000000,
  B00000000,
  B11110000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //11
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11110000,
  B00000000,
  B00000000
};

const byte w_quarter[] /*PROGMEM*/ ={
  B00000000, //o'clock
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //1st quarter
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00010000, 
  B11111100,
  
  B00000000, //half
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00010111, 
  B00000011,
  
  B00000000, //3rd quarter
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00001000, 
  B11111100
};


const byte w_symbol[] /*PROGMEM*/ ={
  B00000000, //symbol
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00001000,
  B00000000
};

//second screen
const  byte w_hour2[]={    
  B00000000, //0 == 12
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00001111,
  B00000000,
  B00000000,
  
  B11100000, //1
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000, 
  B00000000,
  
  B00000000, //2
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11100000, 
  B00000000,
  
  B00000000, //3
  B00000000,
  B00000000,
  B00000000,
  B00001111,
  B00000000,
  B00000000,
  B00000000,  
  
  B00000000, //4
  B00000111,
  B00000111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //5
  B00000000,
  B11111000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //6
  B00000000,
  B00000000,
  B11110000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00011111, //7
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //8
  B00000000,
  B00000000,
  B00001111,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //9
  B11111000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //10
  B00000000,
  B00000000,
  B00000000,
  B11110000,
  B00000000,
  B00000000,
  B00000000,
  
  B00000000, //11
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B11110000,
  B00000000,
  B00000000
};