#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <BlynkSimpleSerialBLE.h>

// Motor control pins
const int leftMotorA = 5;
const int leftMotorB = 6;
const int rightMotorA = 9;
const int rightMotorB = 10;

// GPS serial pins
SoftwareSerial gpsSerial(2, 3); // RX, TX
TinyGPSPlus gps;

// Blynk authentication token and WiFi credentials
char auth[] = "Blc98l6y-IW8-DXRkQUfazP7UqNvmcMB";
char ssid[] = "Mari's iPhone";
char pass[] = "marimuthu";

// Destination coordinates
float destLat = 0.0;
float destLon = 0.0;

// Current coordinates
float currentLat = 0.0;
float currentLon = 0.0;

// Distance threshold
const float threshold = 10.0; // meters

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Blynk.begin(Serial, auth);
  
  // Initialize motor control pins as outputs
  pinMode(leftMotorA, OUTPUT);
  pinMode(leftMotorB, OUTPUT);
  pinMode(rightMotorA, OUTPUT);
  pinMode(rightMotorB, OUTPUT);
}

void loop()
{
  Blynk.run();
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      currentLat = gps.location.lat();
      currentLon = gps.location.lng();
    }
  }
  
  float distance = TinyGPSPlus::distanceBetween(
    currentLat, currentLon,
    destLat, destLon
  );

  Serial.print("Distance to destination: ");
  Serial.print(distance, 6);
  Serial.println(" meters");

  if (distance < threshold) {
    // stop the robot
    digitalWrite(leftMotorA, LOW);
    digitalWrite(leftMotorB, LOW);
    digitalWrite(rightMotorA, LOW);
    digitalWrite(rightMotorB, LOW);
  } else {
    // move the robot towards the destination
    if (currentLon < destLon) {
      // turn right
      digitalWrite(leftMotorA, HIGH);
      digitalWrite(leftMotorB, LOW);
      digitalWrite(rightMotorA, LOW);
      digitalWrite(rightMotorB, HIGH);
    } else {
      // turn left
      digitalWrite(leftMotorA, LOW);
      digitalWrite(leftMotorB, HIGH);
      digitalWrite(rightMotorA, HIGH);
      digitalWrite(rightMotorB, LOW);
    }
  }
}

BLYNK_WRITE(V0)
{
  destLat = param[0].asFloat();
  destLon = param[1].asFloat();
  Serial.print("Destination latitude: ");
  Serial.println(destLat, 6);
  Serial.print("Destination longitude: ");
  Serial.println(destLon, 6);
}
