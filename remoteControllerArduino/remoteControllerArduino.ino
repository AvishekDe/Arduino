

/*
Coded by Avishek De
Open source - do what you want with this code!
*/
#include <Servo.h>


Servo firstESC, secondESC ,thirdESC , fourthESC; //Include as many servo objects as are the number of motors

//Define receiver channels
#define throttle A0
#define rudder A1
#define elevator A2
#define aileron A3

//If you want to debug
#define DEBUG

//Integers for PWM Calculation
volatile int prev_time;
volatile int new_time;

//Define Sensitivities

int rudderSen = 300;
int elevatorSen = 300;
int aileronSen = 300;

void setup() {
  
  //attach them to PWM pins of the Arduino Board
  firstESC.attach(3);  
  secondESC.attach(5);
  thirdESC.attach(9);
  fourthESC.attach(11);
  Serial.begin(9600);    // start serial at 9600 baud
  pinMode(throttle , INPUT);
  pinMode(rudder, INPUT);
  pinMode(elevator, INPUT);
  pinMode(aileron, INPUT);
  
  //Automatic Arm
  arm();

}

void loop(){
  //Run the motor
  runMotor();  
  delay(400);
  #ifdef DEBUG
  Serial.println("--------------------");
  #endif
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
  // Control for Throttle
  throttleController();
  //Control for Rudder
  rudderController();
  //Control for Elevator
  elevatorController();
  //Control for Aileron
  aileronController();
}


//Controller methods for RC Functions
void throttleController(){
    int duration = pulseIn(throttle, HIGH);
    int value = map( duration , 1375, 2525, 700 , 1800);
    #ifdef DEBUG
    Serial.print("Throttle=");
    Serial.println(value);
    #endif
    
    
   //Automatic motor control code goes here
    servoWrite(value,value,value,value);
}

void rudderController(){
  int duration = pulseIn(rudder, HIGH);
  int value = map(duration, 1360 , 2520 , -rudderSen , rudderSen);
  #ifdef DEBUG
  Serial.print("Rudder=");
  Serial.println(value);
  #endif
  
}

void elevatorController(){
   int duration = pulseIn(elevator, HIGH);
  int value = map(duration, 1400 , 2485 , -elevatorSen , elevatorSen);
  #ifdef DEBUG
  Serial.print("Elevator=");
  Serial.println(value);
  #endif
  
  
}

void aileronController(){
   int duration = pulseIn(aileron, HIGH);
  int value = map(duration, 1360 , 2520 , -aileronSen , aileronSen);
  #ifdef DEBUG
  Serial.print("Aileron=");
  Serial.println(value);
  #endif
  
}




//This function writes different/same values to the servo connected to the motors
void servoWrite(int value1 , int value2, int value3, int value4){
  firstESC.writeMicroseconds(value1);
  secondESC.writeMicroseconds(value2);
  thirdESC.writeMicroseconds(value3);
  fourthESC.writeMicroseconds(value4);
}


//If you want to use Interrupt to calculate PWM
/*void startSignal(){
  latest_interrupted_pin=PCintPort::arduinoPin;
  prev_time = micros();
  PCintPort::attachInterrupt(latest_interrupted_pin, &stopSignal, FALLING);
}

void stopSignal(){
  latest_interrupted_pin=PCintPort::arduinoPin;
  new_time = micros();
  PCintPort::attachInterrupt(latest_interrupted_pin, &startSignal, RISING);
  Serial.print(new_time - prev_time);
  Serial.print(" at pin ");
  Serial.println(latest_interrupted_pin);
}*/
