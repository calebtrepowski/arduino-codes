
#define PIN_ECHO 53
#define PIN_TRIGG 51

long distancia;
long tiempo;

void setup() {
  Serial.begin(9600);
  pinMode(PIN_TRIGG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
}

void loop() {
  digitalWrite(PIN_TRIGG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIGG, HIGH);
  delayMicroseconds(10);
  tiempo = pulseIn(PIN_ECHO, HIGH);
  distancia = int(0.017*tiempo);
  Serial.print("Distancia ");
  Serial.print(distancia);
  Serial.println(" cm");
  delay(100);
}
