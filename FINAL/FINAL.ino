#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
#include <TinyGPS.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define trigPin D2
#define echoPin D1
#define motor1Pin1 D5
#define motor1Pin2 D6
#define motor2Pin1 D7
#define motor2Pin2 D8

char auth[] = "2IGcchawaYkT1PWNqBfP2B1UJErP_1KY";
char ssid[] = "FollowME";
char pass[] = "12345678";

SoftwareSerial ss(D3, D4);
TinyGPS gps;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

BlynkTimer timer;

void setup() {
  Serial.begin(9600);
  ss.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  accel.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendGps);
}

void loop() {
  Blynk.run();
  timer.run();
  if (ss.available()) {
    gps.encode(ss.read());
  }
  sensors_event_t event;
  accel.getEvent(&event);
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  float angle = atan2(-x, sqrt(y * y + z * z)) * 180 / M_PI;
  if (angle > 10) {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
  } else if (angle < -10) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
  } else {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
  }
}

void sendGps() {
  float latitude, longitude;
  unsigned long fix_age, time, date, speed;
  gps.f_get_position(&latitude, &longitude, &fix_age);
  speed = gps.f_speed_kmph();
  
  Blynk.virtualWrite(V1, latitude);
  Blynk.virtualWrite(V2, longitude);
  Blynk.virtualWrite(V3, speed);
  
}

BLYNK_WRITE(V4) {
  int buttonState = param.asInt();
  if (buttonState == 1) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin2, HIGH);
    digitalWrite(motor2Pin2, HIGH);
  } else {
    // Turn off the robot
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    digitalWrite(motor2Pin2, LOW);
  }
}
