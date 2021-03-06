

/*
Coded by Avishek De
Open source - do what you want with this code!
*/




/*
MOTOR MAP

3(A)...................5(B)
.
.
.
.
.
.
.
11(D).................9(C)
*/




#include <Servo.h>
#include <EnableInterrupt.h>


Servo firstESC, secondESC ,thirdESC , fourthESC; //Include as many servo objects as are the number of motors

//Define receiver channels
#define throttle A0
#define rudder A1
#define elevator A2
#define aileron A3

//If you want to debug
#define DEBUG

//Integers for PWM Calculation
volatile int prev_timeT;
volatile int new_timeT;
volatile int diffT;
volatile int prev_timeR;
volatile int new_timeR;
volatile int diffR;
volatile int prev_timeE;
volatile int new_timeE;
volatile int diffE;
volatile int prev_timeA;
volatile int new_timeA;
volatile int diffA;

//Integers to store motor velocities and properties
int va=0;
int vb=0;
int vc=0;
int vd=0;
int vr=0;
int ve=0;
int vl=0;
int vt=0;

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
  
  //Enable Interrupts
  enableInterrupt(throttle,enThrottleRise,RISING);
  enableInterrupt(rudder,enRudderRise,RISING);
  enableInterrupt(elevator,enElevatorRise,RISING);
  enableInterrupt(aileron,enAileronRise,RISING);
}

void loop(){
  //Run the motor
  runMotor();  
  
  #ifdef DEBUG
  displayVelocity();
  Serial.println("----------------");
  #endif
}

void arm() {
  
  #ifdef DEBUG
  Serial.println("Entering Arm");
  #endif
  
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
  #ifdef DEBUG
  Serial.println("Exiting Arm");
  #endif
  
}

void runMotor(){
  // Control for Throttle
  //if(!checkRudder() && !checkElevator() && !checkAileron()){
  throttleController();
  //}
  //Control for Rudder
  if(checkRudder()) rudderController();
  //Control for Elevator
  if(checkElevator()) elevatorController();
  //Control for Aileron
  if(checkAileron()) aileronController();
  servoWrite();
}


//Controller methods for RC Functions
void throttleController(){
    int duration = new_timeT-prev_timeT;
    int value = map( duration , 1375, 2525, 700 , 1800);
    
    #ifdef DEBUG
    Serial.print("Throttle=");
    Serial.println(value);
    #endif
    
    va=vb=vc=vd=value;
  }

void rudderController(){
  #ifdef DEBUG
  Serial.print("Rudder=");
  Serial.println(vr);
  #endif

  vb=vb+vr;
  vd=vd+vr;
  va=va-vr;
  vc=va-vr;
  
}

void elevatorController(){
  #ifdef DEBUG
  Serial.print("Elevator=");
  Serial.println(ve);
  #endif
  
  vc=vc+ve;
  vd=vd+ve;
  va=va-ve;
  vb=vb-ve;
  
}

void aileronController(){
   
  #ifdef DEBUG
  Serial.print("Aileron=");
  Serial.println(vl);
  #endif
  
  vb=vb+vl;
  vc=vc+vl;
  va=va-vl;
  vd=vd-vl;
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
  int duration = diffR;
  int value = map(duration, 1360 , 2520 , -rudderSen , rudderSen);
  vr=value;
  if(vr>(rudderMean+eRudder)||vr<(rudderMean-eRudder))
  return true;
  else return false;
}

boolean checkElevator(){
  int duration = diffE;
  int value = map(duration, 1400 , 2485 , -elevatorSen , elevatorSen);
  ve=value;
  if(ve>(elevatorMean+eElevator)||ve<(elevatorMean-eElevator))
  return true;
  else return false;
}

boolean checkAileron(){
  int duration = diffA;
  int value = map(duration, 1360 , 2520 , -aileronSen , aileronSen);
  vl=value;
  if(vl>(aileronMean+eAileron)||vl<(aileronMean-eAileron))
  return true;
  else return false;
}

//Display velocity values
void displayVelocity(){
  Serial.print("Velocity A ");
  Serial.println(va);
  Serial.print("Velocity B ");
  Serial.println(vb);
  Serial.print("Velocity C ");
  Serial.println(vc);
  Serial.print("Velocity D ");
  Serial.println(vd);
}


//Interrupt Functions to calculate PWM Signals
void enThrottleRise(){
  prev_timeT = micros();
  enableInterrupt(throttle,enThrottleFall,FALLING);
}

void enThrottleFall(){
  new_timeT = micros();
  diffT = new_timeT - prev_timeT;
  #ifdef DEBUG
  Serial.print(" diffT = ");
  Serial.println(diffT);
  #endif
  enableInterrupt(throttle,enThrottleRise,RISING);
}

void enRudderRise(){
  prev_timeR = micros();
  enableInterrupt(rudder,enThrottleFall,FALLING);
}

void enRudderFall(){
  new_timeR = micros();
  diffR = new_timeR - prev_timeR;
  #ifdef DEBUG
  Serial.print(" diffR = ");
  Serial.println(diffR);
  #endif
  enableInterrupt(rudder,enRudderRise,RISING);
}

void enElevatorRise(){
  prev_timeE = micros();
  enableInterrupt(elevator,enElevatorFall,FALLING);
}

void enElevatorFall(){
  new_timeE = micros();
  diffE = new_timeE - prev_timeE;
  #ifdef DEBUG
  Serial.print(" diffE = ");
  Serial.println(diffE);
  #endif
  enableInterrupt(elevator,enElevatorRise,RISING);
}

void enAileronRise(){
  prev_timeA = micros();
  enableInterrupt(aileron,enAileronFall,FALLING);
}

void enAileronFall(){
  new_timeA = micros();
  diffA = new_timeA - prev_timeA;
  #ifdef DEBUG
  Serial.print(" diffA = ");
  Serial.println(diffA);
  #endif
  enableInterrupt(aileron,enAileronRise,RISING);
}


//If you want to use Interrupt to calculate PWM (old method) (now replaced by EnableInterrupt Function)
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
