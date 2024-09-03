


// Maximum distance we want to ping for (in centimeters).
#define max_distance 200



const int trigPin = 7;
const int echoPin = 6;
long duration;
int distance;
int distance1;
int speakerPin = 8;
void setup() 
{
  Serial.begin(9600); // Initializes the interface to the LCD screen
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() 
{
  // Write a pulse to the HC-SR04 Trigger Pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Measure the response from the HC-SR04 Echo Pin
  duration = pulseIn(echoPin, HIGH);
  
  // Determine distance from duration
  // Use 343 metres per second as speed of sound
  distance= duration*0.034/2;
  distance1= 180 - distance ;
  // Prints "Distance: <value>" on the first line of the LCD

  if (distance1 > 100) {
   tone (speakerPin, 1000);
  
   } else {
    noTone (speakerPin);

  }
  lcd.setCursor(0,0);
  lcd.print("HEIGHT: ");
  lcd.print(distance1);
  lcd.print("  cm  ");

  // Draws bargraph on the second line of the LCD
  lcd.setCursor(0,1);
  lbg.drawValue(distance1, max_distance);
  delay(500);
}
