#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// replace with your network credentials
char ssid[] = "your_SSID";
char password[] = "your_PASSWORD";

// replace with your Blynk auth token
char auth[] = "your_AUTH_TOKEN";

void setup() {
  // initialize the serial communication
  Serial.begin(9600);

  // connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // connect to Blynk server
  Blynk.begin(auth, WiFi.SSID().c_str(), WiFi.psk().c_str());
}

void loop() {
  // run the Blynk event loop
  Blynk.run();
}
