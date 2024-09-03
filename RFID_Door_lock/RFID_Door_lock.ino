#include<Servo.h>
#include <LiquidCrystal_I2C.h>

#include  <Wire.h>

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
   # define ledGreen 3
   # define ledRed 4
   # define Buzz 5
int count=0;
String expectedRFIDCard = "540070CB5DB2"; // Replace with your RFID card number
Servo myservo;
void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(ledGreen,OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(Buzz,OUTPUT);
  lcd.init();  // turn on the backlight
  lcd.backlight();
}

void loop() {
  if (Serial.available() > 0) {
    String rfidData = Serial.readStringUntil('\n'); // Read the RFID data
   
    if (rfidData != "") {
      rfidData.trim(); // Remove leading/trailing whitespace
      
      if (rfidData == expectedRFIDCard && count==0) {
        lcd.clear();
        Serial.println(" RFID card Ture");
        Serial.println(" Opened"); // Print the scanned RFID card data to serial monitor 
        myservo.write(90);
        lcd.setCursor(0,1);
        lcd.print("Door opened");
        digitalWrite(ledGreen,1);
        digitalWrite(ledRed,0);
        digitalWrite(Buzz,0);
        
          
        count++;
        rfidData = "540070CB5DB3";
      }
      
      else if(rfidData == expectedRFIDCard && count==1){
        lcd.clear();
        Serial.println(" RFID card Ture");
        Serial.println("Closed"); // Print the scanned RFID card data to serial monitor 
        myservo.write(0);
        lcd.setCursor(0,1);
        lcd.print("Door Closed");//degree yoou will assign for closing the door
        digitalWrite(ledGreen,1);
        
        digitalWrite(ledRed,0);
        digitalWrite(Buzz,0);
       
        //degree you will assign for closing the door 
        count--;
        rfidData = "540070CB5DB3";
      }
      else{

        Serial.println(" Error RFID card "); // Print the scanned RFID card data to serial monitor
        lcd.clear();
        lcd.setCursor(0,1);
        lcd.print("Wrong Card");
        digitalWrite(ledRed,1);
        digitalWrite(ledGreen,0);
        digitalWrite(Buzz,1);      
      }
       Serial.println("Scanned RFID card: " + rfidData); // Print the scanned RFID card data to serial monitor      
}
}
}