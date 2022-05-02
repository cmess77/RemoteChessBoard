/*
TODO

*/

#include <Arduino.h>
#include <stdio.h>
#include <stdlib.h>

const int num_hall = 4;

int num_changes = 0;

typedef struct Move {
    char origin[2];
    char destination[2];
    int origin_col_num;
    int destination_col_num;
}move;

move recent_move;

typedef struct Hall {
    char square[3];
    int pin_number;
    int state;
}hall;

hall *hall_list;


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

   int *temp = new hall(n);
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
        case 'f':
            temp = 7;
            break;
    }
    return temp;
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
        if(hall_list[i].state == temp){continue;};

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

                    numChanges = 0;
                    break;
            }
        }
    }
}


void setup() {
    Serial.begin(9600);

    hall_list = returnArray(num_hall);
    
    hall_list[0].square = "e7";
    hall_list[1].square = "e5";
    hall_list[2].square = "e4";
    hall_list[3].square = "e2";

    for(int i = 0; i < num_hall; i++) {
        hall_list[i].pin_number = starting_pin + i;
        pinMode(hall_list[i].pin_number, INPUT_PULLUP);

        hall_list[i].state = digitalRead(hall_list[i].pin_number);
    }

}


void loop() {
    updateHalls();
}