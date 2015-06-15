/* Define pins for HC-SR04 ultrasonic sensor */
 
#define echoPin A0 // Echo Pin = Analog Pin 0
//#define trigPin A0 // Trigger Pin = Analog Pin 1
 
#define LEDPin 13 // Onboard LED
 
long duration; // Duration used to calculate distance
long HR_dist=0; // Calculated Distance
 
int minimumRange=5; //Minimum Sonar range
int maximumRange=200; //Maximum Sonar Range
 
/*--------------------SETUP()------------------------*/
void setup() {
 //Begin Serial communication using a 9600 baud rate
 Serial.begin (9600);
 
 //Setup the trigger and Echo pins of the HC-SR04 sensor
 //pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 //pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}
 
/*----------------------LOOP()--------------------------*/
/*void loop() {
 getDistance();
}*/
 
/*--------------------getDistance() FUNCTION ---------------*/
void loop(){ 
 
 /* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 /*digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 
 
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);*/
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 
 
 Serial.println(duration);
 delay(2000);
 
 
}
