int relay1 = 4;
int relay2 = 5;


void setup() {

    pinMode(relay1, OUTPUT);// set pin as output for relay 1
    pinMode(relay2, OUTPUT);// set pin as output for relay 2


    // keep the motor off by keeping both HIGH
    digitalWrite(relay1, HIGH); 
    digitalWrite(relay2, HIGH); 

 
  
  Serial.begin(9600);// initialize serial monitor with 9600 baud
  Serial.println("Robojax Motor Direction of Rotation");
  Serial.println("Using 2 Relays");  
  delay(2000);
}

void loop() {

 // Rotate in CCW direction
  digitalWrite(relay1, LOW);// turn relay 1 ON
  digitalWrite(relay2, HIGH);// turn relay 2 OFF  
  Serial.println("Rotating in CCW");  
  delay(3000);// wait for 3 seconds

 // stop the motor
 
  
 // Rotate in CW direction
  digitalWrite(relay1, HIGH);// turn relay 1 OFF
  digitalWrite(relay2, LOW);// turn relay 2 ON 
  Serial.println("Rotating in CW");  
  delay(3000);// wait for 3 seconds

 // stop the motor

  
 Serial.println("===============");

          
}// loop end 
