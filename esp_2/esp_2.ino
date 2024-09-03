#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BlynkWifi blynk;
// Motor driver pins
int enA = D1;
int in1 = D2;
int in2 = D3;
int enB = D4;
int in3 = D5;
int in4 = D6;

// GPS module pins
SoftwareSerial ss(D7, D8); // RX, TX
TinyGPS gps;
float lat = 0.0;
float lng = 0.0;

// Blynk app authentication token
char auth[] = "your_auth_token";

void setup() {
  // Set motor driver pins as output
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize GPS module
  ss.begin(9600);

  // Initialize Blynk
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());

  // Set up Blynk app buttons
  Blynk.virtualWrite(V1, LOW); // Stop
  Blynk.virtualWrite(V2, HIGH); // Follow me
}

void loop() {
  // Update GPS location
  while (ss.available()) {
    gps.encode(ss.read());
  }
  gps.f_get_position(&lat, &lng);

  // Update motor speed and direction based on Blynk app input
  int leftSpeed = 0;
  int rightSpeed = 0;
  int followMe = Blynk.virtualRead(V2);
  if (followMe) {
    // Calculate direction and speed based on GPS location
    if (lng < -122.4) { // Robot is to the left of target
      leftSpeed = 100;
      rightSpeed = 50;
    } else if (lng > -122.2) { // Robot is to the right of target
      leftSpeed = 50;
      rightSpeed = 100;
    } else { // Robot is on target
      leftSpeed = 100;
      rightSpeed = 100;
    }
  } else {
    // Stop the robot
    leftSpeed = 0;
    rightSpeed = 0;
  }

  // Set motor speed and direction
  analogWrite(enA, leftSpeed);
  digitalWrite(in1, leftSpeed > 0);
  digitalWrite(in2, leftSpeed < 0);
  analogWrite(enB, rightSpeed);
  digitalWrite(in3, rightSpeed > 0);
  digitalWrite(in4, rightSpeed < 0);

  // Update Blynk app button states
  if (followMe) {
    Blynk.virtualWrite(V1, LOW); // Stop
    Blynk.virtualWrite(V2, HIGH); // Follow me
  } else {
    Blynk.virtualWrite(V1, HIGH); // Stop
    Blynk.virtualWrite(V2, LOW); // Follow me
  }

  // Run Blynk app
  Blynk.run();
}
