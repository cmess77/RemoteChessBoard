/* 
Black Termination: e2
Blue Termination: e4
Purple Termination: e5
Orange Termination: e7
*/

const int hall_pins[4] = {32, 33, 34, 35};

const int input_1a = 24;
const int input_2a = 23;
const int input_12EN = 22;

void setup() {
  pinMode(input_1a, OUTPUT);
  pinMode(input_2a, OUTPUT);
  pinMode(input_12EN, OUTPUT);

  digitalWrite(input_1a, HIGH);
  digitalWrite(input_2a, LOW);

  for(int i = 0; i < 4; i++) {
    pinMode(hall_pins[i], INPUT_PULLUP);
  }
  
    Serial.begin(9600);
}


void loop() {
  analogWrite(input_12EN, 255);

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
