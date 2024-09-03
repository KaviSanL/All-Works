#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(2, 3); // RX, TX pins for GSM800L module

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);
  delay(1000);
  
  sendCommand("AT"); // Check if the module is responding
  delay(1000);
  
  // Enable caller ID information
  sendCommand("AT+CLIP=1");

  makeCall("+917339224811"); // Replace with your mobile number
  
  delay(2000); // Wait for 20 seconds before making the call again
}

void loop() {

}

void makeCall(const char* number) {
  gsmSerial.print("ATD");
  gsmSerial.print(number);
  gsmSerial.println(";");
  
  delay(15000); // Wait for 15 seconds
  
  gsmSerial.println("ATH"); // Hang up the call
  delay(1000);
}

void sendCommand(const char* command) {
  gsmSerial.println(command);
  
  while (!gsmSerial.available()) {} // Wait for response
  while (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}
