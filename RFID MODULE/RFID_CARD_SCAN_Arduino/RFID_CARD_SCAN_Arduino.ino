void setup() {
  Serial.begin(9600);
}

void loop() {
  static int count = 0; // Initialize count variable
  char data;

  if (Serial.available()) {
    data = Serial.read();
    
    if (data) {
      Serial.print(data);
      count++;

      if (count == 12) {
        Serial.println(); // Print a new line
        count = 0; // Reset count to 0
      }
    }
  }
  if (count == 0) {
    delay(300); // Delay for 1 second between reading different RFID tags
  }
}
