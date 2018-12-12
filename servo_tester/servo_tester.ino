#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//    +5v -> VCC (this is power for the BREAKOUT only, NOT the servo power!)
//    GND -> GND
//    Analog 4 -> SDA
//    Analog 5 -> SCL


#define BSL_MIN  120 // BS1 = Big servo (luxorparts)
#define BSL_MAX  460 // 
#define BSL_CH 4

#define BSR_MIN  120 // BS1 = Big servo (luxorparts)
#define BSR_MAX  460 // 
#define BSR_CH 5

#define SSRU_MIN  100 // SS1 = Small servo - check tape
#define SSRU_MAX  440 //
#define SSRU_CH 0

#define SSLD_MIN  100 // SS2 = Small servo - check tape
#define SSLD_MAX  440 //
#define SSLD_CH 1

#define SS3_MIN  105 // SS3 = Small servo - check tape
#define SS3_MAX  445 //
#define SS3_CH 2

#define SS4_MIN  110 // SS4 = Small servo - check tape
#define SS4_MAX  455 //
#define SS4_CH 3

boolean found = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Servo test");
  pinMode(2, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  pwm.begin();
  pwm.setPWMFreq(50);  // Analog servos run at ~60 Hz updates
  delay(10);
}


void loop() {
  if (digitalRead(2) == LOW) {

    digitalWrite(13, HIGH);
    if (!found) {
      closeArms();
      found = true;
    } else if (found) {
      openArms();
      found = false;
    }
    digitalWrite(13, LOW);
    delay(50);
  }
}

void closeArms() {
  digitalWrite(13, HIGH);
  for (int i = 0; i < 100; i++) {
    uint32_t pulselength1 = map(.6 * i, 0, 180, SSRU_MIN, SSRU_MAX);
    pwm.setPWM(SSRU_CH, 0, pulselength1);
    pwm.setPWM(SSLD_CH, 0, pulselength1);
    delay(5);
  }

}

void openArms() {
  uint32_t pulselength1 = map(0, 0, 180, SSRU_MIN, SSRU_MAX);
  pwm.setPWM(SSRU_CH, 0, pulselength1);
  pwm.setPWM(SSLD_CH, 0, pulselength1);
}

void liftLeft() {
  uint32_t pulselength = map(45, 0, 180, BSL_MIN, BSL_MAX);
  pwm.setPWM(BSL_CH, 0, pulselength);
  Serial.println(pulselength);
}
void lowerLeft() {
  uint32_t pulselength = map(180, 0, 180, BSL_MIN, BSL_MAX);
  pwm.setPWM(BSL_CH, 0, pulselength);
  Serial.println(pulselength);
}

void liftRight() {
  uint32_t pulselength = map(140, 0, 180, BSR_MIN, BSR_MAX);
  pwm.setPWM(BSR_CH, 0, pulselength);
  Serial.println(pulselength);
}
void lowerRight() {
  uint32_t pulselength = map(0, 0, 180, BSR_MIN, BSR_MAX);
  pwm.setPWM(BSR_CH, 0, pulselength);
  Serial.println(pulselength);
}




