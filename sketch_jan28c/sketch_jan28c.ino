#include <Keypad.h>
#define in1 5
#define in3 4
#define enable 3
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 11, 10}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {9, 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup(){
  Serial.begin(9600);
  pinMode(in1,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(enable,OUTPUT);
}
void loop(){  
 char customKey = customKeypad.getKey();
  int a=0;
  int b=0;
  int c=0;
  Serial.println(customKey);
 
    
   while(customKey == '1'&& a<5){
  Serial.println("Mode 1");
 frd();
 delay(4000);
 rev();
 delay(4000);
 
a++;


  }
       if(a==5){
       digitalWrite(in1,LOW);
       digitalWrite(in3,LOW);
       analogWrite(enable,0);
       a=0;
     }
     while(customKey == '2'&&b<5)
    {
      Serial.println("Mode 2");
      frd();
       delay(8000);
       rev();
       delay(8000);
b++;


    }
   if(b==5){
      digitalWrite(in1,LOW);
       digitalWrite(in3,LOW);
       analogWrite(enable,0);
       b=0;
     }
     while(customKey == '3'&&c<5)
    {
      Serial.println("Mode 3");
      frd();
       delay(10000);
         rev();
       delay(10000);
c++;
       
     }
   if(c==5){
       digitalWrite(in1,LOW);
       digitalWrite(in3,LOW);
       analogWrite(enable,0);
       c=0;
     }
}
void frd(){
  digitalWrite(in1, HIGH);// turn relay 1 OFF
  digitalWrite(in3, LOW);
  analogWrite(enable,150);
  delay(2000);
  analogWrite(enable,0);
  delay(25);
}
void rev(){
  digitalWrite(in1, LOW);// turn relay 1 OFF
  digitalWrite(in3, HIGH);
  analogWrite(enable,150);
  delay(2000);
  analogWrite(enable,0);
  delay(25);

}
