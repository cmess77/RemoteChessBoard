const int input_1a = 7;
const int input_2a = 8;
const int input_12EN = 6;

void setup() {
    pinMode(input_1a, OUTPUT);
    pinMode(input_2a, OUTPUT);
    pinMode(input_12EN, OUTPUT);

    Serial.begin(9600);
}


void loop() {
    analogWrite(input_12EN, 255);
    digitalWrite(input_1a, LOW);
    digitalWrite(input_2a, HIGH);
    Serial.println("Magnet should be on.");
}
