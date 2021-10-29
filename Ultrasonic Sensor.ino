long distancia;
long tiempo;

void setup() {
  Serial.begin(9600);
  pinMode(53, OUTPUT);
  pinMode(52, INPUT);
}

void loop() {
  digitalWrite(53, LOW);
  delayMicroseconds(5);
  digitalWrite(53, HIGH);
  delayMicroseconds(10);
  tiempo = pulseIn(52, HIGH);
  distancia = int(0.017*tiempo);
  Serial.println("Distancia ");
  Serial.println(distancia);
  Serial.println(" cm");
  delay(1000);
}