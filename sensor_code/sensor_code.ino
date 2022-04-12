/*
TODO

    IMPLEMENT INPUT FROM RASPBERRY PI
    TEST/TIME SENSOR CODE

*/

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

const int = SELECTOR_PIN_A 22;
const int = SELECTOR_PIN_B 23;
const int = SELECTOR_PIN_C 24;
const int = STARTING_MUX_PIN 25;

const int numMux = 8;
const int numHallPerMux = 8;
const int numHall = 64;

const int selectorBinaries[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};

int *hallList;
int *muxList;

int changes = 0;
int testFlag = 1;
int moveStart[2];
int moveEnd[2];
int numChanges = 0;

typedef struct Move {
    int start[2];
    int end[2];
    char startColumnLetter;
    char endColumnLetter;
}move;

move recentMove;


int *returnArray(int n) {
    /*
    Description:
    Function to dynamically allocate memory for an array of size 'n.' 
    ----------------
    Input:
        int n: number of elements to allocate to array
    ----------------
    Output:
        int* temp: pointer to array
    */

   int *temp = new int(n);
   return temp;
}


char numToLetter(int num) {
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
    char temp;
    switch(num){
        case 0:
            temp = 'a';
            break;
        case 1:
            temp = 'b';
            break;
        case 2:
            temp = 'c';
            break;
        case 3:
            temp = 'd';
            break;
        case 4:
            temp = 'e';
            break;
        case 5:
            temp = 'f';
            break;
        case 6:
            temp = 'g';
            break;
        case 7:
            temp = 'h';
            break;
    }
    return temp;
}


void updateHalls() {
    /*
    Description:
    Function to iterate through all hall sensors and update
    their states if necessary (if previous state doesn't match
    current state)
    ----------------
    Input:
        NOTHING
    ----------------
    Output:
        Technically nothing.
        hallList: not returned, but all values are updated via 
        reference to hallList
    */
    for(int i = 0; i < numMux; i++) {
        for(int j = 0; j < numHallPerMux; j++) {
            digitalWrite(SELECTOR_PIN_A, selectorBinaries[i][0]);
            digitalWrite(SELECTOR_PIN_B, selectorBinaries[i][1]);
            digitalWrite(SELECTOR_PIN_C, selectorBinaries[i][2]);

            // do nothing if the cell hasn't changed
            if(hallList[j + (i * 8)] == digitalRead(muxList[i]));

            else {
                hallList[j + (i * 8)] = digitalRead(muxList[i]);
                numChanges++;

                switch(numChanges) {
                    case 1:
                        recentMove.start[0] = j;
                        recentMove.start[1] = i;
                        recentMove.startColumnLetter = numToLetter(recentMove.start[0]);
                        break;
                        
                    case 2:
                        recentMove.end[0] = j;
                        recentMove.end[1] = i;
                        recentMove.endColumnLetter = numToLetter(recentMove.end[0]);

                        Serial.print(recentMove.startColumnLetter);
                        Serial.print(" ");
                        Serial.print(recentMove.start[1] + 1);
                        Serial.print(" ");
                        Serial.print(recentMove.endColumnLetter);
                        Serial.print(" ");
                        Serial.println(recentMove.end[1] + 1);
                        delay(1000);
                        break;
                    case 3:
                        numChanges = 0;
                        break;
                }
            }
        }
    }
}


void setup() {
    Serial.begin(9600);

    hallList = returnArray(numHall);
    muxList = returnArray(numMux);

    for(int i = 0; i < numMux; i++) {
        muxList[i] = STARTING_MUX_PIN + i;
    }

    for(int i = 0; i < numMux; i++) {
        pinMode(muxList[i], INPUT);
    }

    pinMode(SELECTOR_PIN_A, OUTPUT);
    pinMode(SELECTOR_PIN_B, OUTPUT);
    pinMode(SELECTOR_PIN_C, OUTPUT);


}


void loop() {
    // while(testFlag == 1) {

    //     for(int i = 0; i < numMux; i++) {
    //         printf("&d ", muxList[i]);
    //     }
    //     printf("\n");

    //     for(int i = 0; i < numHall; i++) {
    //         hallList[i] = 0;
    //     }

    //     for(int i = 0; i < numHall; i++) {
    //         printf("%d\n", hallList[i]);
    //     }

    //     for(int i = 0; i < numHall; i++) {
    //         hallList[i] = 1;
    //     }
    //     for(int i = 0; i < numHall; i++) {
    //         printf("%d\n", hallList[i]);
    //     }

    //     testFlag = 0;
    // }

    updateHalls();
}