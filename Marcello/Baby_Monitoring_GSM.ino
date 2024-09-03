#define echoPin 2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 3                                      
#include <LiquidCrystal_I2C.h>

#include  <Wire.h>

//initialize the liquid crystal library
//the first parameter is  the I2C address
//the second parameter is how many rows are on your screen
//the  third parameter is how many columns are on your screen
LiquidCrystal_I2C lcd(0x27,  16, 2);
long duration; // Variable to store time taken to the pulse
               // to reach receiver
 
int distance; // Variable to store distance calculated using
              // formula
       

#include <SoftwareSerial.h>

// Define GSM module pins
#define GSM_TX_PIN 7  // Connect GSM module TX pin to Arduino pin 7
#define GSM_RX_PIN 8  // Connect GSM module RX pin to Arduino pin 8

// Define vibration sensor pin
#define SoundSenorPIN 6  // Connect vibration sensor to Arduino pin 2

SoftwareSerial gsmSerial(GSM_TX_PIN, GSM_RX_PIN);  // RX, TX

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2




void setup() {
  Serial.begin(115200);
   gsmSerial.begin(115200);
   pinMode(trigPin,OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 
  
    Serial.println(
        "Baby Monitoring System");
    delay(500);
  
   lcd.init();  // turn on the backlight
  lcd.backlight();
 
  // Initialize vibration sensor pin as input
  pinMode(SoundSenorPIN, INPUT);
  
 
  
  sendCommand("AT"); // Check if the module is responding
  delay(1000);
  
  // Enable caller ID information
  sendCommand("AT+CLIP=1");

 
}

void loop() {
  // start working...
  //ultrasonic
  digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor
 
    digitalWrite(trigPin,HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(10); // keep the trigger "ON" for 10 ms to generate
             // pulse for 10 ms.
 
    digitalWrite(trigPin,LOW); 
    duration = pulseIn(echoPin, HIGH);
    
    distance= duration * 0.0344 / 2;
        
    
        Serial.print("Distance: ");
    Serial.print(distance); // Print the output in serial monitor
    Serial.println(" cm");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("distance;");
    lcd.print(distance);
    delay(100);
    lcd.clear();
  
  if(distance>=2){
  
    // Send SMS
    Serial.println("BabyMoovFromBed");
    BabyMoov("+917339224811"); // Replace with your mobile number
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("YourBabyMoove");
  delay(2000); // Adjust delay time as needed
  lcd.clear();
}
 
int SoundValue = digitalRead(SoundSenorPIN);
if(SoundValue == LOW){
  Serial.println("BabyCrying");
  BabyCry("+917339224811", "Ohh.....Your Baby is crying......");//your num
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Your Baby Cry");
    // Wait for a while to prevent sending multiple SMS in a short time
    delay(5000);
    lcd.clear();

}
else{
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Your baby sleep...");
}
delay(1000);
lcd.clear();
  
}

void BabyCry(String phoneNumber, String message) {
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
void  BabyMoov(const char* number) {
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
