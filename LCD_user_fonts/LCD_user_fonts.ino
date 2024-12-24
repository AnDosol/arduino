#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// https://maxpromer.github.io/LCD-Character-Creator/
// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar[] = {
  B00100,
  B00100,
  B11111,
  B00100,
  B00100,
  B00100,
  B00100
};

byte customChar1[] = {
  B11011,
  B11011,
  B00000,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011
};

void setup() {
  lcd.begin();
  lcd.createChar(0, customChar);
  lcd.createChar(1, customChar1);
  lcd.home();
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.write(0);
  lcd.setCursor(0, 1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);
  lcd.write(1);  
}
void loop() { }