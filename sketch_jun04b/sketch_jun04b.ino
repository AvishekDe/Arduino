//pin assignments
const int switchPin = 2; // switch input
const int motor1Pin = 12; // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 5; // H-bridge leg 2 (pin 7, 2A)
const int pwm = 9;
const int enablePin = 4; // H-bridge enable pin

void setup(){
  pinMode(switchPin, INPUT);
  //set all the other pins you✬re using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(pwm , OUTPUT);
  // set enablePin high so that motor can turn on:we do not need to repeat
  digitalWrite(enablePin, HIGH);
  // if the switch is high, motor will turn on one direction:
  if (digitalRead(switchPin) == HIGH) {
  digitalWrite(motor2Pin, HIGH); // set leg 2 of the H-bridge high
  digitalWrite(motor1Pin, LOW); // set leg 1 of the H-bridge low
  }
  // if the switch is low, motor will turn in the other direction:
  else {
  digitalWrite(motor1Pin, HIGH); // set leg 1 of the H-bridge high
  digitalWrite(motor2Pin, LOW); // set leg 2 of the H-bridge low
  }
 
}

void loop(){
  
  
  analogWrite(pwm , 255);
   digitalWrite(motor1Pin , HIGH);
  digitalWrite(motor2Pin , LOW);
  delay(5000);
  
  
  analogWrite(pwm , 255);
   digitalWrite(motor1Pin , LOW);
  digitalWrite(motor2Pin , HIGH);
  delay(5000);
 
  /*for(int i=50;i<=170;i+=5){
    analogWrite(pwm , i);
    delay(500);
  }
  delay(5000);
  for(int j=170;j>=50;j-=5){
    analogWrite(pwm, j);
    delay(500);
  }*/
}
