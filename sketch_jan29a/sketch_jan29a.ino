#define relay1 4 //Motor1  L293 Pin in1 

#define relay2 6
void setup(){
  Serial.begin(9600);
pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT); 
}
void loop(){
  digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);
  delay(4000);
   digitalWrite(relay1, LOW);// turn relay 1 OFF
  digitalWrite(relay2, HIGH);
  
  delay(4000);
}
