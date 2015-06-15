/*
Coded by Marjan Olesch
Sketch from Insctructables.com
Open source - do what you want with this code!
*/
#include <Servo.h>


int value = 0; // set values you need to zero
//int value1=0,value2=0,value3=0,value4 =0;
int arm_key = 328; // Set this value to value <700 to indicate motor is armed
boolean resp = false;

Servo firstESC, secondESC ,thirdESC , fourthESC; //Create as much as Servoobject you want. You can controll 2 or more Servos at the same time

void setup() {

  firstESC.attach(3);  // attached to pin 9 I just do this with 1 Servo
  secondESC.attach(5);
  thirdESC.attach(9);
  fourthESC.attach(11);
  Serial.begin(9600);    // start serial at 9600 baud

}

void loop(){
  if(!resp){
    resp = arm();
  }
  else runMotor();
  
}

boolean arm() {

//First connect your ESC WITHOUT Arming. Then Open Serial and follo Instructions
 
  firstESC.writeMicroseconds(value);
  secondESC.writeMicroseconds(value);
  thirdESC.writeMicroseconds(value);
  fourthESC.writeMicroseconds(value);
 
  if(Serial.available()){
    value = Serial.parseInt();    // Parse an Integer from Serial
    if(value==arm_key)
    return true;
  }
  return false;
}

void runMotor(){
    servoWrite(1800,0,1800,00);
}

void servoWrite(int value1 , int value2, int value3, int value4){
  firstESC.writeMicroseconds(value1);
  secondESC.writeMicroseconds(value2);
  thirdESC.writeMicroseconds(value3);
  fourthESC.writeMicroseconds(value4);
}
