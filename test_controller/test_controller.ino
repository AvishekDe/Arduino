
#define outPin 5
#define inPin A0

void setup(){
  Serial.begin(9600);
}

void loop(){
  //delay(1000);
  pinMode(outPin , OUTPUT);
  pinMode(inPin , INPUT);
  for(int i=0 ; i<=250 ; i+=1){
    analogWrite(outPin , i);
    //delay(1000);
    Serial.println(analogRead(inPin));
    //delay(3000);
  }
}
