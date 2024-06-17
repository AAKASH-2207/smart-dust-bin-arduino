/*
Aakash Sharma
Code for Creating a Smart dustbin using IR sensor and ultrasonic sensor
*/
#include <Servo.h>
int IRsensor = 9;
const int led_red = 5 ; //when bin in filled
const int led_green = 3 ; // when bin in empty
Servo lid_open;
int trig = 10; //used to receive controlling signals from the Arduino board. This is the triggering input pin of the sensor
int echo = 11; //used for sending signals to the Arduino board where the Arduino calculates the pulse duration to know the distance
long timetaken; 
float filterArray[20]; // defining array to store multiple data sample received from the sensor
float distance; // stores the distance from ultrasonic sensor
float ultrasonicMeasure();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(IRsensor, INPUT);
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  lid_open.attach(6);
  pinMode(trig, OUTPUT); // Sets the trig as an OUTPUT
  pinMode(echo, INPUT); // Sets the echo as an INPUT

}

void loop() {
  // code for servo open and close
  int sensor_status = digitalRead(IRsensor);
  if(sensor_status == 1){
    lid_open.write(120);
  }else{
    lid_open.write(0);
  }
  delay(10);
  //first code end
  //code for ultrasonic distance finder
    digitalWrite(trig, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid 
                          // collision in serial monitor 
 
    digitalWrite(trig, HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(5); // keep the trigger "ON" for 10 ms to generate
                           // pulse for 10 ms.
 
    digitalWrite(trig, LOW); // Turn off the pulse trigger to stop
                             // pulse generation
    timetaken = pulseIn(echo, HIGH);
    distance = timetaken * 0.0344 / 2; // Expression to calculate
                                 // distance using time
    delay(10);
    if(distance <=23 && distance > 11){
      analogWrite(led_green, 255);
      analogWrite(led_red, 0);
    }else if(distance <=11 && distance >= 5){
      analogWrite(led_green, 255);
      analogWrite(led_red, 255);
    }else if(distance <5){
      analogWrite(led_red,255);
      analogWrite(led_green, 0);
    }
}
