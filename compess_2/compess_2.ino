#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <SoftwareSerial.h>
#include <Adafruit_GPS.h>
#include <BlynkSimpleSerialBLE.h>

// Bluetooth module
SoftwareSerial bluetoothSerial(10, 11); // RX, TX

// GPS module
Adafruit_GPS GPS(&Serial1);

// Accelerometer
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// Blynk app auth token
char auth[] = "YourAuthToken";

// Robot pinout
const int leftMotorPin = 3;
const int rightMotorPin = 5;
const int ledPin = 13;

// Constants for robot control
const float maxSpeed = 255.0;
const float maxTurn = 0.5;

// Variables for robot control
float speed = 0.0;
float turn = 0.0;

void setup()
{
  // Initialize serial communication
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  GPS.begin(9600);
  accel.begin();

  // Initialize pins
  pinMode(leftMotorPin, OUTPUT);
  pinMode(rightMotorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize Blynk app
  Blynk.begin(auth, bluetoothSerial);
}

void loop()
{
  // Read GPS data
  GPS.read();
  float latitude = GPS.latitudeDegrees;
  float longitude = GPS.longitudeDegrees;

  // Read accelerometer data
  sensors_event_t event;
  accel.getEvent(&event);
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;

  // Compute speed and turn based on accelerometer data
  float pitch = atan2(y, sqrt(x*x + z*z)) * 180 / PI;
  speed = map(pitch, -90, 90, -maxSpeed, maxSpeed);
  float roll = atan2(x, sqrt(y*y + z*z)) * 180 / PI;
  turn = map(roll, -90, 90, -maxTurn, maxTurn);

  // Send data to Blynk app
  Blynk.virtualWrite(V0, latitude);
  Blynk.virtualWrite(V1, longitude);
  Blynk.virtualWrite(V2, speed);
  Blynk.virtualWrite(V3, turn);

  // Control robot based on speed and turn
  if (speed >= 0) {
    analogWrite(leftMotorPin, speed);
    analogWrite(rightMotorPin, speed * (1 - turn));
  } else {
    analogWrite(leftMotorPin, speed * (1 + turn));
    analogWrite(rightMotorPin, -speed);
  }
}

// Control robot on/off using Blynk app
BLYNK_WRITE(V4)
{
  int command = param.asInt();
  if (command == 1)
  {
    digitalWrite(ledPin, HIGH);
  }
  else if (command == 0)
  {
    digitalWrite(ledPin, LOW);
    analogWrite(leftMotorPin, 0);
    analogWrite(rightMotorPin, 0);
  }
}
