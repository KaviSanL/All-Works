int x_pin = A3;
int y_pin = A4;
void setup() {
  // put your setup code here, to run once:
pinMode(A0, INPUT);
pinMode(A1, INPUT);
Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:
int x_data = analogRead(A0);
int y_data = analogRead(A1);
Serial.print("x_data:");
Serial.print(x_data);
Serial.print("\t");
Serial.print("y_data:");
Serial.println(y_data);
delay(100);
}
