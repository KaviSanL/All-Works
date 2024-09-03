#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(1000);
  Serial.println("Initializing...");

  // Print instructions
  Serial.println("Type AT commands and press Enter:");
  /*( AT, AT+CPIN? , AT+CSQ , AT+CREG? , AT+COPS? , AT+CMGF=1 , ATD+919988776655;)
  AT: This is the basic command to check if the GSM module is responding. When you send "AT" to the module, it should respond with "OK" if it's working properly.

  AT+CPIN?: This command checks the status of the SIM card. If the module responds with "READY," it means the SIM card is detected and ready for use.

  AT+CSQ: This command checks the signal strength. The module will respond with a value in dB (decibels) indicating the signal quality. A higher value corresponds to better signal strength.

  AT+CREG?: This command checks the registration status of the module on the network. It will respond with a value that indicates whether the module is registered on the network.

  AT+COPS?: This command checks the current network operator. It will respond with the name of the network operator the module is connected to.

  AT+CMGF=1: This command sets the SMS mode to text mode.

  AT+CMGS="<phone_number>": This command is used to send an SMS. Replace*/
}

void loop() {
  // Check for user input
  if (Serial.available()) {
    char input = Serial.read();
    mySerial.write(input);

    // Read and print GSM response
    while (mySerial.available()) {
      char response = mySerial.read();
      Serial.write(response);
    }
  }

  // Check for GSM module response
  if (mySerial.available()) {
    char response = mySerial.read();
    Serial.write(response);
  }
}
