#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //rs,en,d4,d5,d6,d7

byte grado[8] = 
{
0b00001100,
0b00010010,
0b00010010,
0b00001100,
0b00000000,
0b00000000,
0b00000000,
0b00000000
};

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.createChar(1, grado);
  lcd.setCursor(0, 0);
  lcd.print("La cerveza se");
  lcd.setCursor(0, 1);
  lcd.print("toma a -3");  
  lcd.write(1);
}

void loop() {
  // put your main code here, to run repeatedly:

}
