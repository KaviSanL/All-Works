#include<Arduino.h>
#include<SoftwareSerial.h>
#include<TinyGPS.h>
#include<JQ6500_Serial.h>
SoftwareSerial mySerial(6,7); 
JQ6500_Serial mp3(mySerial);
const int trigpin= 9; //CONNECT THE TRIGGER PIN TO DIGITAL PIN 9
const int echopin= 10; //CONNECT THE ECHO PIN TO DIGITAL PIN 10
long duration;
int distance;
const int relay=8;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echopin, INPUT);
  pinMode(relay,OUTPUT);
  mySerial.begin(9600);
  mp3.reset();
  mp3.setVolume(50);
  mp3.setLoopMode(MP3_LOOP_NONE);
  mp3.play();
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigpin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);
  duration = pulseIn(echopin, HIGH);
  //distance = duration*0.034/2;      
  distance = duration/58.2;
  if(distance<=30){
    Serial.println("Obstacle Detecting");
    digitalWrite(relay,HIGH);
    delay(1000);
     mp3.playFileByIndexNumber(1);
  }
  else
      digitalWrite(relay,LOW);
}
