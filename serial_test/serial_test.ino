const int num_bytes = 18;
const byte start_byte = 0x00;

byte buffer[num_bytes];


void checkSerial() {
    if(Serial.available()) {
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
    // checkSerial();
    Serial.print("Hello from arduino.\n");
}