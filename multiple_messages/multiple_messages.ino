void setup()
{
  pinMode(11,OUTPUT);
  pinMode(12,INPUT);
  digitalWrite(11,0);
  Serial.begin(9600);
}
int buttonVal=0;
void loop()
{
  buttonVal=digitalRead(12);
  Serial.println(buttonVal);
  if(buttonVal==1)
  {
    digitalWrite(11,1);
    delay(500);
  }
    else
    {
      
    digitalWrite(11,0);
    delay(500);
  }
}
