#include <Arduino.h>
#include <stdio.h>

#define selectorPinC 16
#define selectorPinB 17
#define selectorPinA 18

typedef struct Multiplexer {
    int pinNumber;
}mux;

mux mux1, mux2, mux3, mux4, mux5, mux6, mux7, mux8;

mux mux_list[8] = {mux1, mux2, mux3, mux4, mux5, mux6, mux7, mux8};

typedef struct HallSensor {
    int hallState;
}hall;

hall hall_1, hall_2, hall_3, hall_4, hall_5, hall_6, hall_7, hall_8, hall_9, hall_10, hall_11, hall_12, hall_13, hall_14, 
hall_15, hall_16, hall_17, hall_18, hall_19, hall_20, hall_21, hall_22, hall_23, hall_24, hall_25, hall_26, hall_27, hall_28, 
hall_29, hall_30, hall_31, hall_32, hall_33, hall_34, hall_35, hall_36, hall_37, hall_38, hall_39, hall_40, hall_41, hall_42, 
hall_43, hall_44, hall_45, hall_46, hall_47, hall_48, hall_49, hall_50, hall_51, hall_52, hall_53, hall_54, hall_55, hall_56, 
hall_57, hall_58, hall_59, hall_60, hall_61, hall_62, hall_63, hall_64;

hall hall_list[8][8] = {
    {hall_1, hall_2, hall_3, hall_4, hall_5, hall_6, hall_7, hall_8},
    {hall_9, hall_10, hall_11, hall_12, hall_13, hall_14, hall_15, hall_16},
    {hall_17, hall_18, hall_19, hall_20, hall_21, hall_22, hall_23, hall_24},
    {hall_25, hall_26, hall_27, hall_28, hall_29, hall_30, hall_31, hall_32},
    {hall_33, hall_34, hall_35, hall_36, hall_37, hall_38, hall_39, hall_40},
    {hall_41, hall_42, hall_43, hall_44, hall_45, hall_46, hall_47, hall_48},
    {hall_49, hall_50, hall_51, hall_52, hall_53, hall_54, hall_55, hall_56},
    {hall_57, hall_58, hall_59, hall_60, hall_61, hall_62, hall_63, hall_64}
};

int selector_binaries[8][3] = {
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},
    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};


void updateHalls(hall (*sensorList)[8][8]) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            digitalWrite(selectorPinC, selector_binaries[j][0]);
            digitalWrite(selectorPinB, selector_binaries[j][1]);
            digitalWrite(selectorPinA, selector_binaries[j][2]);

            //(*sensorList)[i][j].hallState = digitalRead(mux_list[i].pinNumber);
            (*sensorList)[i][j].hallState = 1;
        }
    }
}


void setup() {
    mux1.pinNumber = 8;
    mux2.pinNumber = 9;
    mux3.pinNumber = 10;
    mux4.pinNumber = 11;
    mux5.pinNumber = 12;
    mux6.pinNumber = 13;
    mux7.pinNumber = 14;
    mux8.pinNumber = 15;

    for(int i = 0; i < 8; i++) {
        pinMode(mux_list[i].pinNumber, INPUT);
    }

    pinMode(selectorPinA, OUTPUT);
    pinMode(selectorPinB, OUTPUT);
    pinMode(selectorPinC, OUTPUT);

    Serial.begin(9600);

    //updateHalls(&hall_list);

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            hall_list[i][j].hallState = 0;
        }
    }
}


int main(void) {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            hall_list[i][j].hallState = 0;
        }
    }

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%n ", &hall_list[i][j].hallState);
        }
        printf("\n");
    }

    updateHalls(&hall_list);

    printf("Printing updated table.\n");
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            printf("%n ", &hall_list[i][j].hallState);
        }
        printf("\n");
    }
return 0;
}