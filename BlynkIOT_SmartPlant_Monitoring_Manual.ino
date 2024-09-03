// Viral Science www.viralsciencecreativity.com www.youtube.com/c/viralscience
// Blynk IOT Smart Plant Monitoring System

/* Connections
Relay. D3
Temp.  D4
Vcc 3.3v
GND  GND
*/

//Include the library files

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

//Initialize the LCD display



char auth[] = "fFBlcv_cFlaKuu5nP__bijES6bpBhI6b";  //Enter your Blynk Auth token
char ssid[] = "123456";  //Enter your WIFI SSID
char pass[] = "12345678";  //Enter your WIFI Password

DHT dht(D4, DHT11);//(DHT sensor pin,sensor type)  D4 DHT11 Temperature Sensor
BlynkTimer timer;

//Define component pins
#define Smoke A0     //A0 Smoke Moisture Sensor
#define fire D5

void checkPhysicalButton();
int relay1State = LOW;

#define RELAY_PIN_1       D3   //D3 Relay
  //D7 Button
#define VPIN_BUTTON_1    V12 

//Create three variables for pressure
double T, P;
char status;



void setup() {
  Serial.begin(9600);


 pinMode(RELAY_PIN_1, OUTPUT);
 digitalWrite(RELAY_PIN_1, LOW);

  digitalWrite(RELAY_PIN_1, relay1State);


  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();

  //Call the function
  timer.setInterval(100L, SmokeSensor);
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, fireSensor);
  
}


//Get the DHT11 sensor values
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);


}


//Get the Smoke moisture values
void SmokeSensor() {
  int value = analogRead(Smoke);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V3, value);

}
void fireSensor(){
int fireValue = analogRead(fire);
Blynk.virtualWrite(V2, fireValue);
}




BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}



void loop() {
   


     
      
  Blynk.run();//Run the Blynk library
  timer.run();//Run the Blynk timer

  }
