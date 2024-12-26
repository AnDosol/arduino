


/*
  2023, 04, 23
  송명규
  010-2402-4398
  mgsong@hanmail.net 

  V1.0 == 2023, 04, 23 = 최초작성
  V1.2 == 2023, 08, 16 = d_in 추가
  V1.5 == 2023, 11, 16 = byte in arduino 함수 추가  = 더조은컴퓨터학원 에서
  V1.6 == 2024, 05, 28 = define, Enum 추가 == 한국직업능력교육원 IoT 8기 과정에서 추가
  V1.7 == 2024, 12, 10 = LED Byte Out 함수 및 LED Pin 배열변수 추가 == 한국직업능력교육원 AIoT 1기 과정에서 추가 
  V1.8 == 2024, 12, 12 = d_set, d_clr, d_chk, d_tg 함수추가 == 한국직업능력교육원 AIoT 1기 과정에서 추가   
*/

#ifndef __My_Arduino_LIB__
#define __My_Arduino_LIB__

#define  ON  1
#define  OFF 0
#define _ON  0
#define _OFF 1

// V1.6 추가 == IoT 8기 == 2024, 5, 28추가
#define LED_0  8 // 14
#define LED_1  9
#define LED_2  10
#define LED_3  11
#define LED_4  12
#define LED_5  13
#define LED_6  18  //A4
#define LED_7  19  //A5 

enum LED_
{
  led0 = 2,
  led1 = 3,
  led2 = 4,
  led3 = 5,
  led4 = 6,
  led5 = 7,
  led6 = 8,
  led7 = 9
}LED;
 
const int led_0 = A0;
const int led_1 = 12;
const int led_2 = 2;
const int led_3 = 3;
const int led_4 = 4;
const int led_5 = 5;
const int led_6 = 6;
const int led_7 = 7;

// 출력 핀 정의 = 핀번호는 PRj에 맞게 수정하여 사용하세요
struct GPIO_OUT
{
  const char OUT_Bit_0;
  const char OUT_Bit_1;
  const char OUT_Bit_2;
  const char OUT_Bit_3;
  const char OUT_Bit_4;
  const char OUT_Bit_5;
  const char OUT_Bit_6;
  const char OUT_Bit_7; 
}Out = {A0, 12, 2, 3, 4, 5, 6, 7}; // 핀 번호는 프로젝트에 맞게 수정하여 사용하세요

// 입력 핀 정의 = 핀번호는 PRj에 맞게 수정하여 사용하세요
struct GPIO_IN
{
  const char IN_Bit_0;
  const char IN_Bit_1;
  const char IN_Bit_2;
  const char IN_Bit_3;
  const char IN_Bit_4;
  const char IN_Bit_5;
  const char IN_Bit_6;
  const char IN_Bit_7;
}In = {A0, A1, A2, A3, A4, A5, 11, 12}; // 핀 번호는 프로젝트에 맞게 수정하여 사용하세요

extern char gpio_in_flag = 0;  // GPIO 입력이 있으면 1로 설정된다. = 외부 입력시. Key 압력체크용

// 구조체 포인터 선언
struct GPIO_OUT *Gpio_Out = &Out;
struct GPIO_IN  *Gpio_in = &In;

// 배열변수 선언 == 2024, 12, 10 추가 == AIOT 1기 추가
unsigned char LED_pin[10] = {m_led1, m_led2, m_led3, m_led4, LED_4, LED_5, LED_6, LED_7};


// MCU Mode Bit Control
#define bit_set(ADDRESS, BIT) (ADDRESS |= (1<<BIT)) // bit hi 
#define bit_clr(ADDRESS, BIT) (ADDRESS &= ~(1<<BIT)) // bit low
#define bit_chk(ADDRESS, BIT) (ADDRESS & (1<<BIT))  // bit chak
#define bit_tg(PORT, BIT) (PORT ^= (1<<BIT))  //bit 토글

// Arduino Macro
#define d_out(pin, value) digitalWrite(pin, value)
#define d_in(pin) digitalRead(pin)
// 2024, 12, 12 추가 == AIOT 1기
#define d_set(pin) digitalWrite(pin, HIGH) // 2024, 12, 12 추가 == AIOT1기
#define d_clr(pin) digitalWrite(pin, LOW) // 2024, 12, 12 추가 == AIOT1기
#define d_tg(pin)  digitalWrite(pin, !d_in(pin)) // 2024, 12, 12 추가 == AIOT1기
#define d_chk(pin) d_in(pin)


// Arduino API 사용시
void Byte_Out(unsigned char data)
{
 d_out(Gpio_Out -> OUT_Bit_0, data%2);     // bit 0 = lsb
 d_out(Gpio_Out -> OUT_Bit_1, data/2%2);   // bit 1 
 d_out(Gpio_Out -> OUT_Bit_2, data/4%2);   // bit 2 
 d_out(Gpio_Out -> OUT_Bit_3, data/8%2);   // bit 3 
 d_out(Gpio_Out -> OUT_Bit_4, data/16%2);  // bit 4  
 d_out(Gpio_Out -> OUT_Bit_5, data/32%2);  // bit 5
 d_out(Gpio_Out -> OUT_Bit_6, data/64%2);  // bit 6
 d_out(Gpio_Out -> OUT_Bit_7, data/128%2); // bit 7 = msb
}

// 2024, 12, 10 추가 == AIOT 1기 
// Led Byte out 
void Led_Byte_Out(unsigned char data)
{
  // 방법 2
  for(int k = 0; k<=7; k++)
   {
	  d_out(LED_pin[k], (data >> k) % 2);  
   }	  
 
 /*
 // 방법 1 	
 // byte in to bit out 
 d_out(LED_1, data%2);     // bit 0 = lsb
 d_out(LED_2, data/2%2);   // bit 1 
 d_out(LED_3, data/4%2);   // bit 2 
 d_out(LED_4, data/8%2);   // bit 3 
 d_out(LED_5, data/16%2);  // bit 4  
 d_out(LED_6, data/32%2);  // bit 5
 d_out(LED_7, data/64%2);  // bit 6
 d_out(LED_8, data/128%2); // bit 7 = msb
 */
 }

// 2024, 12, 23추가 == AIOT8기 
// 멀티펑션 보드용
void Led_4bit_Out(unsigned char data)
{
  // 방법 2
  for(int k = 0; k <= 3; k++)
   {
	  d_out(M_LED[k], (data >> k) % 2);  
   }	  
}   

// Arduino API 사용시
char Byte_In()
{
  char buf = 0x0e;

 buf =  d_in(Gpio_in -> IN_Bit_0);     // bit 0 = lsb
 buf |= d_in(Gpio_in -> IN_Bit_1)*2;   // bit 1 
 buf |= d_in(Gpio_in -> IN_Bit_2)*4;   // bit 2 
 buf |= d_in(Gpio_in -> IN_Bit_3)*8;   // bit 3 
 buf |= d_in(Gpio_in -> IN_Bit_4)*16;  // bit 4  
 buf |= d_in(Gpio_in -> IN_Bit_5)*32;  // bit 5
 buf |= d_in(Gpio_in -> IN_Bit_6)*64;  // bit 6
 buf |= d_in(Gpio_in -> IN_Bit_7)*128; // bit 7 = msb

 buf &= 0x0e; 
 while((PINC & 0x0e) != 0x0e)   
  {
    gpio_in_flag = 1;
  }

 return buf;
}

// 2023, 11, 20 추가 = 멀티펑션보드 
#define Bz_Off(Pin, Value)  d_out(Pin, Value) // bz off 
#define Bz_On(Pin, Value)   d_out(Pin, Value) // bz on 
 

#endif

// 사용법
// d_out(LED1, ON);
// bit_set(PORTD, 5);
// bit_clr(PORTD, 3);
// if(bit_chk(PIND, 3) == 0){  }
// bit_tg(PORTD, 0);
// delay(400);