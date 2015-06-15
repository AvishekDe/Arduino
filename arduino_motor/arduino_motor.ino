int p1 = 3 , p2 = 5;
int a = 7 , b=9 , c=11 , d=13;

void setup(){
  Serial.begin(9600);
  
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


void loop(){
  
  
  for(int i = 50 ; i<=255 ; i+=5){
    analogWrite(p1 , i);
    analogWrite(p2 , i);
    delay(1000);
  }
  
  delay(5000);
  
  for(int j = 255 ; j>=50 ; j-=5){
    analogWrite(p1 , j);
    analogWrite(p2 , j);
    delay(1000);
  }
}
