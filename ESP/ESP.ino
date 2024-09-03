#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// create a software serial object to read the GPS module
SoftwareSerial gpsSerial(D5, D6);  // RX, TX

// create a TinyGPS++ object to parse the GPS data
TinyGPSPlus gps;

void setup() {
  // initialize the serial communication
  Serial.begin(9600);
  gpsSerial.begin(9600);
}

void loop() {
  // read data from the GPS module
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      // get the latitude, longitude, and altitude
      float latitude = gps.location.lat();
      float longitude = gps.location.lng();
      float altitude = gps.altitude.meters();
      
      // print the location data
      Serial.print("Latitude: ");
      Serial.println(latitude, 6);
      Serial.print("Longitude: ");
      Serial.println(longitude, 6);
      Serial.print("Altitude: ");
      Serial.println(altitude);
    }
  }
}
