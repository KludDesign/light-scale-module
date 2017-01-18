#include <Wire.h>

int ValKgEsclave1;
int ValKgEsclave2;
int ValKgEsclave3;
int ValKgEnfant;
int ValKgAdulte;
int ValKgAgee;
int row;

const byte col = 9;

const int latchPin = 8; //Pin connected to latch pin (ST_CP) of 74HC595
const int clockPin = 12; //Pin connected to clock pin (SH_CP) of 74HC595
const int dataPin = 11; //Pin connected to Data in (DS) of 74HC595

// Table des leds à allumer


unsigned int sequence[][col] = {
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00001111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B01111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000001, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000011, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00000111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00001111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00011111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B00111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B01111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000000, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000001, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000011, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00000111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00001111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00011111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B00111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B01111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000000, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000001, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000011, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00001111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00011111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B00111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B01111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000000, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000001, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000011, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00001111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00011111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B00111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B01111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000000, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000001, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000011, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00000111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00001111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00011111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B00111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B01111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000000, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000001, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000011, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00000111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00001111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00011111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B00111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B01111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111,
    B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111};

void setup() {
  
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
  
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
}

void loop() {
  
    Wire.requestFrom(1, 1);    // request 6 bytes from slave device #2
    while (Wire.available()) { // slave may send less than requested
      ValKgEsclave1 = Wire.read(); // Récupère la valeur de slave 1
    }

    delay(500);
    
    Wire.requestFrom(2, 1);    // request 6 bytes from slave device #2
    while (Wire.available()) { // slave may send less than requested
      ValKgEsclave2 = Wire.read(); // Récupère la valeur de slave 2
    }

    delay(500);

    Wire.requestFrom(3, 1);    // request 6 bytes from slave device #2
    while (Wire.available()) { // slave may send less than requested
      ValKgEsclave3 = Wire.read(); // Récupère la valeur de slave 3
    }

    // Ajustement des valeurs récupéré par Arduino maître via le I2C pour être à 0
    ValKgEsclave1 = ValKgEsclave1-10;
    ValKgEsclave2 = ValKgEsclave2-35;
    ValKgEsclave3 = ValKgEsclave3-6;

    delay(500);

    Serial.println(ValKgEsclave1, DEC);
    Serial.println(ValKgEsclave2, DEC);
    Serial.println(ValKgEsclave3, DEC);
    Serial.println("");
   
  // Si poids sup à 100kg
  if (ValKgEsclave1 > 100 || ValKgEsclave2 > 100 || ValKgEsclave3 > 100){
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][0]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][1]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][2]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][3]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][4]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][5]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][6]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][7]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][8]);
          digitalWrite(latchPin, HIGH);}
  else{

      // Si deux personnes montent en même temps
      if (ValKgEsclave1>15 && ValKgEsclave2>15 || ValKgEsclave1>15 && ValKgEsclave3>15 || ValKgEsclave2>15 && ValKgEsclave3>15){
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][0]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][1]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][2]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][3]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][4]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][5]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][6]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][7]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[73][8]);
          digitalWrite(latchPin, HIGH);
          delay(200);
          digitalWrite(latchPin, LOW);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][0]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][1]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][2]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][3]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][4]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][5]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][6]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][7]);
          shiftOut(dataPin, clockPin, MSBFIRST, sequence[1][8]);
          digitalWrite(latchPin, HIGH);
          }

     else{
        // Balance enfant
        if (ValKgEsclave1>ValKgEsclave2 && ValKgEsclave1>ValKgEsclave3){
          
            ValKgEnfant = (ValKgEsclave1)*0.7; //Quantité d'eau = 70%
            Serial.println(ValKgEnfant, DEC);
      
            for (int row = 0; row < ValKgEnfant; row++){
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][0]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][1]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][2]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][3]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][4]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][5]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][6]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][7]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][8]);
                digitalWrite(latchPin, HIGH);
              }
         }
      
        delay(300);
      
        // Balance personne adulte
        if (ValKgEsclave2>ValKgEsclave1 && ValKgEsclave2>ValKgEsclave3){
          
            ValKgAdulte = (ValKgEsclave2)*0.62; //Quantité d'eau = 62%
            Serial.println(ValKgAdulte, DEC);
            
            for (int row = 0; row < ValKgAdulte; row++){
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][0]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][1]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][2]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][3]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][4]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][5]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][6]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][7]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][8]);
                digitalWrite(latchPin, HIGH);
        
              }
         }
      
         delay(300);
      
      
        // Balance personne agée
        if (ValKgEsclave3>ValKgEsclave1 && ValKgEsclave3>ValKgEsclave2){
          
            ValKgAgee = (ValKgEsclave3)*0.55; //Quantité d'eau = 55%
            Serial.println(ValKgAgee, DEC);
            
            for (int row = 0; row < ValKgAgee; row++){
                digitalWrite(latchPin, LOW);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][0]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][1]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][2]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][3]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][4]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][5]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][6]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][7]);
                shiftOut(dataPin, clockPin, MSBFIRST, sequence[row][8]);
                digitalWrite(latchPin, HIGH);
        
             }
         } 
      }
  }
  delay(300);
}

