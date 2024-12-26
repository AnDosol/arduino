
/*
  2023, 11, 23
  송명규
  010-2402-4398
  mgsong@hanmail.net 

  V1.0 == 2023, 11, 23 = 최초작성
  V1.2 == 2023, 11, 28 = 소프트웨어 시리얼 포트 추가 = 더조은컴퓨터학원 에서
  V1.4 == 2023, 11, 29 = ESP32, LCD 출력 추가
  V1.5 == 2023, 12, 26 = Adafruit사 SSD1306 + GFX Library에 I2C OLED 출력 추가
  V1.6 == 2023, 12, 27 = U8G2 Library에 I2C OLED 출력 추가
  V1.7 == 2024, 01, 15 = ARM용 printf 포팅
  V1.8 == 2024, 01, 16 = 모든 MCU 및 디바이스용으로 대폭 보강 및 기능 추가
                       = 특히 부동소수점 표시 기능 보강 = 소수점 8자리까지 표시되게 보강 함
                       = 통합 라이브러리로 운용 함
  V1.9 == 2024, 01, 23 = ARM I2C LCD, OLED 출력 추가
          2024, 01, 25 = ST7920 128x64 동작모드 추가
  V2.0 == 2024, 02, 08 = 병렬방식 Char Type LCD 출력 추가
  V2.2 == 2024, 06, 03 = Arduino I2C LCD 수정 및 추가
  V2.4 == 2024, 07, 22 = RPi Mode 
  V2.5 == 2024, 12, 03 = Rpi I2C LCD 및 UART 출력기능 추가 및 수정
*/

/*
 * --------------------------------------------------------------
 * Perform simple printing of formatted data
 * Supported conversion specifiers: 
 *      d, i     signed int
 *      u        unsigned int
 *      ld, li   signed long
 *      lu       unsigned long
 *      f        double
 *      c        char
 *      s        string
 *      %        '%'
 * Usage: %[conversion specifier]
 * Note: This function does not support these format specifiers: 
 *      [flag][min width][precision][length modifier]
 * --------------------------------------------------------------
 */

#ifndef __MY_ARM_printf_LIB__
#define __MY_ARM_printf_LIB__

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>


#define SERIAL_PRINTF_MAX_BUFF      255
#define F_PRECISION                 6 // 소수점 자리수 설정 6

#if (ESP32_Mode || R_PI_Mode || Arduino_Mode || Mcu_8Bit_Mode)  // 2024, 01, 16 추가   
  #if U8G2_G_LCD || U8G2_OLED
      //int cnt = 1234;
       
  #elif SSD1306_I2C_OLED //  Adafruit사 SSD1306 + GFX 라이브러리 사용
      #define SCREEN_WIDTH 128 // OLED display width, in pixels
      #define SCREEN_HEIGHT 64 // OLED display height, in pixels
      #define OLED_RESET -1                  // Wemos TTGO ESP8266 with 0.91 Inch OLED version A type
      #define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
      int cnt = 1234;

  #elif SW_Uart_mode
    #define Rx_Pin  11 // A4
    #define Tx_Pin  10 // A5
    #define rx_pin_init(pin) pinMode(Rx_Pin, INPUT);
    #define tx_pin_init(pin) pinMode(Tx_Pin, OUTPUT);
    #define SW_Uart 100 
    SoftwareSerial My_Port(Rx_Pin, Tx_Pin);
    #define sw_uart_init(bps) My_Port.begin(bps)
    
  #elif HW_Uart_mode  // 2024, 6, 3, IoT 8기 수정
      #define  HW_Uart  1        
      #define  ESP32    2
      extern char out_mode = HW_Uart;

  #elif R_PI_Mode // 2024, 7, 22 추가
      // pi gpio Lib
      #include <pigpio.h>     
  #endif

#elif ARM_Mode  // 2024, 01, 15 추가
  #include <stdio.h>
  #include <string.h>
  #include <stdlib.h>
  //#include "stm32f1xx_hal.h"
  #include "stm32l1xx_hal.h"
  #include "main.h"
      uint16_t cnt_16 = 1234;
      float song_pi = 23.56789012;

    #if UART
       #include "usart.h"
    #elif I2C_LCD_IF // 2024, 01, 23 추가
       #include "i2c.h"
       #include "My_ARM_I2C_LCD_V2_0.h"
       extern I2C_HandleTypeDef hi2c1;  // change your handler here accordingly
       #define SLAVE_ADDRESS_LCD 0x4E // change this according to ur setup
    #elif U8G2_OLED || U8G2_G_LCD
       #include "u8g2/u8g2.h"
       struct OLED_G
        {
    	  char x;
    	  char y;
    	  char disx2;
        }O_Led = {0,0,0};
       struct OLED_G *oled = &O_Led;
    #elif SSD1306_I2C_OLED

    #endif
#endif

extern void dev_printf(const char *fmt, ...);
extern void dev_printf_int(const char *fmt, ...);

void dev_printf_int(const char *fmt, ...) {
  /* Buffer for storing the formatted data */
  char buf[SERIAL_PRINTF_MAX_BUFF];
  memset(buf, 0, SERIAL_PRINTF_MAX_BUFF);
  /* pointer to the variable arguments list */
  va_list pargs;
  /* Initialise pargs to point to the first optional argument */
  va_start(pargs, fmt);
  /* create the formatted data and store in buff */
  vsnprintf(buf, SERIAL_PRINTF_MAX_BUFF, fmt, pargs);
  va_end(pargs);

#if (ESP32_Mode || R_PI_Mode || Arduino_Mode || Mcu_8Bit_Mode)    
    #if U8G2_G_LCD || U8G2_OLED  // u8g2 LIB
       u8g2.print(buf);
    #elif SSD1306_I2C_OLED  // SSD1306 LIB
       display.print(buf);
    #elif SW_Uart
       My_Port.print(buf);    
    #elif HW_Uart  // 2024, 06, 03 수정  = ioT 8기 수정
      {
       if(out_mode == HW_Uart || out_mode == ESP32) Serial.print(buf);
      }
    #elif Arduino_i2c_Char_LCD // 2024, 06, 03 추가  = ioT 8기 수정        
      {
        lcd.print(buf); // 2024, 06, 03 추가        
      }
    #elif R_PI_Mode_Uart // 2024, 07, 22 추가   
     {
	    serWrite(My_port, buf, sizeof(buf)-1); 	 
	   }   
    #elif R_PI_Mode_i2c_Char_LCD // 2024, 12, 3 수정
     {
       typeln(buf);
     }   
    #endif
#elif ARM_Mode  // 2024, 01, 15 추가
   #if UART  // 2024, 01, 23 추가
      #if USART_Ch_1_EN
         HAL_UART_Transmit(&huart1, (uint8_t *)&buf, strlen(buf), 0x1000);
      #endif

      #if USART_Ch_2_EN
         HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0x1000);
      #endif

      #if USART_Ch_3_EN
         HAL_UART_Transmit(&huart3, (uint8_t *)&buf, strlen(buf), 0x1000);
      #endif
   #elif I2C_LCD_IF // 2024. 01, 23 추가
          lcd_str(buf);
   #elif U8G2_OLED || U8G2_G_LCD   // 2024. 01, 23 추가
          (oled -> disx2 == 0) ? u8g2_DrawStr(&u8g2, oled -> x, oled -> y, buf)
                		      : u8g2_DrawStrX2(&u8g2, oled -> x, oled -> y, buf);
          u8g2_SendBuffer(&u8g2);
   #elif  Char_LCD  // 2024, 02, 08 추가
          lcd_str(buf);
        
   #elif SSD1306_I2C_OLED

   #endif
#endif
}

void dev_printf(const char *fmt, ...) {
  /* buffer for storing the formatted data */
  char buf[SERIAL_PRINTF_MAX_BUFF];
  memset(buf, 0,SERIAL_PRINTF_MAX_BUFF);
     
  char *pbuf = buf;
 
  /* pointer to the variable arguments list */
  va_list pargs;
  
  /* Initialise pargs to point to the first optional argument */
  va_start(pargs, fmt);
  /* Iterate through the formatted string to replace all 
  conversion specifiers with the respective values */
  while(*fmt) {
    if(*fmt == '%') {
      switch(*(++fmt)) {
        case 'd':             
        case 'i': 
          pbuf += sprintf(pbuf, "%d", va_arg(pargs, int));
          break;
        case 'u': 
          pbuf += sprintf(pbuf, "%u", va_arg(pargs, unsigned int));
          break;
        case 'l': 
          switch(*(++fmt)) {
            case 'd':              
            case 'i':             
              pbuf += sprintf(pbuf, "%ld", va_arg(pargs, long));
              break;
            case 'u': 
              pbuf += sprintf( pbuf, "%lu", va_arg(pargs, unsigned long));
              break;
           }
          break;
        case 'f': // 2024, 01, 16 수정             
             #if (ESP32_Mode || Arduino_Mode || Mcu_8Bit_Mode)
                pbuf += strlen(dtostrf( va_arg(pargs, double), 2, F_PRECISION, pbuf)); //2 = 공백, F_PRECISION = 소수점 자리수, org .1자리                   
             
             #elif (ARM_Mode  || R_PI_Mode) // 2024, 01, 15 추가, 2024, 07, 22 수정 
        	    pbuf += sprintf(pbuf, "%.6f",va_arg(pargs, double)); // 2024, 01, 16 추가                               
             #endif
        break;
        
        case 'c':
          *(pbuf++) = (char)va_arg(pargs, int);
          break;
        case 's': 
          pbuf += sprintf(pbuf, "%s", va_arg(pargs, char *));
          break;
        case '%':
          *(pbuf++) = '%';
          break;
        default:
          break;
      }
    } else {
      *(pbuf++) = *fmt;
    }
    
    fmt++;
  }
  
  *pbuf = '\0';
  
  va_end(pargs);

 //202, 01, 16 추가 및 수정
#if (ESP32_Mode || R_PI_Mode || Arduino_Mode || Mcu_8Bit_Mode)
    #if U8G2_G_LCD || U8G2_OLED  // u8g2 LIB
       u8g2.print(buf);
    #elif SSD1306_I2C_OLED  // SSD1306 LIB
       display.print(buf);
    #elif SW_Uart
       My_Port.print(buf);
    #elif HW_Uart  // 2024, 06, 03 수정  = ioT 8기 수정
      {
       if(out_mode == HW_Uart || out_mode == ESP32) Serial.print(buf);
      }
    #elif Arduino_i2c_Char_LCD // 2024, 06, 03 추가  = ioT 8기 수정    
      {    
        lcd.print(buf); // 2024, 06, 03 추가        
      }
    #elif R_PI_Mode_Uart // 2024, 07, 22 추가   
     {
	     serWrite(My_port, buf, sizeof(buf)-1); 	 
	   }
    #elif R_PI_Mode_i2c_Char_LCD // 2024, 12, 3 수정
     {
       typeln(buf);
     }      
    #endif    
#elif ARM_Mode  // 2024, 01, 15 추가
   #if UART  // 2024, 01, 23 추가
      #if USART_Ch_1_EN
         HAL_UART_Transmit(&huart1, (uint8_t *)&buf, strlen(buf), 0x1000);
      #endif

      #if USART_Ch_2_EN
         HAL_UART_Transmit(&huart2, (uint8_t *)&buf, strlen(buf), 0x1000);
      #endif

      #if USART_Ch_3_EN
         HAL_UART_Transmit(&huart3, (uint8_t *)&buf, strlen(buf), 0x1000);
      #endif
   #elif I2C_LCD_IF    // 2024. 01, 23 추가
           lcd_str(buf);
   #elif U8G2_OLED || U8G2_G_LCD  // u8g2 LIB     // 2024. 01, 23 추가
           (oled -> disx2 == 0) ? u8g2_DrawStr(&u8g2, oled -> x, oled -> y, buf)
        		                    : u8g2_DrawStrX2(&u8g2, oled -> x, oled -> y, buf);
           u8g2_SendBuffer(&u8g2);
   #elif Char_LCD // 2024, 02, 08 추가
         lcd_str(buf);

   #elif SSD1306_I2C_OLED

   #endif
#endif
}

#endif

