int pwm = 5, val=0;


void setup(){
  Serial.begin(9600);
  pinMode(pwm , OUTPUT);
  analogWrite(pwm , 0);
  delay(15000);
}

void loop()
{  
  analogWrite(pwm , 0);
  delay(15000);
  
   for(int i = 0;i <=255;i+=5)
   {
       analogWrite(pwm , i);
      Serial.println(i);
      delay(500);
   }
  delay(2000);
   for(int i = 255;i >=0;i-=5)
   {
       analogWrite(pwm , i);
      Serial.println(i);
      delay(500);
   }
  delay(2000);
  
}
