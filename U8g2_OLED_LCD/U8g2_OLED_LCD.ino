// sys Lib
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Arduino EXT Lib
// Arduino timer2 Lib

#include <MsTimer2.h>
// arduino i2c LCD Lib

#include <LiquidCrystal_I2C.h>
// Arduino U8G2 OLED Lib

#include <U8x8lib.h>
#include <U8g2lib.h>
#include <MUIU8g2.h>

// My Lib
// Mult Func Board Pin Map define
#include "My_Mult_Func_BD_Pin_define_Lib.h"
// My GPIO Lib
#include "My_Arduino_GPIO_Lib_V1_8.h"
// Fnd == 74hc595
#define FND_595_IF  1
#include "My_Arduino_FND_Lib_V2_5.h"
// i2C LCd My Lib
#include "My_Arduino_LiqCry_I2C_LCD_Lib_V1_3.h"
// U8g2 OLED
#define HW_I2C_OLED   1
#include "My_Arduino_U8G2_Lib_V1_2.h"


// dev printf
#define Arduino_Mode   1
#define Arduino_i2c_Char_LCD   2
//#include "My_MCU_Printf_Lib_V2_5.h"

struct _CNT_
{
  int cnt16;
  int t_loop;
}count = {1234, 0};

struct _CNT_ *cnt = &count; 

struct _FLAG_
{
  char led_flag;
}flag = {0};

struct _FLAG_ *fg = &flag;

char d_buf[40];

void time_irq()
{
  // timer interrupt call 백 함수
  (cnt -> t_loop > 200) ? cnt -> t_loop = 0,   
                          cnt -> cnt16++,
                          (*fg).led_flag = 1   
                        : cnt -> t_loop++;
  if(cnt -> cnt16 > 2000) cnt ->cnt16 = 1234;    
  fnd_595_out(cnt ->cnt16); //multi funcition fnd
  //Serial.println("1");
}

void setup() {
  
  MsTimer2::set(1000, time_irq);
  MsTimer2::start();
  // put your setup code here, to run once:
  // LED GPIO SET
  for(int k =0; k <= 3; k++) pinMode(M_LED[k], OUTPUT);
  Led_Byte_Out(0xff); 

  // FND OUTPUT
  pinMode(LATCH, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  // Uart Set
  Serial.begin(115200);
   // I2C LCD INIT
  lcd_init();

 // OLED Init
 my_u8g2_init();
 // lcd disPLAY

 print_xy_str(0, 0, "Odd UP Cnt= ");
 print_xy_str(0, 1, "Env DN Cnt= ");

 // u8g2 oled
 u8g2.clearBuffer();         // clear the internal memory
 u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
 u8g2.setFontDirection(0);
 u8g2.drawStr(0,10,"Hello World!");
 //u8g2.drawStrX2(0,10,"Hello World!");  // write something to the internal memory
 u8g2.setCursor(8, 20);
 u8g2.print("dosol"); 
 u8g2.sendBuffer();
}

 

void loop() {
  
  sprintf(d_buf, "%d", cnt->cnt16);
  print_xy_str(11, 0, d_buf);
  sprintf(d_buf, "%d", (10000 - cnt->cnt16));
  print_xy_str(11, 1, d_buf);
  // put your main code here, to run repeatedly:
  cnt->cnt16 > 9999 ? (cnt->cnt16 = 0) : cnt->cnt16++;
  delay(1000);

u8g2.setCursor(2, 40);
u8g2.print(d_buf); 
u8g2.sendBuffer();

}