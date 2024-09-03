#include <SimpleDHT.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// Define GSM module pins
#define GSM_TX_PIN 7  // Connect GSM module TX pin to Arduino pin 7
#define GSM_RX_PIN 8  // Connect GSM module RX pin to Arduino pin 8

// Define vibration sensor pin
#define FlameSenorPIN 3  // Connect vibration sensor to Arduino pin 2

SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);  // RX, TX

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 2;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
   gsmSerial.begin(9600);
  
  // Initialize vibration sensor pin as input
  pinMode(FlameSenorPIN, INPUT);
  gsmSerial.begin(9600);
  delay(1000);
  
  sendCommand("AT"); // Check if the module is responding
  delay(1000);
  
  // Enable caller ID information
  sendCommand("AT+CLIP=1");

  makeCall("+917339224811"); // Replace with your mobile number
  
  delay(2000);
}

void loop() {
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  lcd.print("tempature  "); lcd.print((int)temperature);
  lcd.setCursor(0, 1);
  lcd.print("humidity  ");
  lcd.print((int)humidity);
  delay(1000);
  if(temperature>=40){
  
    // Send SMS
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Temperature is High");
    sendSMS("+917339224811", "It,s HIGH Temperature!");//your num
    
    // Wait for a while to prevent sending multiple SMS in a short time
    delay(5000); // Adjust delay time as needed
}
int flameValue = digitalRead(FlameSenorPIN);
if(flameValue == HIGH){
  Serial.println("Flame");
  makeCall("+917339224811"); // Replace with your mobile number
  
  delay(2000);

}
  
}

void sendSMS(String phoneNumber, String message) {
  // Send SMS command
  gsmSerial.println("AT+CMGF=1"); // Set SMS mode to text
  delay(1000);
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(phoneNumber);
  gsmSerial.println("\"");
  delay(1000);
  gsmSerial.println(message);
  delay(100);
  gsmSerial.println((char)26); // End SMS
  delay(1000);
}
void makeCall(const char* number) {
  gsmSerial.print("ATD");
  gsmSerial.print(number);
  gsmSerial.println(";");
  
  delay(15000); // Wait for 15 seconds
  
  gsmSerial.println("ATH"); // Hang up the call
  delay(1000);
}

void sendCommand(const char* command) {
  gsmSerial.println(command);
  
  while (!gsmSerial.available()) {} // Wait for response
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}
