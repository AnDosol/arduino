
/*
  2023, 12, 28
  송명규
  010-2402-4398
  mgsong@hanmail.net 

  V1.0 == 2023, 04, 23 = 최초작성, IF 통합, OLED, G-LCD통합
*/


#ifndef __MY_Arudino_U8G2_LIB__
#define __MY_Arduino_U8G2_LIB__

// U8g2lib.h 에 선언 됨
#if ST7920_8Bit_IF   
   //G-LCD용 ST7920 128 x 64 == PSB 15번 Pin = VCC == 5V, 16번 Pin : NC, Only GPIO Pin Control
   //SetPin_8Bit(getU8x8(), d0, d1, d2, d3, d4, d5, d6, d7, enable, cs, dc, reset);
   #define RS 8
   #define EN 9
   //#define RET == 미사용
   // RW pin = H/W상에서 GND로 연결 
   U8G2_ST7920_128X64_F_8080 u8g2(U8G2_R0, 14,15,2,3,4,5,6,7, /*en=*/ 9, /*cs=*/ U8X8_PIN_NONE, /*RS=*/ 8, /*ret pin7*/U8X8_PIN_NONE);//, /*RW=*/12, U8X8_PIN_NONE);	// Remember to set R/W to 0 
#elif ST7920_SW_SPI 
   // G-LCD용 ST7920 128 x 64 == PSB 15번 Pin = GND == 0V, 16번 Pin : NC == SPI IF
   #define SW_CLK   2
   #define SW_Data  3
   #define SW_CS    4   
       // SPI : EN 6번 Pin = clk, R/W 5번 Pin = Data(MOSI), RS 4번 Pin = CS 
   U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 9, /* data=*/ 12, /* CS=*/ 8, /* reset=*/ U8X8_PIN_NONE);
#elif ST7920_HW_SPI 
   // G-LCD용 ST7920 128 x 64 == PSB 15번 Pin = GND == 0V, 16번 Pin : NC == SPI IF
   #define HW_CS   2
   //#define HW_Ret  3
   U8G2_ST7920_128X64_F_HW_SPI u8g2(U8G2_R0, /* CS=*/ 10, /* reset=*/ 8);
#elif KS0108_8Bit_IF 
   // G-LCD용 KS0108 128 x 64 == 15번 Pin : CS1, 16번 Pin == CS2. Only GPIO Pin Control
   //u8x8_SetPin_KS0108(getU8x8(), d0, d1, d2, d3, d4, d5, d6, d7, enable, dc, cs0, cs1, cs2, reset); 
   #define RS   2
   #define EN  3
   #define CS1   2
   #define CS2  3
   //#define RET   2
   U8G2_KS0108_128X64_F u8g2(U8G2_R0, 14,15,2,3,4,5,6,7, /*enable=*/ 9, /*dc=*/ 8, /*cs0=*/ 10, /*cs1=*/ 11, /*cs2=*/ U8X8_PIN_NONE, /* reset=*/  U8X8_PIN_NONE); 	// Set R/W to low!
#elif HW_I2C_OLED 
   // HW I2C 방식 == OLED용   
   U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#elif SW_I2C_OLED 
   // SW I2C 방식 == == OLED용
   #define SW_CLK   2
   #define SW_Data  3
   U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* reset=*/ 8);
#elif ESP32_SW_I2C_OLED 
   // ESP32 용 == OLED IF
   #define SW_CLK   2
   #define SW_Data  3
   U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 16, /* data=*/ 17, /* reset=*/ U8X8_PIN_NONE);   // ESP32 Thing, pure SW emulated I2C
#elif ESP32_HW_I2C_OLED 
   U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ 16, /* data=*/ 17);   // ESP32 Thing, HW I2C with pin remapping
#elif SW_SPI4_OLED 
   // SW SPI 4 방식 == OLED용
   #define SW_CS    2
   #define SW_CLK   3
   #define SW_Data  4
   #define SW_DC    5
   //#define RET      6
   U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
#elif HW_SPI4_OLED 
   // HW SPI 4 방식 == OLED용
   #define SW_CS    2
   #define SW_CLK   3
   #define SW_Data  4
   #define SW_DC    5
   //#define RET      6
   U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);
#elif SW_SPI3_OLED 
   // SW SPI 3 방식 == OLED용
   #define SW_CS    2
   //#define RET      6   
   U8G2_SSD1306_128X64_NONAME_F_3W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* reset=*/ 8);
#elif HW_SPI3_OLED 
   // HW SPI 3 방식 == OLED용
   #define SW_CS    2
   //#define RET      6  
   U8G2_SSD1306_128X64_NONAME_F_3W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 10, /* reset=*/ 8);
#endif


void my_u8g2_init()
{
  u8g2.begin();
  u8g2.enableUTF8Print();		// enable UTF8 support for the Arduino print() function   
  
  // u8g2.h 참고 == Font에 대해선
  //u8g2.setFont(u8g2_font_unifont_t_korean1); // Arduino korea2 font는 미 지원 함  
  u8g2.setFont(u8g2_font_ncenB08_tr);	
  u8g2.setFontDirection(0);
  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setCursor(0, 0);
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000); 
}

#endif


