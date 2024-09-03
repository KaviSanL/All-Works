#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <BlynkSimpleSerialBLE.h>

#define BLYNK_PRINT Serial
#define RX_PIN 3
#define TX_PIN 2
#define MAX_SPEED 255

// Initialize Bluetooth serial connection
SoftwareSerial Bluetooth(RX_PIN, TX_PIN);

// Initialize GPS module
TinyGPSPlus gps;

// Initialize motor shield
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *leftMotor = AFMS.getMotor(1);
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);

// Initialize Blynk app
char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  AFMS.begin();
  Blynk.begin(Serial, auth);
}

void loop() {
  // Read GPS data and update location
  while (Bluetooth.available() > 0) {
    if (gps.encode(Bluetooth.read())) {
      if (gps.location.isValid()) {
        // Get current latitude and longitude
        double lat = gps.location.lat();
        double lon = gps.location.lng();
        
        // Send data to Blynk app
        Blynk.virtualWrite(V1, lat);
        Blynk.virtualWrite(V2, lon);
        
        // Calculate distance from target location
        double targetLat = TARGET_LATITUDE;
        double targetLon = TARGET_LONGITUDE;
        double distance = TinyGPSPlus::distanceBetween(lat, lon, targetLat, targetLon);
        
        // Adjust robot movement based on distance
        if (distance < 20) {
          // Stop robot when target is reached
          leftMotor->setSpeed(0);
          rightMotor->setSpeed(0);
        } else {
          // Set motor speed based on distance
          int speed = (int)(distance / 100 * MAX_SPEED);
          leftMotor->setSpeed(speed);
          rightMotor->setSpeed(speed);
          
          // Set motor direction based on location
          if (lat > targetLat) {
            leftMotor->run(BACKWARD);
            rightMotor->run(BACKWARD);
          } else {
            leftMotor->run(FORWARD);
            rightMotor->run(FORWARD);
          }
        }
      }
    }
  }
  Blynk.run();
}
