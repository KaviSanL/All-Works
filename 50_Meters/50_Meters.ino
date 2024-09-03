#define in1 3
#define in2 4
#define in3 5
#define in4 6
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

}

void loop() {
  Forward;
  delay(20000);
  Left;
  delay(1000);
}
void Forward()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in3,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in4,LOW);
}
void Left()
{
  digitalWrite(in1,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in2,HIGH);
  digitalWrite(in4,LOW);
}
