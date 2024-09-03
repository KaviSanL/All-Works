#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <BlynkSimpleSerialBLE.h>

SoftwareSerial gpsSerial(2, 3); // RX, TX pins for GPS module
TinyGPS gps; // Create a new instance of the TinyGPS object
SoftwareSerial bluetoothSerial(4, 5); // RX, TX pins for Bluetooth module
char auth[] = "your_auth_token"; // Your Blynk auth token

int motor1Speed = 0; // Initialize motor speeds to 0
int motor2Speed = 0;
int motor1Pin1 = 6; // Motor driver pins for motor 1
int motor1Pin2 = 7;
int motor2Pin1 = 8; // Motor driver pins for motor 2
int motor2Pin2 = 9;

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  gpsSerial.begin(9600); // Initialize GPS serial communication
  bluetoothSerial.begin(9600); // Initialize Bluetooth serial communication
  Blynk.begin(bluetoothSerial, auth); // Connect to Blynk app using Bluetooth
  pinMode(motor1Pin1, OUTPUT); // Initialize motor driver pins
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
}

void loop() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    if (gps.encode(c)) {
      double lat, lng;
      gps.f_get_position(&lat, &lng);
      Blynk.virtualWrite(V1, lat); // Update Blynk app with GPS coordinates
      Blynk.virtualWrite(V2, lng);
      if (Blynk.connected()) {
        Blynk.run(); // Run Blynk app commands
      }
      double targetLat = 12.3456; // Replace with your target latitude
      double targetLng = 78.9101; // Replace with your target longitude
      double distance = TinyGPS::distance_between(lat, lng, targetLat, targetLng); // Calculate distance to target
      if (distance <= 10) { // If within 10 meters of target
        motor1Speed = 0; // Stop both motors
        motor2Speed = 0;
      } else {
        if (lng < targetLng) { // If target is to the east
          motor1Speed = 100; // Set motor 1 to full speed forward
          motor2Speed = 50; // Set motor 2 to half speed forward
        } else if (lng > targetLng) { // If target is to the west
          motor1Speed = 50; // Set motor 1 to half speed forward
          motor2Speed = 100; // Set motor 2 to full speed forward
        }
      }
      analogWrite(motor1Pin1, motor1Speed); // Set motor speeds using PWM
      analogWrite(motor1Pin2, 0);
      analogWrite(motor2Pin1, motor2Speed);
      analogWrite(motor2Pin2, 0);
    }
  }
}
