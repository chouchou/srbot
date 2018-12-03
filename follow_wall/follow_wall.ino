#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define L_TRIPIN 7
#define L_ECHPIN 6
#define R_TRIPIN 5
#define R_ECHPIN 4

unsigned long interval1 = 1000000; // interval time in us;
unsigned long interval2 = 100000; // interval time in us;
unsigned long lastRun1 = 0;
unsigned long lastRun2 = 0;

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(4);

void setup() {
  Serial.begin(9600);
  AFMS.begin();  // create with the default frequency 1.6KHz
}

void loop() {
  if ((micros() - lastRun1) > interval1) {
    lastRun1 = micros();
    Serial.println(getDistance("left"));
    //rightMotor->run(BACKWARD);
    //rightMotor->setSpeed(100);

  } else if ((micros() - lastRun2) > interval2) {
    lastRun2 = micros();

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
  } else if(sensor =="right"){
    trigPin = R_TRIPIN;
    echPin = R_ECHPIN;
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
