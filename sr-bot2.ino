#include <Servo.h>

#define SERVO_RIGHT 6
#define SERVO_LEFT 5

#define ECHOPIN 12
#define TRIGPIN 13
#define IR_LEFT 0 //(ANALOG 0)
#define IR_RIGHT 1 //(ANALOG 1)

#define DA_SIZE 8

unsigned long interval1 = 1000000; // interval time in us;
unsigned long interval2 = 100000; // interval time in us;
unsigned long lastRun1 = 0;
unsigned long lastRun2 = 0;

int distPos = 0;
uint32_t distArray[DA_SIZE];
int leftIR =0;
int rightIR = 0;
Servo left;
Servo right;
bool whitereached=false;

void setup() {
  Serial.begin(9600); // USB Cable
  left.attach(SERVO_LEFT);
  right.attach(SERVO_RIGHT);
}
void loop() {
  left.write(0);
  right.write(255);
  if(!whitereached){
 driveStraight();   
    }
 
 Serial.println(whitereached);
  if(whitereached){
    turnright();
    
    }
  
  if ((micros() - lastRun1) > interval1) {
    lastRun1 = micros();
    displayDistance();
    leftIR = analogRead(IR_LEFT);     // read the input pin
    Serial.println(leftIR);
    rightIR = analogRead(IR_RIGHT);     // read the input pin
    Serial.println(rightIR);
  } else if ((micros() - lastRun2) > interval2) {
    lastRun2 = micros();
    measureDistance();

  }
}
void turnright(){
      right.attach(SERVO_RIGHT);
    left.attach(SERVO_LEFT);
  left.write(0);
  right.write(0);
leftIR = analogRead(IR_LEFT);     // read the input pin
    //Serial.println(leftIR);
    rightIR = analogRead(IR_RIGHT);     // read the input pin  
if(leftIR+rightIR>900){
  whitereached=false;
  return;
  }

  void driveStraight(){
  left.write(0);
  right.write(255);
  // Vitt är lågt
  // Svart är högt
    leftIR = analogRead(IR_LEFT);     // read the input pin
    Serial.println(leftIR);
    rightIR = analogRead(IR_RIGHT);     // read the input pin
    Serial.println(rightIR);
    if(leftIR+rightIR<100){
    right.detach();
    left.detach();
    whitereached=true;
    }
    if(leftIR+rightIR>200){
    right.attach(SERVO_RIGHT);
    left.attach(SERVO_LEFT);
    }
    if(rightIR<100){
      //left.write(255);
      left.detach();
 
      //Serial.println("right");
      }
      
      if(leftIR<100){
      right.detach();
     // right.write(0);
     // Serial.println("left");
      }
     
     if(leftIR+rightIR>900){
     left.attach(SERVO_LEFT);
    right.attach(SERVO_RIGHT);
    whitereached=false;
      left.write(0);
    right.write(255);
      }

  
  
  
  }


  







void measureDistance() {
  uint32_t duration; // duration of the round trip
  uint32_t cm;        // distance of the obstacle

  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  pinMode(TRIGPIN, OUTPUT);
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(3);

  // Start trigger signal

  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  pinMode(ECHOPIN, INPUT);
  duration = pulseIn(ECHOPIN, HIGH);

  // convert the time into a distance
  cm = (uint32_t)((duration << 4) + duration) / 1000.0; // cm = 17 * duration/1000
  ++distPos; //move to next position in array
  if (distPos == DA_SIZE) { //check if oversized
    distPos = 0; //reset
  }
  distArray[distPos] = cm; //assign value at next position
}

void displayDistance() {
  uint32_t temp = 0;
  for (int i = 0; i < DA_SIZE; i++) {
    //Serial.print("Value at position ");
    //Serial.print(i);
    //Serial.print(" is equal: ");
    //Serial.println(distArray[i],DEC);
    //Serial.print("The new sum is ");
    temp = temp + distArray[i];
    //Serial.println(temp);
  }
  temp = temp >> 3;
  //Serial.print("Dvidied by 8 should give average: ");
  Serial.print(temp, DEC);
  Serial.println(" cm");
}
