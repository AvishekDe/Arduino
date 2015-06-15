#include <Servo.h>
 
Servo esc1 , esc2 , esc3, esc4;
int throttlePin = 0;
int rudderPin = 2;
 
void setup()
{
  Serial.begin(9600);
esc1.attach(5);
esc2.attach(6);
esc3.attach(9);
esc4.attach(10);
}
 
void loop()
{
int throttle = analogRead(throttlePin);
int rudder = analogRead(rudderPin);
Serial.println(throttle);
Serial.println(rudder);
Serial.println("----------------------------------------");
throttle = map(throttle, 0, 1023, 0, 179);
rudder = map(rudder , 0, 1023 , 41 , 150);
esc1.write(throttle);
esc2.write(rudder);
esc3.write(throttle);
esc4.write(rudder);
delay(2000);
}
