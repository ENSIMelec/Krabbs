#define PUMP1 4
#define PUMP2 5
#define PUMP3 6

#define VANNE1 7
#define VANNE2 8
#define VANNE3 9

#define BUTTON1 A0
#define BUTTON2 A1
#define BUTTON3 A2

#define VANNE_DELAY 150


bool active1, active2, active3;


void setup() {
  pinMode(PUMP1, OUTPUT);
  pinMode(PUMP2, OUTPUT);
  pinMode(PUMP3, OUTPUT);

  pinMode(VANNE1, OUTPUT);
  pinMode(VANNE2, OUTPUT);
  pinMode(VANNE3, OUTPUT);

  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  

  digitalWrite(VANNE1, 0);
  digitalWrite(VANNE2, 0);
  digitalWrite(VANNE3, 0);
  digitalWrite(PUMP1, 0);
  digitalWrite(PUMP2, 0);
  digitalWrite(PUMP3, 0);
  
}

void loop() {
  delay(50);
  bool b1 = !digitalRead(BUTTON1);
  bool b2 = !digitalRead(BUTTON2);
  bool b3 = !digitalRead(BUTTON3);

  if(b1){
    active1 = true;
    digitalWrite(PUMP1, 1);
  }

  
  if(b2){
    active2 = true;
    digitalWrite(PUMP2, 1);
  }

  
  if(b3){
    active3 = true;
    digitalWrite(PUMP3, 1);
  }

  if((!b1 && active1) || (!b2 && active2) || (!b3 && active3)){
    if(!b1 && active1){
      digitalWrite(PUMP1, 0);
      digitalWrite(VANNE1, 1);
    }
    if(!b2 && active2){
      digitalWrite(PUMP2, 0);
      digitalWrite(VANNE2, 1);
    }
    if(!b3 && active3){
      digitalWrite(PUMP3, 0);
      digitalWrite(VANNE3, 1);
    }
    
    delay(VANNE_DELAY);

    if(!b1 && active1){
      digitalWrite(VANNE1, 0);
      active1 = false;
    }
    if(!b2 && active2){
      digitalWrite(VANNE2, 0);
      active2 = false;
    }
    if(!b3 && active3){
      digitalWrite(VANNE3, 0);
      active3 = false;
    }
  }
  
  

  
}
