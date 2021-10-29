#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //rs,en,d4,d5,d6,d7

void setup() {
  lcd.begin(16, 2); //fija el numero de caracteres y de filas
  lcd.setCursor(0, 0); //fija la posicion del cursior en el LCD
  lcd.print("   Contador");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis()/100); //devuelve el numero de milisegundos desde que la placa arduino empezo a correr el programa actual 
}
