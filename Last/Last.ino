#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <NewPing.h>
#include <Servo.h>
#include <AFMotor.h>
#include <BlynkSimpleSerialBLE.h>

#define BLYNK_PRINT Serial
#define GPS_RX 4
#define GPS_TX 3
#define ADXL345_ADDR 0x53
#define SERVO_PIN 5
#define MOTOR1_PWM 3
#define MOTOR1_DIR 12
#define MOTOR2_PWM 11
#define MOTOR2_DIR 13
#define TRIGGER_PIN A0
#define ECHO_PIN A1

SoftwareSerial gpsSerial(GPS_RX, GPS_TX);
TinyGPS gps;
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);
NewPing sonar(TRIGGER_PIN, ECHO_PIN, 200);
Servo servo;
AF_DCMotor motor1(MOTOR1_DIR, MOTOR1_PWM);
AF_DCMotor motor2(MOTOR2_DIR, MOTOR2_PWM);

char auth[] = "your_Blynk_token";
char ssid[] = "your_SSID";
char pass[] = "your_WIFI_password";
int ledPin = 13;
int buttonState = 0;

void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);
  Blynk.begin(Serial, auth);
  accel.begin();
  servo.attach(SERVO_PIN);
  pinMode(ledPin, OUTPUT);
  motor1.setSpeed(255);
  motor2.setSpeed(255);
}

void loop()
{
  Blynk.run();
  readGPS();
  readAccelerometer();
  readUltrasonic();
}

void readGPS()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences;
  float flat, flon;
  unsigned long age;
  gpsSerial.listen();
  while (gpsSerial.available())
  {
    char c = gpsSerial.read();
    if (gps.encode(c))
      newData = true;
  }
  if (newData)
  {
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("GPS Latitude:");
    Serial.print(flat, 4);
    Serial.print(" GPS Longitude:");
    Serial.println(flon, 4);
  }
}

void readAccelerometer()
{
  sensors_event_t event;
  accel.getEvent(&event);
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  Serial.print("X:");
  Serial.print(x);
  Serial.print(" Y:");
  Serial.print(y);
  Serial.print(" Z:");
  Serial.println(z);
  if (x > 2.0)
  {
    digitalWrite(ledPin, HIGH);
    servo.write(0);
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    Blynk.virtualWrite(V0, 1);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    servo.write(90);
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    Blynk.virtualWrite(V0, 0);
  }
}

void readUltrasonic()
{
  delay(50);
  unsigned int distance = sonar.ping_cm();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

BLYNK_WRITE(V0)
{
   buttonState = param.asInt();
  if (buttonState == 1)
  {
    digitalWrite(ledPin, HIGH);
    servo.write(0);
  }
  else
  {
    digitalWrite(ledPin, LOW);
    servo.write(90);
  }
}
