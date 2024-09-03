# define pir 2
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include  <Wire.h>
LiquidCrystal_I2C lcd(0x27,  16, 2);
#define GSM_TX_PIN 7 
#define GSM_RX_PIN 8
#define tilt 3
SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);
void setup()
{
  pinMode(pir,INPUT);
  Serial.begin(9600);
  gsmSerial.begin(9600);
  pinMode(tilt, INPUT);
  lcd.init();
  lcd.backlight();
  sendCommand("AT");
  delay(1000);
  sendCommand("AT+CLIP=1");
}
void loop()
{
  int pirValue = digitalRead(pir);
  int tiltValue = digitalRead(tilt);
  if(pir==LOW)
  {
    AnimalCrossAlert("Your Number", "The Animal Crossed the Gate No1.....");
    lcd.clear();
    Serial.print("Animal Crossed");
    lcd.setCursor(0,0);
    lcd.print("Animal crossed");
    delay(1000);
    lcd.clear();
  }
  else
  {
  lcd.clear();
  Serial.print("Animal Not Cross");
  lcd.setCursor(0,0);
  lcd.print("Animal Not Cross");
  delay(1000);
  lcd.clear();
  }
  if(tiltValue == LOW)
  {
    Serial.println("Animals Started to Fight");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("AnimalsAreFight");
    ThreadAlert("Your NUmber");
    delay(3000);
    lcd.clear();
  }
  else
  {
    Serial.println("Animals are Calm");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("No Thread");
    delay(3000);
    lcd.clear();
  }
  delay(3000);
  lcd.clear();
}
void AnimalCrossAlert(String phoneNumber, String message) {
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.println((char)26); 
  delay(1000);
}
void ThreadAlert(const char* number) {
  gsmSerial.print("ATD");
  gsmSerial.print(number);
  gsmSerial.println(";");
  delay(15000);
  gsmSerial.println("ATH");
  delay(1000);
}

void sendCommand(const char* command) {
  gsmSerial.println(command);
  while (!gsmSerial.available()) {} 
  while (gsmSerial.available())
   {
    Serial.write(gsmSerial.read());
  }
}