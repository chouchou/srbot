#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define L_TRIPIN 7
#define L_ECHPIN 6
#define R_TRIPIN 5
#define R_ECHPIN 4
#define M_TRIPIN 3
#define M_ECHPIN 2

#define LL_IR 13 // LL = Left Left
#define LR_IR 12 // LR = Left Rgiht etc.
#define ML_IR 11
#define MR_IR 10
#define RL_IR 9
#define RR_IR 8

unsigned long interval1 = 1000000; // interval time in us;
unsigned long controlLoop = 100000; // interval time in us;
unsigned long lastRun1 = 0;
unsigned long lastCtrlLoop = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
  pinMode(LL_IR, INPUT);
  pinMode(LR_IR, INPUT);
  pinMode(ML_IR, INPUT);
  pinMode(MR_IR, INPUT);
  pinMode(RL_IR, INPUT);
  pinMode(RR_IR, INPUT);

}

void loop() {
  if ((micros() - lastRun1) > interval1) {
    lastRun1 = micros();
    Serial.print("LL: ");
    Serial.print(digitalRead(LL_IR));
    Serial.print(", LR: ");
    Serial.print(digitalRead(LR_IR));
    Serial.print(", ML: ");
    Serial.print(digitalRead(ML_IR));
    Serial.print(", MR: ");
    Serial.print(digitalRead(MR_IR));
    Serial.print(", RL: ");
    Serial.print(digitalRead(RL_IR));
    Serial.print(", RR: ");
    Serial.println(digitalRead(RR_IR));

  } else if ((micros() - lastCtrlLoop) > controlLoop) {
    lastCtrlLoop = micros();

  }
}

int getDistance(String sensor) {
  uint32_t duration; // duration of the round trip
  uint32_t cm;        // distance of the obstacle
  int trigPin;
  int echPin;
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  if (sensor == "left") {
    trigPin = L_TRIPIN;
    echPin = L_ECHPIN;
  } else if (sensor == "right") {
    trigPin = R_TRIPIN;
    echPin = R_ECHPIN;
  } else if (sensor == "center") {
    trigPin = M_TRIPIN;
    echPin = M_ECHPIN;
  }
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  // Start trigger signal
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echPin, INPUT);
  duration = pulseIn(echPin, HIGH);
  // convert the time into a distance
  cm = (uint32_t)((duration << 4) + duration) / 1000.0; // cm = 17 * duration/1000
  return cm;
}
