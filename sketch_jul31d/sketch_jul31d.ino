// Define the pins for the IR sensors
const int sensor1 = 2;
const int sensor2 = 3;
const int sensor3 = 4;
const int sensor4 = 5;
const int sensor5 = 6;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the IR sensor pins as inputs
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
}

void loop() {
  // Read the sensor values
  int s1 = digitalRead(sensor1);
  int s2 = digitalRead(sensor2);
  int s3 = digitalRead(sensor3);
  int s4 = digitalRead(sensor4);
  int s5 = digitalRead(sensor5);

  // Print the sensor values in the Serial Monitor
  Serial.print("Sensor 1: ");
  Serial.print(s1);
  Serial.print("\tSensor 2: ");
  Serial.print(s2);
  Serial.print("\tSensor 3: ");
  Serial.print(s3);
  Serial.print("\tSensor 4: ");
  Serial.print(s4);
  Serial.print("\tSensor 5: ");
  Serial.println(s5);

  // Add a small delay to avoid overwhelming the Serial Monitor
  delay(100);
}
