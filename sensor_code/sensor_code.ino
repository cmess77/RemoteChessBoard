/*
TODO

- integrate servo code

*/

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>
#include <Adafruit_PWMServoDriver.h> 

const int num_hall = 4;
const int magEn = 22;
const int input1a = 23;
const int input2a = 24;
const int SERVOMIN0 = 108;// 0
const int SERVOMAX0 = 469;// 180
const int SERVOMAX1 = 88; // 180 degrees
const int SERVOMIN1 = 268; // 268 is 90 degrees//max act 400...
const int SERVOMIN2 = 220;//90
const int SERVOMAX2 = 395;//180
const int SERVO_FREQ = 50; // Analog servos run at ~50 Hz updates

//e4 correct angles
int  angbe4 = 96;
int  angj1e4 = 166;
int  angj2e4 = 110;
//e2 correct angles
int angbe2 = 119;
int angj1e2 = 164;
int angj2e2 = 118;

const float h = 9.437-1.6; //correcting for hangning mag in inches
const float da = 0.5;
int x1;
int x2;
int y1;
int y2;
//int z;
char zc;
int xt;
int yt;
int zt;
int t = 0;


//distance variables (in.)
const int squareSide = 1;
float dist;
//float gap;
const float L1 = 4.09;
const float L2 = 5.86;
float j1dist;
//int L3;
float pieceh;
int num_changes = 0;

//angle vars
//int bstart = 300  ; //to be determined experimentally
//int pos = bstart;
float angb = 90;
float angj1 = 0;
float angj2 = 0;
float fangb;
float fangj1;
float fangj1r;
float fangj2;
int pos;
//final draft of code aims to translate chess notation
//x will be position data
//
float PWMbe4 = map(angbe4,0,180,SERVOMIN0,SERVOMAX0);
float PWMj1e4 = map(angj1e4,90,180,SERVOMIN1,SERVOMAX1);
float PWMj2e4 = map(angj2e4,90,180,SERVOMIN2,SERVOMAX2);

float PWMbe2 = map(angbe2,0,180,SERVOMIN0,SERVOMAX0);
float PWMj1e2 = map(angj1e2,90,180,SERVOMIN1,SERVOMAX1);
float PWMj2e2 = map(angj2e2,90,180,SERVOMIN2,SERVOMAX2);

float PWMb;
float PWMj1;
float PWMj2;
float PWMbf;
float PWMj1f;
float PWMj2f;
typedef struct Move {
    char origin[2];
    char destination[2];
    int origin_col_num;
    int destination_col_num;
}move;

move recent_move;

typedef struct Hall {
    char square[2];
    int pin_number;
    int state;
}hall;

hall *hall_list;
char *buffer;

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();


int *return_hall_array(int n) {
    /*
    Description:
    Function to dynamically allocate memory for an array of size n.
    ----------------
    Input:
        int n: number of elements to allocate to array
    ----------------
    Output:
        int* temp: pointer to array
    */

   int *temp = malloc(sizeof(Hall) * n);
   return temp;
}


char letter_to_num(char letter) {
    /*
    Description:
    Function to change a number 0-7 into the corresponding 
    chess board column number a-h.
    ----------------
    Input:
        int num: column in number form
    ----------------
    Output:
        char temp: column in letter form to be used outside of function
    */
    int temp;
    switch(letter){
        case 'a':
            temp = 0;
            break;
        case 'b':
            temp = 1;
            break;
        case 'c':
            temp = 2;
            break;
        case 'd':
            temp = 3;
            break;
        case 'e':
            temp = 4;
            break;
        case 'f':
            temp = 5;
            break;
        case 'g':
            temp = 6;
            break;
        case 'h':
            temp = 7;
            break;
    }
    return temp;
}


void pieceheight(char c){

    switch(c) {
        case 'p':
            pieceh = 1.0;
            break;
        case 'b':
            pieceh = 1.206;
            break;
        case 'n':
            pieceh = 1.0;
            break;
        case 'r':
            pieceh = 1.373;
            break;
        case 'q':
            pieceh = 1.634;
            break;
        case 'k':
            pieceh = 1.664;
            break;
    }
}


void calcAng(int x, int y,char c){
  dist = sqrt(sq(x)+sq(y));
  pieceheight(c);
  j1dist = sqrt(sq(dist)+sq(h-pieceh));
  //map(90, 0, 180, SERVOMIN0, SERVOMAX0);
  if(y > 0){
    fangb = 90.0 - atan(y/x)*(180.0/M_PI);
  }
  else if(y< 0){
    fangb =  90.0 + atan(y/abs(x))*(180/M_PI);
  }
  fangj1 = acos((sq(L1)+sq(j1dist)-sq(L2))/(2*L1*j1dist))*(180/M_PI);
  fangj1r = atan(dist/(h-pieceh))*(180/M_PI);
  fangj1 += fangj1r;
  fangj2 = acos((sq(L1)+sq(L2)-sq(j1dist))/(2*L1*L2))*(180/M_PI);
}


void StartPos(){
  pwm.setPWM(0,0,288); //higher is more right from support perspect.
  pwm.setPWM(1,0,88); // higher  is lower
  pwm.setPWM(2,0,220);  
}


void transcoords(int xa, int ya){
  //yt = ya - 3.5;
  //xt = xa + 0.5;
  yt = ya - 4.5;
  xt = xa+0,5;
}


char *checkSerial() {
    for(int i = 0; i < 5; i++) {
        if(Serial.available()) {
            char ch = Serial.read();
            if(ch > 0) {
                buffer[i] = ch;
            }
            int flag = 1;
        }
    }
    if(flag == 1) {
        return buffer;
    }
    else:
        
}


void updateHalls() {
    /*
    Description:
    Function to iterate through all hall sensors and update
    their states if necessary (if previous state doesn't match
    current state). Sends move made by OTB player to python 
    script.
    ----------------
    Input:
        NOTHING
    ----------------
    Output:
        No formal output, updates hall_list.
    */
    for(int i = 0; i < num_hall; i++) {
        int temp = digitalRead(hall_list[i].pin_number);
        if(hall_list[i].state == temp){continue;}

        else {
            hall_list[i].state = temp;
            num_changes++;

            switch(num_changes) {
                case 1:
                    recent_move.origin = hall_list[i].square;
                    recent_move.origin_col_num = letter_to_num(recent_move.origin[0]);
                    break;
                    
                case 2:
                    recent_move.destination = hall_list[i].square;
                    recent_move.destination_col_num = letter_to_num(recent_move.destination_col);

                    Serial.print(recent_move.origin);
                    Serial.print(" ");
                    Serial.print(recent_move.destination);
                    Serial.print("\n");
                    delay(500);

                    numChanges = 0;
                    break;
            }
        }
    }
}


void setup() {
    Serial.begin(9600);

    pwm.begin();
    pwm.setOscillatorFrequency(27000000);
    pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

    hall_list = returnArray(num_hall);
    
    hall_list[0].square = "e2";
    hall_list[1].square = "e4";
    hall_list[2].square = "e5";
    hall_list[3].square = "e7";

    int starting_pin = 32;

    for(int i = 0; i < num_hall; i++) {
        hall_list[i].pin_number = starting_pin + i;
        pinMode(hall_list[i].pin_number, INPUT_PULLUP);

        hall_list[i].state = digitalRead(hall_list[i].pin_number);
    }

    pinMode(magEn, OUTPUT);
    pinMode(input1a, OUTPUT);
    pinMode(input2a, OUTPUT);
    digitalWrite(input1a, HIGH);
    digitalWrite(input2a, LOW);
    delay(10);
}


void loop() {
    StartPos();
    updateHalls();

    StartPos();
    delay(1000);
    //e2->e4
  
    while(testflag){
        t = 0;
        while(PWMj1<PWMj1e2){
        pwm.setPWM(1,0,88 + t*(PWMj1e2/20));
        pwm.setPWM(2,0,220 + t*(PWMj2e2/20));
        PWMj1 = t*(PWMj1e2/20);
        PWMj2 = t*(PWMj2e2/20);
        t++;
        delay(20);
        }
        if(PWMj1 < PWMj1e2 || PWMj2 < PWMj2e2){
        pwm.setPWM(1,0,PWMj1e2);
        pwm.setPWM(2,0,PWMj2e2);
        }
        analogWrite(magEn, 255);
        testflag = 0;
    }

    delay(1000)
    StartPos();
    testflag = 1;
    while(testflag){
        t = 0;
        while(PWMj1<PWMj1e4){
        pwm.setPWM(1,0,88 + t*(PWMj1e4/20));
        pwm.setPWM(2,0,220 + t*(PWMj2e4/20));
        PWMj1 = t*(PWMj1e4/20);
        PWMj2 = t*(PWMj2e4/20);
        t++;
        delay(20);
        }
        if(PWMj1 < PWMj1e4 || PWMj2 < PWMj2e4){
        pwm.setPWM(1,0,PWMj1e4);
        pwm.setPWM(2,0,PWMj2e4);
        }
        analogWrite(magEn, 0);
        testflag = 0;
    }

    free(hall_list);

}