#include<Servo.h>
Servo myservo;
const int sensor2=2;
int stop=0;
int buttonvalue=0;
const int button=5;
const int servopin=3;
int sensorvalue2;
int count=0;
int pos;
void setup()
{
  Serial.begin(9600);
pinMode(sensor2,INPUT);
pinMode(button,INPUT);  
myservo.attach(servopin);
myservo.write(0);
}

void loop()
{
  delay(15); // Delay a little bit to improve simulation performance
  int a=0;
  sensorvalue2=digitalRead(sensor2);
  Serial.println(sensorvalue2);
  if(sensorvalue2==1 && count==0){
    
    counter();
  }
    delay(2000);
   while(count==1 && a<100 && stop==0){

    sensor();
    if(sensorvalue2==1){
    decounter();
      
    }
    else{
      myservo.attach(servopin);
      myservo.write(0);
      sensor();
      Serial.println("Motor Running");
      for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    sensor();
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    sensor();
      }
       for (pos = 0; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    sensor();
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);
    sensor();
      }
      
  }
  a++;  
}
  if(stop==1){
    rst();
    delay(5000);
  }
  


  
  
 
 
  
}
  void counter(){
    while(count==0 && sensorvalue2==1){
      count++;
      
    }
    sensorvalue2=0;
  }
void decounter(){
  count=0;
  stop=1;
  myservo.write(0);
  myservo.detach();
  Serial.println("Stopped");
}
void sensor(){
    
    sensorvalue2=digitalRead(sensor2);
    

}
void rst(){

  buttonvalue=digitalRead(button);
  Serial.println("Resetting");
  
  if(buttonvalue==1){
    Serial.print("resetted");
    count=0;
    stop=0;
    sensorvalue2=0;
    myservo.write(0);
    }

}
