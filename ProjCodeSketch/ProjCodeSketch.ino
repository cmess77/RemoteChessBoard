#include <Servo.h>
#include <math.h>
Servo base;
Servo joint1;
Servo joint2;
Servo joint3;
Servo Rais; //may not be necessary, joint 3 may be raise
/*Chess squares are around 2-2.5 in,
 * will have place holder value in place currently*/
 //Disclaimer - pins will be declared based off of Arduino UNO pins - seems like it didn't matter
//declaring servo pins
int bp = 2;
int j1p = 3;
int j2p = 4;
int j3p = 5;
int Rp = 6;
//electromagnet
int elmag = 7;

//arm variables
int squareSide;
int dist;
int L1;
int L2;
int L3;
//angle vars
int pos = 90;
int ba = 0;
int j1a = 0;
int j2a = 0;
int j3a = 4;
int Ra = 5;
//final draft of code aims to recognize based off of chess notation

//x will be position data
void calcAng(int x, int y){
  dist = sqrt(x^2+y^2);
  float angb = 90 + atan(y/x);
  float angj1 = acos(dist/L1);
  float angj2 = 0;
}
void UpdArm(int x, int y){
  //to make the movement a little smoother
  
for (pos = 0; pos <= ba; pos += 1) { 
    // in steps of 1 degree
    base.write(pos);              
    delay(5);
}
for (pos = 0; pos <= j1a; pos += 1) { 
    // in steps of 1 degree
    joint1.write(pos);              
    delay(5);
}
for (pos = 0; pos <= j2a; pos += 1) { 
    // in steps of 1 degree
    joint2.write(pos);              
    delay(5);
}
for (pos = 90; pos <= j3a; pos += 1) { 
    // in steps of 1 degree
    joint3.write(pos);              
    delay(5);
}
for (pos = 90; pos <= Ra; pos += 1) { 
    // in steps of 1 degree
    Rais.write(pos);              
    delay(5);
}

}
void setup() {
  // put your setup code here, to run once:
base.attach(bp);
joint1.attach(j1p);
joint2.attach(j2p);
joint3.attach(j3p);
Rais.attach(Rp);
pinMode(elmag, OUTPUT);
//sets up the base for rotation in either direction
base.write(90);

Serial.begin(9600);

}

void loop() {
                         
  

}
