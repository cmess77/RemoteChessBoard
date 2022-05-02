const int num_bytes = 18;
const byte start_byte = 0x00;

byte buffer[num_bytes];


void checkSerial() {
    if(Serial.available()) {
        Serial.print("I received: ");
        char ch = Serial.read();
        if(ch > 0) {
            Serial.print(ch);
        }
    }
}


void setup() {
    Serial.begin(9600);
}


void loop() {

    Serial.print("e7 e5\n");
    delay(5000);
    Serial.print("d7 d5\n");
    delay(5000);
    
}