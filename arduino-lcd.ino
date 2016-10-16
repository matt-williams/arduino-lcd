#include <SoftwareSerial.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7, 8);
SoftwareSerial serial2(10, 11);

String lines[2] = {"    [matrix]", ""};
int scrolls[2] = {0, 0};
bool newLine = false;
bool changed = true;

void setup() {
  Serial.begin(9600);

  pinMode(10, INPUT);
  pinMode(11, OUTPUT);
  serial2.begin(9600);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.noAutoscroll();
}

unsigned long nextMillis = 0;

void loop() {
  if (serial2.available() > 0) {
    char c = serial2.read();
    Serial.print(c);
    if ((c == '\r') || (c == '\n')) {
      newLine = true;
    } else {
      if (newLine) {
        lines[0] = lines[1];
        lines[1] = "";
        scrolls[0] = scrolls[1];
        scrolls[1] = -15;
        newLine = false;
      }
      lines[1] += String(c);
      changed = true;
    }
  }
  if (millis() > nextMillis) {
    if ((lines[0].length() > 16) || (scrolls[0] < 0)) {
      if (scrolls[0] < (int)lines[0].length()) {
        scrolls[0]++;
      } else {
        scrolls[0] = -15;
      }
      changed = true;
    }
    if ((lines[1].length() > 16) || (scrolls[1] < 0)) {
      if (scrolls[1] < (int)lines[1].length()) {
        scrolls[1]++;
      } else {
        scrolls[1] = -15;
      }
      changed = true;
    }
    if (changed) {
      lcd.clear();
      lcd.setCursor(scrolls[0] < 0 ? -scrolls[0] : 0, 0);
      lcd.print(lines[0].substring(scrolls[0] < 0 ? 0 : scrolls[0], scrolls[0] + 16 < (int)lines[0].length() ? scrolls[0] + 16 : lines[0].length()));
      lcd.setCursor(scrolls[1] < 0 ? -scrolls[1] : 0, 1);
      lcd.print(lines[1].substring(scrolls[1] < 0 ? 0 : scrolls[1], scrolls[1] + 16 < (int)lines[1].length() ? scrolls[1] + 16 : lines[1].length()));
      changed = false;
    }
    nextMillis += 300;
  }
}
