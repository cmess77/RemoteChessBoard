#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

const int SERVOMIN0 = 108;
const int SERVOMAX0 = 469;
const int SERVOMIN1 = 88; // 180 degrees
const int SERVOMAX1 = 268; // 90 degrees
const int SERVOMIN2 = 65;
const int SERVOMAX2 = 278;
const int SERVO_FREQ = 50; // Analog servos run at ~50 Hz updates


void setup() {

  pwm.begin();

  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates

  delay(10);
}


void loop() {
  pwm.setPWM(0,0,map(90, 0, 180, SERVOMIN0, SERVOMAX0));
  pwm.setPWM(1,0,150);
  pwm.setPWM(2,0,SERVOMAX2);

}
