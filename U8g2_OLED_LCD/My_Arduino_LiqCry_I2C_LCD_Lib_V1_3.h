
/*
  2023, 05, 16
  송명규
  010-2402-4398
  mgsong@hanmail.net 

  V1.0 == 2023, 05, 16 = 최초작성
  V1.2 == 2023, 11, 28 = 기능함수 추가 ==더조은컴퓨터학원 에서
  V1.3 == 2024, 05, 30 = 기능 추가 = LCD 초기화,  LCD test 함수 수정
*/

#ifndef __MY_Arudino_Liq_LCD_LIB__
#define __MY_Arduino_Liq_LCD_LIB__

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C  lcd(0x27, 16, 2); 

#define back_LED_ON   lcd.backlight()
#define back_LED_OFF  lcd.noBacklight()

#define __cursor_ON__   lcd.cursor()
#define __cursor_OFF__  lcd.noCursor()

#define Dis_ON      lcd.display()
#define Dis_OFF     lcd.noDisplay()

#define Cursor_ON   lcd.blink()
#define Cursor_OFF  lcd.noBlink() 

#define LCD_All_CLr lcd.clear() 
#define LCD_Home    lcd.home()

#define char_RR_Dis  lcd.leftToRight()
#define char_LF_Dis  lcd.rightToLeft()   

void Lcd_Test();

void gotoxy(char x, char y)
{
 // if(y == 1) y = 0;
 // else if(y == 2) y = 1;

  lcd.setCursor(x, y);
}

void one_line_clr(char x, char y)
{
  // max 4 x 20 char type LCD 사용할 수 있음
  lcd.setCursor(0, y);
  for(int i = 0; i<= x; i++)   
    lcd.print(' ');  
}

void set_char_clr(char x, char y)
{
  lcd.setCursor(x, y);
   lcd.print(' ');
}

void print_xy_str(char x, char y, char *buf)
{
   lcd.setCursor(x, y);
   while(*buf != '\0')
   {
     lcd.print(*buf);
     buf++;
   }
}

void lcd_str(char *buf)
{
  while(*buf != '\0')
   {
     lcd.print(*buf);
     buf++;
   }
}

void print_xy_char(char x, char y, char buf)
{
  lcd.setCursor(x, y);
   lcd.print(buf);
}

void print_xy_send(char x, char y, char buf)
{
  lcd.setCursor(x, y);
   lcd.write(buf);
}

void lcd_init()
{
  // 2024, 5, 30 추가 변경 
  lcd.begin();     //init() == 구번전 ;
  lcd.clear();
  lcd.backlight();
  lcd.home(); 
}

void LF_dis_move(char nb, int busy_d)
{
  for(char i = 0; i <= nb; i++)
   {
    lcd.scrollDisplayLeft();
    delay(busy_d);
   }
}

void RR_dis_move(char nb, int busy_d)
{
  for(char i = 0; i <= nb; i++)
   {
    lcd.scrollDisplayRight();
    delay(busy_d);
   }
}


// 2024, 05, 30 추가 및 변경
void Lcd_Test()
{
  print_xy_str(3,0,"Test 123@#$%");
  print_xy_str(1,1,"Song Moung gyu");
  
  Dis_ON;
  delay(1000);
  Dis_OFF;
  delay(1000);
  Dis_ON;
  delay(1000);
  Dis_OFF;
  delay(1000);
  Dis_ON;
  delay(1000);

  Cursor_ON;
  
   // display rr/LL Move 
  LF_dis_move(7, 200);
  delay(500);
  Cursor_OFF;
  delay(500);

  __cursor_ON__;
  RR_dis_move(7, 200);  
  delay(500);
  __cursor_OFF__;

  LCD_All_CLr;

  Cursor_ON;
  LCD_Home;
}

#endif

