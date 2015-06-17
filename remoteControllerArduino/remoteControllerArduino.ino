

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

//Integers to store motor velocities and properties
int va=0;
int vb=0;
int vc=0;
int vd=0;
int vr=0;
int ve=0;
int vl=0;

//Define mean values
int rudderMean=0;
int elevatorMean = 0;
int aileronMean = 0;

//Define error in reading
int eRudder = 40;
int eElevator = 60;
int eAileron = 60;
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
  
  #ifdef DEBUG
  //delay(400);
  Serial.println("--------------------");
  #endif
}

void arm() {

  //First connect your ESC WITHOUT Arming
  
  //Set an initial delay of 3 seconds
  delay(3000);
  
  //Throttle full
  va=vb=vc=vd=2000;
  servoWrite();
  
  delay(1500); //This delay should be less than 2 seconds
  
  //Throttle min
  va=vb=vc=vd=700;
  servoWrite();
  
  delay(3000); //Delay of 3 seconds before motor runs
}

void runMotor(){
  // Control for Throttle
  if(!checkRudder() && !checkElevator() && !checkAileron()){
  throttleController();
  }
  //Control for Rudder
  rudderController();
  //Control for Elevator
  elevatorController();
  //Control for Aileron
  aileronController();
  servoWrite();
}


//Controller methods for RC Functions
void throttleController(){
    int duration = pulseIn(throttle, HIGH);
    int value = map( duration , 1375, 2525, 700 , 1800);
    #ifdef DEBUG
    Serial.print("Throttle=");
    Serial.println(value);
    #endif
    
    va=vb=vc=vd=value;
   //Automatic motor control code goes here
}

void rudderController(){
  int duration = pulseIn(rudder, HIGH);
  int value = map(duration, 1360 , 2520 , -rudderSen , rudderSen);
  #ifdef DEBUG
  Serial.print("Rudder=");
  Serial.println(value);
  #endif
  
  vr=value;
}

void elevatorController(){
   int duration = pulseIn(elevator, HIGH);
  int value = map(duration, 1400 , 2485 , -elevatorSen , elevatorSen);
  #ifdef DEBUG
  Serial.print("Elevator=");
  Serial.println(value);
  #endif
  ve=value;
  
}

void aileronController(){
   int duration = pulseIn(aileron, HIGH);
  int value = map(duration, 1360 , 2520 , -aileronSen , aileronSen);
  #ifdef DEBUG
  Serial.print("Aileron=");
  Serial.println(value);
  #endif
  vl=value;
}




//This function writes different/same values to the servo connected to the motors
void servoWrite(){
  firstESC.writeMicroseconds(va);
  secondESC.writeMicroseconds(vb);
  thirdESC.writeMicroseconds(vc);
  fourthESC.writeMicroseconds(vd);
}

//Check if sticks are active
boolean checkRudder(){
  if(vr>(rudderMean+eRudder)||vr<(rudderMean-eRudder))
  return true;
  else return false;
}

boolean checkElevator(){
  if(ve>(elevatorMean+eElevator)||ve<(elevatorMean-eElevator))
  return true;
  else return false;
}

boolean checkAileron(){
  if(vl>(aileronMean+eAileron)||vl<(aileronMean-eAileron))
  return true;
  else return false;
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
