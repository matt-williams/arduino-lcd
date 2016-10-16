#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);

void setup() {
  lcd.begin(16, 2);
  lcd.clear();

  lcd.print("Hello, this is a test!");
}

void loop() {
  delay(300);
  lcd.scrollDisplayLeft();
}
