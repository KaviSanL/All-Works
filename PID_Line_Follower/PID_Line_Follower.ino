// L298N motor driver pin connections
#include<L298N.h>
#define ENA 9
#define IN1 4
#define IN2 3
#define ENB 10
#define IN3 6
#define IN4 7

// Sensor threshold values
int threshold[6];

// PID control constants
float Kp = 0.0006;
float Ki = 0.0001;
float Kd = 10;

// Line following speed
int lfspeed = 200;

// Variables for PID control
int I = 0;
int previousError = 0;

// Function prototypes
void linefollow();
void calibrate();

void setup()
{
  Serial.begin(9600);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
}

void loop()
{
  while (digitalRead(11)) {}
  delay(1000);
  calibrate();
  while (digitalRead(12)) {}
  delay(1000);

  while (1)
  {
    if (analogRead(1) > threshold[1] && analogRead(5) < threshold[5])
    {
      analogWrite(ENA, 0);
      analogWrite(ENB, lfspeed);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else if (analogRead(5) > threshold[5] && analogRead(1) < threshold[1])
    {
      analogWrite(ENA, lfspeed);
      analogWrite(ENB, 0);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    else if (analogRead(3) > threshold[3])
    {
      linefollow();
    }
  }
}

void linefollow()
{
  int error = (analogRead(2) - analogRead(4));
  int PIDvalue = Kp * error + Ki * I - Kd * (error - previousError);
  previousError = error;
  I += error;

  int lsp = lfspeed - PIDvalue;
  int rsp = lfspeed + PIDvalue;

  if (lsp > 255) {
    lsp = 255;
  }
  if (lsp < 0) {
    lsp = 0;
  }
  if (rsp > 255) {
    rsp = 255;
  }
  if (rsp < 0) {
    rsp = 0;
  }

  analogWrite(ENA, lsp);
  analogWrite(ENB, rsp);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void calibrate()
{
  for (int i = 1; i < 6; i++)
  {
    int minVal = analogRead(i);
    int maxVal = analogRead(i);

    for (int j = 0; j < 3000; j++)
    {
      int val = analogRead(i);
      if (val < minVal)
      {
        minVal = val;
      }
      if (val > maxVal)
      {
        maxVal = val;
      }
    }

    threshold[i] = (minVal + maxVal) / 2;
    Serial.print(threshold[i]);
    Serial.print("   ");
  }
  Serial.println();
}
