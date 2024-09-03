#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

#include  <Wire.h>

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
//Alarm reciever's phone number with country code
const String PHONE = "+917339224811";

//GSM Module RX pin to Arduino 3
//GSM Module TX pin to Arduino 2
#define rxPin 2
#define txPin 3
SoftwareSerial sim800(rxPin,txPin);

//the pin that the pir sensor is atteched to
int pir_sensor = 11;

void setup() {
  pinMode(pir_sensor, INPUT);    // initialize sensor as an input
  Serial.begin(115200);          // initialize serial

  sim800.begin(9600);
  Serial.println("SIM800L software serial initialize");

  sim800.println("AT");
  delay(1000);
  lcd.init();  // turn on the backlight
  lcd.backlight();
}

void loop(){

//////////////////////////////////////////////////
while(sim800.available()){
  Serial.println(sim800.readString());
}
//////////////////////////////////////////////////
while(Serial.available())  {
  sim800.println(Serial.readString());
}
//////////////////////////////////////////////////
  int val = digitalRead(pir_sensor);  // read sensor value
  if (val == LOW) {                  // check if the sensor is HIGH
    //state = HIGH;
    Serial.println("Motion detected!");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Theft Detected");
    Serial.println("calling....");
    delay(1000);
    sim800.println("ATD"+PHONE+";");
    delay(20000); //20 sec delay
  }
}