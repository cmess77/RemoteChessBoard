#include <Arduino.h>

const int hall_pin = 37;
const int led_pin = 25;

void setup() {
    pinMode(hall_pin, INPUT_PULLUP);
    pinMode(led_pin, OUTPUT);

    Serial.begin(9600);
}


void loop() {

    if(digitalRead(hall_pin) == LOW) {
        digitalWrite(led_pin, HIGH);
        Serial.println("MAGNETIC FIELD DETECTED");
    }
    
    else if(digitalRead(hall_pin) == HIGH) {
        digitalWrite(led_pin, LOW);
        Serial.println("MAGNETIC FIELD NOT DETECTED.");
    }



}
