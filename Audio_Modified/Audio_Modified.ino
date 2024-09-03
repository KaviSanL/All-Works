#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#define ctsPin 4 


// Use pins 2 and 3 to communicate with DFPlayer Mini
static const uint8_t PIN_MP3_TX = 2; // Connects to module's RX
static const uint8_t PIN_MP3_RX = 3; // Connects to module's TX
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
#include <Keypad.h>


const byte ROWS = 3; //four rows
const byte COLS = 3; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  
};
byte rowPins[ROWS] = { 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = { 8, 7, 6}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



// Create the Player object
DFRobotDFPlayerMini player;

void setup() 
{


  // Init USB serial port for debugging
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);
  //ultra
  
 pinMode(ctsPin, INPUT);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");

    // Set volume to maximum (0 to 30).
    player.volume(30);

  } 
  else
 {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }
    delay(500);
}

void loop() 
{
      int ctsValue = digitalRead(ctsPin); 
      if (ctsValue == HIGH)
        {  
           Serial.println("Touched");
           player.volume(30);
           player.play(1);
           delay(11000);

        }  

  
  
   char customKey = customKeypad.getKey();
  
  if (customKey)
  {
    Serial.println(customKey);
    if(customKey == '1')
    {


    // Set volume to maximum (0 to 30).
    player.volume(30);
    player.play(2);
    
    
    }
    else if(customKey == '2')
    {
       player.volume(30);
    player.play(3);
    
   
    }
     else if(customKey == '3')
    {
       player.volume(30);
    player.play(4);
    
    
    }
    else if(customKey == '4')
    {
       player.volume(30);
    player.play(5);
    
    
    }
    else if(customKey == '5')
    {
       player.volume(30);
    player.play(6);
    
    
    }
    else if(customKey == '6')
    {
       player.volume(30);
    player.play(7);
    
    
    }
    else if(customKey == '7')
    {
       player.volume(30);
    player.play(8);
    
    
    }
    else if(customKey == '8')
    {
       player.volume(30);
    player.play(9);
    
    
    }
    else if(customKey == '9')
    {
       player.volume(30);
    player.play(10);
    
    
    }

     


  }

}
