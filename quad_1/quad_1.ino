/*
 Provide power to the rotors of a motor using PWM pins of ATMEGA
 
 */

int value = 0;
#define pwm 3

void setup()  { 
  int r1 = 5, r2 = 6, b1 = 10, b2 = 11, l1 = A3, l2 = A2, l3 = A1, l4 = A0;
  pinMode(pwm, OUTPUT);
  //digitalWrite(5 , HIGH);
  digitalWrite(6 , HIGH);
  digitalWrite(10 , HIGH);
  digitalWrite(11 , HIGH);
  // nothing happens in setup
} 

void loop()  
{   
   for(int fadeValue = 150 ; fadeValue <= 255; fadeValue +=10) 
   { 
     setVoltage(fadeValue);
    // sets the value (range from 0 to 255)
    delay(2000);                            
    } 
  
  delay(10000);
  
   // fade out from max to min in increments of 5 points:
   for(int fadeValue = 255 ; fadeValue >= 150; fadeValue -=10)
   { 
     setVoltage(fadeValue);
    // sets the value (range from 0 to 255)   
    delay(2000);                            
   } 
  
}

void setVoltage(int fadeValue){
  /*analogWrite(5, fadeValue);
    analogWrite(6, fadeValue);   
    analogWrite(10, fadeValue); 
    analogWrite(11, fadeValue);*/
    analogWrite(5,fadeValue);
}

