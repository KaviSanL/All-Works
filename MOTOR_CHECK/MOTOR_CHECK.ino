int in1 = 2;
int in2 = 4;
int enA = 3;
int in3 = 5;
int in4 = 7;
int enB = 6;
void setup() {
  pinMode(enA,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(enB,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
  digitalWrite(enA,100);
  digitalWrite(enB,100);
  // put your main code here, to run repeatedly:

}
