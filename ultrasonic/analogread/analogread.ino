/* Define pins for HC-SR04 ultrasonic sensor */
 
#define echoPin A1 // Echo Pin = Analog Pin 0
#define trigPin A0 // Trigger Pin = Analog Pin 1
 
 
long duration; // Duration used to calculate distance
long HR_dist=0; // Calculated Distance
int max_dist=30;
int min_dist = 0;
 
int minimumRange=5; //Minimum Sonar range
int maximumRange=200; //Maximum Sonar Range

int last = 0;
int current = 0;

//For motor control
int p1 = 3 , p2 = 5;
int a = 7 , b=9 , c=11 , d=13;

//Set speed and sensitivity for Differential controller
int sensitivity = 50;
int speed=50;

 
/*--------------------SETUP()------------------------*/
void setup() {
 //Begin Serial communication using a 9600 baud rate
 Serial.begin (9600);
 
 //Setup the trigger and Echo pins of the HC-SR04 sensor
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 //int last = getDistance();
 
 //Setup pins for motor controller
 pinMode(p1 , OUTPUT);
  pinMode(p2 , OUTPUT);
  pinMode(a , OUTPUT);
  pinMode(b , OUTPUT);
  pinMode(c , OUTPUT);
  pinMode(d , OUTPUT);
  digitalWrite(a , HIGH);
  digitalWrite(b , LOW);
  digitalWrite(c , HIGH);
  digitalWrite(d , LOW);
 
}
 
/*----------------------LOOP()--------------------------*/
void loop() {
  
  /* Removed hashed out lines to enforce differential controller */
  
  
 int current = getDistance();
 //int diff = ultracontroller(last , current);
 Serial.println(current/*diff*/);
 //last=current;
 speed = map(current , min_dist , max_dist , 0 , 255);
 analogWrite(p1 , speed);
 analogWrite(p2 , speed);
 //speed+=diff;
 
}
 
/*--------------------getDistance() FUNCTION ---------------*/
int getDistance(){ 
 
 /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 HR_dist = duration/58.2;
 return HR_dist;
}

// Differential Controller
int ultracontroller(int l, int c){
  return sensitivity*(c-l);
}



