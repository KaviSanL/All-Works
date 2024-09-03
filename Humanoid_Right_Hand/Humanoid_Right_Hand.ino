#include <Servo.h>
Servo myservo; 
const int RELAY_PINR1 = 6; //6up   
const int RELAY_PINR2 = 4; //4down
int pos1 = 0; 

void setup() {
  pinMode(RELAY_PINR1, OUTPUT);
  pinMode(RELAY_PINR2, OUTPUT);
  myservo.attach(5);
}

void loop() {
  digitalWrite(RELAY_PINR1, LOW);   
  delay(2000);                     
  digitalWrite(RELAY_PINR1, HIGH);    
  delay(3000); 
 
  for (pos1 = 0; pos1 <= 180; pos1 += 1) 
  { 
    myservo.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  for (pos1 = 180; pos1 >= 0; pos1 -= 1) 
  { 
    myservo.write(pos1);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15 ms for the servo to reach the position
  }
  
  digitalWrite(RELAY_PINR2, LOW);   
  delay(1000);                     
  digitalWrite(RELAY_PINR2, HIGH);    
delay(3000);
}
