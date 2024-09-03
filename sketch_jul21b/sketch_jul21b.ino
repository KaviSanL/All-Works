int ledPin=13;

void setup ()
{
}
void loop()
{
  while(ledPin>=8)
{
pinMode (ledPin, OUTPUT);
digitalWrite ( ledPin, HIGH);
delay (100);
digitalWrite (ledPin, LOW);
ledPin=ledPin-1;
    delay(100);
}
  ledPin=13;
}
