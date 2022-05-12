
#define LeftPump 4 //commande Pompes à vide
#define MidPump 7 //
#define RightPump 12 //
#define LeftValve 5 //commandes électrovannes
#define MidValve 8 //
#define RightValve 11 //



void setup() {
  Serial.begin(9600);
  pinMode(LeftPump,OUTPUT);
  pinMode(MidPump,OUTPUT);
  pinMode(RightPump,OUTPUT);
  pinMode(LeftPump, OUTPUT);
  pinMode(MidPump, OUTPUT);
  pinMode(RightPump, OUTPUT);
}

void loop() {
  /*
  * 
  * 
  * ____________préhension/stockage des éléments de jeu ____________
  *
  *
  */

  /*
   * Stockage à gauche
   */
   
  takeSample(MidPump, MidValve);
  delay(3000); //à modifier
  takeSample(LeftPump, LeftValve);
  delay(1000);
  releaseSample(MidPump, MidValve);
  delay(3000); //à modifier

  /*
   * Stockage à droite
   */
   
  takeSample(MidPump, MidValve);
  delay(3000); //à modifier
  takeSample(RightPump, RightValve);
  delay(1000);
  releaseSample(MidPump, MidValve);
  delay(3000); //à modifier

  /*
   * Stockage à gauche
   */
   
  takeSample(MidPump, MidValve);
  delay(3000);

  /*
  * 
  * 
  * ____________relâchement des éléments de jeu ____________
  *
  *
  */
  releaseSample(MidPump, MidValve);
  delay(3000); //à modifier
  
  takeSample(MidPump, MidValve);
  delay(1000);
  releaseSample(RightPump, RightValve);
  delay(1000);
  releaseSample(MidPump, MidValve);
  delay(3000); //à modifier
  
  takeSample(MidPump, MidValve);
  delay(1000);
  releaseSample(LeftPump, LeftValve); 
  delay(1000);
  releaseSample(MidPump, MidValve);
  delay(3000); //à modifier
}


void takeSample(const byte pinPump, const byte pinValve){
  digitalWrite(pinPump, HIGH);
  digitalWrite(pinValve, LOW);
  Serial.print("échantillon pris sur la ventouse");
}

void releaseSample(const byte pinPump, const byte pinValve) {
  digitalWrite(pinPump, LOW);
  digitalWrite(pinValve, HIGH);
  Serial.print("échantillon relaché de la ventouse");
}
