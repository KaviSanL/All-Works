// C++ code
//
int i = 0;

int brightness = 0;

void setup()
{
  pinMode(9, OUTPUT);
}

void loop()
{
  for (i = 0; i <= 255; i += 5) {
    analogWrite(9, brightness);
    delay(30); // Wait for 30 millisecond(s)
  }
  for (i = 255; i >= 0; i -= 5) {
    analogWrite(9, brightness);
    delay(30); // Wait for 30 millisecond(s)
  }
}