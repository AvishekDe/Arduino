/*
Coded by Avishek De
Open source - do what you want with this code!
*/
#include <Servo.h>


Servo firstESC, secondESC ,thirdESC , fourthESC; //Include as many servo objects as are the number of motors

void setup() {
  
  //attach them to PWM pins of the Arduino Board
  firstESC.attach(3);  
  secondESC.attach(5);
  thirdESC.attach(9);
  fourthESC.attach(11);
  Serial.begin(9600);    // start serial at 9600 baud
  
  //Automatic Arm
  arm();

}

void loop(){
  //Run the motor
  runMotor();
  
}

void arm() {

  //First connect your ESC WITHOUT Arming
  
  //Set an initial delay of 3 seconds
  delay(3000);
  
  //Throttle full
  servoWrite(2000,2000,2000,2000);
  
  delay(1500); //This delay should be less than 2 seconds
  
  //Throttle min
  servoWrite(700,700,700,700);
  
  delay(3000); //Delay of 3 seconds before motor runs
}

void runMotor(){
   //Automatic motor control code goes here
    servoWrite(1800,0,1800,00);
}

//This function writes different/same values to the servo connected to the motors
void servoWrite(int value1 , int value2, int value3, int value4){
  firstESC.writeMicroseconds(value1);
  secondESC.writeMicroseconds(value2);
  thirdESC.writeMicroseconds(value3);
  fourthESC.writeMicroseconds(value4);
}
