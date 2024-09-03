#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <AFMotor.h>
#include <BlynkSimpleSerialBLE.h>

// Define the motor pins
AF_DCMotor motor1(5);
AF_DCMotor motor2(6);
AF_DCMotor motor3(7);
AF_DCMotor motor4(8);

// Define the software serial pins for the GPS and Bluetooth modules
SoftwareSerial gpsSerial(3, 4); // RX, TX
SoftwareSerial bluetoothSerial(10, 11); // RX, TX

// Define the GPS object
TinyGPS gps;

// Define the Blynk auth token
char auth[] = "Blc98l6y-IW8-DXRkQUfazP7UqNvmcMB";

void setup() {
  // Initialize the serial ports
  Serial.begin(9600);
  gpsSerial.begin(9600);
  bluetoothSerial.begin(9600);

  // Set up the motor drive pins
  motor1.setSpeed(255);
  motor2.setSpeed(255);

  // Connect to the Blynk app
  Blynk.begin(bluetoothSerial, auth);
}

void loop() {
  // Read data from the GPS module
  while (gpsSerial.available()) {
    if (gps.encode(gpsSerial.read())) {
      // Get the current location from the GPS
      float lat, lon;
      gps.f_get_position(&lat, &lon);

      // Print the current location to the serial port
      Serial.print("Lat: ");
      Serial.print(lat, 6);
      Serial.print(", Lon: ");
      Serial.println(lon, 6);

      // Use the location to control the robot
      followMe(lat, lon);
    }
  }

  // Process incoming Bluetooth messages from the Blynk app
  Blynk.run();
}

void followMe(float lat, float lon) {
  // TODO: Implement follow me logic here

  // For now, just turn on the motors to move forward
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

// Define a Blynk callback to turn the robot on or off
BLYNK_WRITE(V1) {
  int value = param.asInt();

  if (value == HIGH) {
    motor1.run(FORWARD);
    motor2.run(FORWARD);
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  } else {
    motor1.run(RELEASE);
    motor2.run(RELEASE);
    motor3.run(RELEASE);
    motor4.run(RELEASE);
  }
}
