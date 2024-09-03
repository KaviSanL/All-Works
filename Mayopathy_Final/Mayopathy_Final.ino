#include <Keypad.h>
#define relay1 2 //Motor1  L293 Pin in1 

#define relay2 5


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
pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT); 
}
void loop(){
  char customKey = customKeypad.getKey();
  int a=0;
  int b=0;
  int c=0;
  int d=0;
  Serial.println(customKey);
 
    
   while(customKey == '1'&& a<20){
    Serial.println("Mode 1");
digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);
  delay(1000);
   digitalWrite(relay1, LOW);// turn relay 1 OFF
  digitalWrite(relay2, HIGH);
  
  delay(1000);
a++;

  }
     while(customKey == '2'&&b<20)
    {
      Serial.println("Mode 2");
digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);
  delay(3000);
   digitalWrite(relay1, LOW);// turn relay 1 OFF
  digitalWrite(relay2, HIGH);
  
  delay(3000);
b++;


    }
     while(customKey == '3'&&c<20)
    {
      Serial.println("Mode 3");
digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);
  delay(5000);
   digitalWrite(relay1, LOW);// turn relay 1 OFF
  digitalWrite(relay2, HIGH);
  
  delay(5000);
c++;
    }
while(customKey == '4'&&d<20)
    {
      Serial.println("Mode 4");
digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);
  delay(7000);
   digitalWrite(relay1, LOW);// turn relay 1 OFF
  digitalWrite(relay2, HIGH);
  
  delay(7000);
  d++;


    }
   
  
}
