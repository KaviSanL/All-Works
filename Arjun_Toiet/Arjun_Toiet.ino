  #include<Servo.h>
#define trigPin 6  
#define echoPin 5
#define GreenLED 2
#define RedLED 3
#define Relay 4
#define BlueLED 7
float new_delay; 
Servo myservo;
int pos = 0;
void setup() 
{
  Serial.begin (9600); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(GreenLED,OUTPUT);
  pinMode(RedLED,OUTPUT);
  pinMode(Relay,OUTPUT);
  pinMode(BlueLED,OUTPUT);
  myservo.attach(9);
}


void loop() 
{
  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
//  new_delay= (distance *3) +30;
  Serial.print(distance);
  Serial.println("  cm");
  if (distance < 10)
  {
   myservo.write(90);
   delay(500);
   
  }
   
 
  

  
}
