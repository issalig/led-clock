void initButton(int num){
   pinMode(num, INPUT_PULLUP);
}

int readButton(int num){
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
