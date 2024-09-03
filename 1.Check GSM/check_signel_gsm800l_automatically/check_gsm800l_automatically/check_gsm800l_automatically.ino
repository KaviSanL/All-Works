#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  delay(1000);
  Serial.println("Initializing...");

  // Check AT
  sendATCommand("AT");

  // Check SIM card status
  sendATCommand("AT+CPIN?");

  // Check signal strength
  sendATCommand("AT+CSQ");

  // Check network registration
  sendATCommand("AT+CREG?");

  // Check current operator
  sendATCommand("AT+COPS?");

  // Set SMS mode to text
  sendATCommand("AT+CMGF=1");
  //ATD+919988776655;

  // Print the results
  Serial.println("Initialization completed.");
}

void loop() {
  // Do nothing in the loop
}

void sendATCommand(const char* command) {
  mySerial.println(command);
  delay(500);
  
  while (mySerial.available()) {
    char c = mySerial.read();
    Serial.write(c);
  }
  
  Serial.println();
}


/*
#include<LiquidCrystal.h>   
LiquidCrystal LCD(8,9,10,11,12,13);

#define CLUTCH A2
#define B1 4//BUTTON 1
#define B2 3  //BUTTON 2
#define M1 6// RELAY FOR FORWARD
#define M2 5  //RELAY FOR BACKWARD

 

unsigned int a=0,b=0,c=0,d=0,e=0,f=0;
unsigned int A=0,VALA=1,VALB=0;
int AVALA=0,AVALB=0,AVALC=0,AVALD=0,AVALE=0,AVALG=1,count=0;
int Gpsdata;               // for incoming serial data
  unsigned int finish =0;  // indicate end of message
  unsigned int pos_cnt=0;  // position counter
  unsigned int lat_cnt=0;  // latitude data counterij.~~
  unsigned int log_cnt=0;  // longitude data counter
  unsigned int flg    =0;  // GPS flag
  unsigned int com_cnt=0;  // comma counter
  char lat[20];            // latitude array
  char lg[20];             // longitude array
void gsm_send();
void Receive_GPS_Data();



void setup() {
  // put your setup code here, to run once:
  
 
 
  Serial.begin(9600);
 
  
}

void loop() {
  // put your main code here, to run repeatedly:
Receive_GPS_Data();
  Serial.print("hiii");
   gsm_send();
   delay(1000);

}
void gsm_send()
{  
LCD.clear();
LCD.setCursor(0,0);
LCD.print("sending sms1........................");
delay(500);
Serial.print("AT");         // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CMGF=1");  // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CNMI=2,2,2,0");     // SIM CARD READY CHECK
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("AT+CMGS=");   // SMS SEND FUNCTION
delay(100);  delay(100);
Serial.print('"');
delay(100);  delay(100);
Serial.print("6381516328");
delay(100);  delay(100);
Serial.print('"');   
delay(100);  delay(100);    
Serial.write(13);
delay(1000);
//Serial.print("SAFETY ALERT");
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);

Serial.print("LAT=");
delay(100);
Serial.print(lat);
delay(100);  delay(100);
Serial.write(13);           // ENTER
delay(1000);
Serial.write(10);           // NEW LINE
delay(1000);
Serial.print("LOG=");
delay(100);
Serial.print(lg);
delay(600);
Serial.write(13);
delay(100);
//Serial.write(10);           // NEW LINE
//delay(100);  delay(100);
//delay(1000);
Serial.write(26);        // CTRL+Z
delay(100);  delay(100);
LCD.setCursor(0,0);
delay(600);   
LCD.print("   COMPLETED     ");
}
//*******************
// GPS VALUE
//*******************
void Receive_GPS_Data()
{
  LCD.clear();
while(finish==0){
while(Serial.available()>0)
{
  Gpsdata = Serial.read();
flg = 1;
if( Gpsdata=='$' && pos_cnt == 0)   // finding GPRMC header
pos_cnt=1;
if( Gpsdata=='G' && pos_cnt == 1)
pos_cnt=2;
if( Gpsdata=='P' && pos_cnt == 2)
pos_cnt=3;
if( Gpsdata=='R' && pos_cnt == 3)
pos_cnt=4;
if( Gpsdata=='M' && pos_cnt == 4)
pos_cnt=5;
if( Gpsdata=='C' && pos_cnt==5 )
pos_cnt=6;
if(pos_cnt==6 &&  Gpsdata ==','){   // count commas in message
com_cnt++;
flg=0;
}

if(com_cnt==3 && flg==1){
if(lat_cnt<10)
{
lat[lat_cnt++] =  Gpsdata;  
}// latitude
flg=0;
}

if(com_cnt==5 && flg==1){
if(log_cnt<12)
{
lg[log_cnt++] =  Gpsdata;         // Longitude

}
flg=0;
}

if( Gpsdata == '*' && com_cnt >= 5){
com_cnt = 0;                      // end of GPRMC message
lat_cnt = 0;
log_cnt = 0;
flg     = 0;
finish  = 1;
}
}
}
}
*/