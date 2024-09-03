#include <Servo.h>
#define LDR1 A0
#define LDR2 A1
#define error 10
int Spoint =  90;
Servo servo;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  servo.write(Spoint);
  delay(1000);
}

void loop() {
   int ldr1 = analogRead(LDR1);
   int ldr2 = analogRead(LDR2);
   Serial.print(ldr1);
      Serial.print(" ");
   Serial.println(ldr2);


  int value1 = abs(ldr1 - ldr2);
  int value2 = abs(ldr2 - ldr1);


  if ((value1 <= error) || (value2 <= error)) {

  } else {
    if (ldr1 > ldr2) {
      Spoint = --Spoint;
    }
    if (ldr1 < ldr2) {
      Spoint = ++Spoint;
    }
  }

  servo.write(Spoint);
  delay(80);
}