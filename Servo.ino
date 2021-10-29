#include <Servo.h>
Servo servo1;
int angulo = 90;
int salto = 3;
int Eje_X = A1;
int Eje_Y = A2;
int boton = 4, LED = 12;


void setup() {
  // put your setup code here, to run once:
  servo1.attach(6);
  pinMode(boton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (! digitalRead(boton))
  {
    digitalWrite(LED, HIGH);
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  int p =analogRead(A1);
  if (p < 400)
  {
    angulo = angulo - salto;
  } 
     
  else if (p > 600)
  {
    angulo = angulo + salto;
  } 
     
  servo1.write(angulo);
  delay(50);
}
