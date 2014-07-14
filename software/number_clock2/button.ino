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
