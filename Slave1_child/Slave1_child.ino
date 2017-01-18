#include <Wire.h>
#include <WheatstoneBridge.h>

WheatstoneBridge wsb_strain1(A0, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain2(A1, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain3(A2, 365, 675, 0, 1000);
WheatstoneBridge wsb_strain4(A3, 365, 675, 0, 1000);

int val1;
int val2;
int val3;
int val4;
int valRaw1;
int valRaw2;
int valRaw3;
int valRaw4;
int ValTotal;
int ValKg;

void requestEvent() {
  //Calcul du poids 
  val1 = wsb_strain1.measureForce();
  valRaw1 = wsb_strain1.getLastForceRawADC();
  val2 = wsb_strain2.measureForce();
  valRaw2 = wsb_strain2.getLastForceRawADC();
  val3 = wsb_strain3.measureForce();
  valRaw3 = wsb_strain3.getLastForceRawADC();
  val4 = wsb_strain4.measureForce();
  valRaw4 = wsb_strain4.getLastForceRawADC();
  ValTotal = valRaw1+valRaw2+valRaw3+valRaw4;

  ValKg = (ValTotal - 1410)*0.28;
  
  Wire.write(ValKg); // respond with message of 6 bytes
  // as expected by master
}

void setup() {
  Wire.begin(1);                // join i2c bus with address #8
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()

