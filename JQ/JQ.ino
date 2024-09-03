#include<SoftwareSerial.h>
#include<JQ6500_Serial.h>
SoftwareSerial mySerial(8,9); 
JQ6500_Serial mp3(mySerial);

 void setup()
 {
  mySerial.begin(9600);
  mp3.reset();
  mp3.setVolume(50);
  mp3.setLoopMode(MP3_LOOP_NONE);
  mp3.play();
 }
 void loop()
 {
   mp3.play();
  mp3.playFileByIndexNumber(1);
    delay(2000);
    mp3.reset();
 }
