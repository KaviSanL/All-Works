#include <Servo.h>
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

 
int pos1 = 90; 
int pos2 = 0;

const int RELAY_PINR1 = 4; // R up   
const int RELAY_PINR2 = 5; // R down
const int RELAY_PINL1 = 9; // L up   
const int RELAY_PINL2 = 10; // L down

void setup() {
 servo1.attach(6);//Eyes
 servo2.attach(7);//Head
 servo3.attach(8);// R Hand
 servo4.attach(11);// L Hand
 pinMode(RELAY_PINR1, OUTPUT);
 pinMode(RELAY_PINR2, OUTPUT);
 pinMode(RELAY_PINL1, OUTPUT);
 pinMode(RELAY_PINL2, OUTPUT);
}

void loop()
{
  
  //turn from center to left
  
  for (pos1 = 90; pos1 >= 0; pos1 -= 1) 
  { 
    servo1.write(pos1);//eyes turns to left side               
    delay(15);  
    servo2.write(pos1);//head turns to left side
    delay(15);                    
  }


  //turn from left to center
  
  for (pos1 =0; pos1 <= 90; pos1 += 1) 
  { 
    servo1.write(pos1);//eyes comes to center              
    delay(15); 
    servo2.write(pos1);//head comes to center              
    delay(15);                      
  }


  digitalWrite(RELAY_PINR1, HIGH);   //Right hand up
  delay(2000);                     
  digitalWrite(RELAY_PINR1, LOW);    
  delay(3000); 
 
  for (pos2 = 0; pos2 <= 180; pos2 += 1) //Hold the fingers 
  { 
    servo3.write(pos2);              
    delay(15);                      
  }
  for (pos2 = 180; pos2 >= 0; pos2 -= 1) //Release the fingers
  { 
    servo3.write(pos2);              
    delay(15);                       
  }
  
  digitalWrite(RELAY_PINR2, HIGH);    //Right hand down
  delay(1000);                     
  digitalWrite(RELAY_PINR2, LOW);    
  delay(3000);

 //turn from center to right
  
  for (pos1 = 90; pos1 <= 180; pos1 += 1) 
  { 
    servo1.write(pos1); //eyes turn right side             
    delay(15);
    servo2.write(pos1); //head turn right side             
    delay(15);                       
  }


  //turn from right to center
 
  for (pos1 = 180; pos1 >= 90; pos1 -= 1)  
  { 
    servo1.write(pos1);//eyes comes to center              
    delay(15);
    servo2.write(pos1);//head comes to center              
    delay(15);                       
  }


  digitalWrite(RELAY_PINL1, HIGH);   //Left hand up
  delay(2000);                     
  digitalWrite(RELAY_PINL1, LOW);    
  delay(3000); 
 
  for (pos2 = 0; pos2 <= 180; pos2 += 1) //Hold the fingers 
  { 
    servo4.write(pos2);              
    delay(15);                      
  }
  for (pos2 = 180; pos2 >= 0; pos2 -= 1) //Release the fingers
  { 
    servo4.write(pos2);              
    delay(15);                       
  }
  
  digitalWrite(RELAY_PINL2, HIGH);    //Left hand down
  delay(1000);                     
  digitalWrite(RELAY_PINL2, LOW);    
  delay(3000);

}
