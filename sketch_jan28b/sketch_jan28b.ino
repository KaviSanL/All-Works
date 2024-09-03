
const int RELAY_PINR1 = 6; //6up   
const int RELAY_PINR2 = 4; //4down


void setup() {
  pinMode(RELAY_PINR1, OUTPUT);
  pinMode(RELAY_PINR2, OUTPUT);
 
}

void loop() {
  digitalWrite(RELAY_PINR1, HIGH);// turn relay 1 OFF
  digitalWrite(RELAY_PINR2, LOW);
  delay(4000);
   digitalWrite(RELAY_PINR1, LOW);// turn relay 1 OFF
  digitalWrite(RELAY_PINR2, HIGH);
  
  delay(4000);
}
