
void setup() {
  Serial.begin(9600);
  
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
  delay(1000);
  
}
 
void loop() {
  int value = analogRead(A0);
  Serial.println(value);
  if (value > 1000) {
    digitalWrite(2, LOW);
    
  } else {
    digitalWrite(2, HIGH);
   
  }
 
 
}
