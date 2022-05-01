/* 
Black Termination: e7
Blue Termination: e5
Purple Termination: e4
Orange Termination: e2
*/

const int hall_pins[4] = {7, 6, 5, 4};


void setup() {

  for(int i = 0; i < 4; i++) {
    pinMode(hall_pins[i], INPUT_PULLUP);
  }
  
    Serial.begin(9600);
}


void loop() {

  for(int i = 0; i < 4; i++) {
    if(digitalRead(hall_pins[i]) == LOW) {
        Serial.print("1 ");
    }
    
    else if(digitalRead(hall_pins[i]) == HIGH) {
        Serial.print("0 ");
    }
  }
  Serial.println("");
  delay(500);
}
