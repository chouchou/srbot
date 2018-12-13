//  veryBasic_SerialInSerialOut_001
//  Credits to - http://www.martyncurrey.com/hc-06-zg-b23090w-bluetooth-2-0-edr-modules/  
//
//  Uses hardware serial to talk to the host computer and Software Serial for communication with the bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  Arduino A0 (SS RX) - BT TX no need voltage divider 
//  Arduino A1 (SS TX) - BT RX through a voltage divider (5v to 3.3v)
//********************//
// Default PIN: 1234  //
//********************//
 
#include <SoftwareSerial.h>
SoftwareSerial BTserial(A0, A1); // RX, TX
 
char c=' ';
 
void setup() 
{
    Serial.begin(9600);
    Serial.print("Sketch:   ");   Serial.println(__FILE__);
    Serial.print("Uploaded: ");   Serial.println(__DATE__);
    Serial.println(" ");
 
    BTserial.begin(9600);  
    Serial.println("BTserial started at 9600");
    Serial.println(" ");
}
 
void loop()
{
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTserial.available())
    {
        c = BTserial.read();
        Serial.write(c);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if ( Serial.available() )
    {
        c = Serial.read();   
        BTserial.write(c);
    }
}
