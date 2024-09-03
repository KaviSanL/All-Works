#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#define echoPin                                            \
    2 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin                                            \
    3            // attach pin D3 Arduino to pin Trig of HC-SR04      
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX 
 SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
long duration; // Variable to store time taken to the pulse
               // to reach receiver
 
int distance; // Variable to store distance calculated using
              // formula
DFRobotDFPlayerMini player;
 
void setup()
{
    pinMode(trigPin,
            OUTPUT); // Sets the trigPin as an OUTPUT
    pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
 
    // Serial Communication is starting with 9600 of
    // baudrate speed
    Serial.begin(9600);
  softwareSerial.begin(9600);
    // The text to be printed in serial monitor
    Serial.println(
        "Distance measurement using Arduino Uno.");
    delay(500);
     if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);

  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
    delay(500);
}
 
void loop()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2); // wait for 2 ms to avoid
                          // collision in serial monitor
 
    digitalWrite(
        trigPin,
        HIGH); // turn on the Trigger to generate pulse
    delayMicroseconds(
        10); // keep the trigger "ON" for 10 ms to generate
             // pulse for 10 ms.
 
    digitalWrite(trigPin,
                 LOW); // Turn off the pulse trigger to stop
                       // pulse generation
 
    // If pulse reached the receiver echoPin
    // become high Then pulseIn() returns the
    // time taken by the pulse to reach the
    // receiver
 
    duration = pulseIn(echoPin, HIGH);
    distance
        = duration * 0.0344 / 2; // Expression to calculate
                                 // distance using time
 
    Serial.print("Distance: ");
    Serial.print(
        distance); // Print the output in serial monitor
    Serial.println(" cm");
    delay(100);
    if(distance >= 10)
    {
      Serial.println("Obstacle Detected");
      player.volume(30);
      player.play(1);
    }
}