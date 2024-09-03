
#define relay1 4 
#define relay2 6//Motor1  L293 Pin in1 
void setup(){
  Serial.begin(9600);
pinMode(relay1,OUTPUT);
pinMode(relay2,OUTPUT);
}
void loop(){
  digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);
  delay(1000);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay1, LOW);
  delay(1000);
}
