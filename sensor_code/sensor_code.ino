#include <Arduino.h> // to appease the VSCode gods
#include <stdio.h> // for testing purposes

// declaring pins for mux selector pins (hoping to share them between all 8, in parallel)
#define selectorPinC 16
#define selectorPinB 17
#define selectorPinA 18

/*
Hoping to find a way using pointers and malloc()/free() to improve the mux and hall
mess happening below. Currently working that. This is why it may look kind of
messy or inefficient. It's because it is both of those things, lol.
*/

// declaring variables for below array, with pin numbers assigned to them (output pin from mux)
int mux1 = 8, mux2 = 9, mux3 = 10, mux4 = 11, mux5 = 12, mux6 = 13, mux7 = 14, mux8 = 15;

// declaring array to iterate over later
int mux_list[8] = {mux1, mux2, mux3, mux4, mux5, mux6, mux7, mux8};

//declaring hall sensor variables, to keep track of their states (high or low)
int hall_1, hall_2, hall_3, hall_4, hall_5, hall_6, hall_7, hall_8, hall_9, hall_10, hall_11, hall_12, hall_13, hall_14, 
hall_15, hall_16, hall_17, hall_18, hall_19, hall_20, hall_21, hall_22, hall_23, hall_24, hall_25, hall_26, hall_27, hall_28, 
hall_29, hall_30, hall_31, hall_32, hall_33, hall_34, hall_35, hall_36, hall_37, hall_38, hall_39, hall_40, hall_41, hall_42, 
hall_43, hall_44, hall_45, hall_46, hall_47, hall_48, hall_49, hall_50, hall_51, hall_52, hall_53, hall_54, hall_55, hall_56, 
hall_57, hall_58, hall_59, hall_60, hall_61, hall_62, hall_63, hall_64;

// declaring array to iterate over later
int hall_list[8][8] = {
    {hall_1, hall_2, hall_3, hall_4, hall_5, hall_6, hall_7, hall_8},
    {hall_9, hall_10, hall_11, hall_12, hall_13, hall_14, hall_15, hall_16},
    {hall_17, hall_18, hall_19, hall_20, hall_21, hall_22, hall_23, hall_24},
    {hall_25, hall_26, hall_27, hall_28, hall_29, hall_30, hall_31, hall_32},
    {hall_33, hall_34, hall_35, hall_36, hall_37, hall_38, hall_39, hall_40},
    {hall_41, hall_42, hall_43, hall_44, hall_45, hall_46, hall_47, hall_48},
    {hall_49, hall_50, hall_51, hall_52, hall_53, hall_54, hall_55, hall_56},
    {hall_57, hall_58, hall_59, hall_60, hall_61, hall_62, hall_63, hall_64}
};

// array to store combinations of selector signals sent to mux
int selectorBinaries[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};

int test_flag = 1; // for testing, by definition lol


// function to update hall sensor states
void updateHalls(int (*sensorList)[8][8]) {
    // iterating through sensor array
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            /*
            writing the correct values to selector lines, pulling the values
            from the "selectorBinaries" array
            */
            digitalWrite(selectorPinC, selectorBinaries[j][0]);
            digitalWrite(selectorPinB, selectorBinaries[j][1]);
            digitalWrite(selectorPinA, selectorBinaries[j][2]);


            // if the existing state hasn't changed, don't change it
            if((*sensorList)[i][j] == digitalRead(mux_list[i])) {
                break;
            }

            // existing state is outdated, update it
            else {
                (*sensorList)[i][j] = digitalRead(mux_list[i]);
                // (*sensorList)[i][j] = 1; // for testing..
            }
        }
    }
}


void setup() {
    // setting pinModes for all mux (easier than longhand lol)
    for(int i = 0; i < 8; i++) {
        pinMode(mux_list[i], INPUT);
    }

    // setting pinModes for all selector pins
    pinMode(selectorPinA, OUTPUT);
    pinMode(selectorPinB, OUTPUT);
    pinMode(selectorPinC, OUTPUT);

    // beginning (you guessed it) Serial communication
    Serial.begin(9600);

<<<<<<< HEAD
    updateHalls(&hall_list);
=======
    //updateHalls(&hall_list)

    // for testing purposes
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            hall_list[i][j] = 0;
        }
    }
>>>>>>> 8661bb93f42f4fae62c3991c324d48edda2594ed
}


void loop() {
<<<<<<< HEAD
    updateHalls(&hall_list);
=======
    /*
    all code below is only for testing purposes; in practice, 
    this function will only include the line 
    "updateHalls(&hall_list);"
    */
    
    while(test_flag == 1) {
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                hall_list[i][j] = 0;
            }
        }

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                printf("%n ", &hall_list[i][j]);
            }
            printf("\n");
        }

        updateHalls(&hall_list);

        printf("Printing updated table.\n");

        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                printf("%n ", &hall_list[i][j]);
            }
            printf("\n");
        }

        test_flag = 0;
    }
>>>>>>> 8661bb93f42f4fae62c3991c324d48edda2594ed
}
