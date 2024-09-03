# define ldr A0
#define Relay 4
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include  <Wire.h>
LiquidCrystal_I2C lcd(0x27,  16, 2);
#define GSM_TX_PIN 7 
#define GSM_RX_PIN 8
#define Vibration 3
SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);
void setup()
{
  pinMode(ldr,INPUT);
  Serial.begin(9600);
  gsmSerial.begin(9600);
  pinMode(Vibration, INPUT);
  pinMode(Relay,OUTPUT);
  lcd.init();
  lcd.backlight();
  sendCommand("AT");
  delay(1000);
  sendCommand("AT+CLIP=1");
}
void loop()
{
  int ldrValue = analogRead(ldr);
  int vibrationValue = digitalRead(Vibration);
  if(ldrValue >= 80)
  {
    lcd.clear();
    Serial.println(ldrValue);
    Serial.print("HeadlightON");
    lcd.setCursor(0,0);
    lcd.print("HeadlightON");
    delay(1000);
    digitalWrite(Relay,1);
    lcd.clear();
  }
  else
  {
  lcd.clear();
  Serial.print("HeadlightOFF");
  lcd.setCursor(0,0);
  lcd.print("HeadlightOFF");
  delay(1000);
  digitalWrite(Relay,0);
  lcd.clear();
  }
  if(vibrationValue == LOW)
  {
    Serial.println("Vehicle in to the accident");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Accident....");
    accidentAlert("Your Number");
    delay(3000);
    lcd.clear();
  }
  else
  {
    Serial.println("Safe ride");
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Vehicle Safe");
    delay(3000);
    lcd.clear();
  }
  delay(3000);
  lcd.clear();
}
void accidentAlert(const char* number) {
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