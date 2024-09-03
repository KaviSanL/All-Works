   
const int ledPin = 13;   // Define the LED pin on the ESP8266 board
String expectedRFIDCard = "540070CB5DB2"; // Replace with your RFID card number

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Turn off the LED initially
}

void loop() {
  if (Serial.available() > 0) {
    String rfidData = Serial.readStringUntil('\n'); // Read the RFID data
   
    if (rfidData != "") {
      rfidData.trim(); // Remove leading/trailing whitespace
      
      if (rfidData == expectedRFIDCard) {
        digitalWrite(ledPin, HIGH); // Turn on the LED when a matching RFID card is scanned
        delay(1000); // You can adjust the delay as needed
        digitalWrite(ledPin, LOW); // Turn off the LED after a delay
      }
       Serial.println("Scanned RFID card: " + rfidData); // Print the scanned RFID card data to serial monitor      
    }
  }
}
