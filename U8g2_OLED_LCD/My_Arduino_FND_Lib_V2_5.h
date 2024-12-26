/*
 my_Arduino_fnd.h
 *
 *  1995, 8, 22
 *     송명규
      010-2402-4398
     mgsong@hanmail.net
  
  V1.0 ==  아주아주 오래전에.... ??
  V1.1 ==  2022, 08, 27
  V1.2 ==  2022, 10, 12 = 정리, 조건식 추가
  V2.0 ==  2023, 08, 18  = 대폭수정 및 보강 = enum 방식 추가
  V2.2 ==  2023, 11, 07  = 수능시헌 보는날 기념으로 대폭수정 == 더조은컴퓨터아카데미 에서...
  V2.3 ==  2023, 11, 20  = 멀티펑션보드 74HC595 FND 함수 추가 == 더조은컴퓨터아카데미 에서...
  V2.4 ==  2024, 06, 21  = 버그수정, DP FLag 수정 보완 = Iot 8기
  V2.5 ==  2024, 12, 17  = LED Scan Device 추가 == AIOT 1기 
*/

#ifndef __My_Arduino_FND_LIB__  //{  // endif-1
#define __My_Arduino_FND_LIB__

// fnd font data
// K-공통
const unsigned char fnd_font[] =
{
   // 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   H,   L,   E,   o,   P,  F,
   0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x27,0x7f,0x6f,0x76,0x38,0x79,0x5c,0x73,0x71,
   // C,    d,    A,    u,    T,    r,   b,  blk
   0x39, 0x5e, 0x77, 0x1c, 0x44, 0x50, 0x7c, 0x00
};

// fnd E-Font maseg display
enum E_Font
{
  O = 0x0d,   //o display
  F = 0x0f,    // F display
  H = 0x0a,    // H   "
  L = 0x0b,    // L   "
  E = 0x0c,    // E   "
  P = 0x0e,    // P   "
  C = 0x10,    // C   "
  D = 0x11,    // d   "
  A = 0x12,    // A   "
  U = 0x13,    // u   "
  T = 0x14,    // t   "
  R = 0x15,    // r   "
  B = 0x16,    // b   "
  BLK = 0x00   // fnd blk display
}E_font;

enum pin_map{ // pin_map = 열거형 이름정의 + 열거형 변수 선언을 동시에 함 
  x1000 = 4, // d8
  x100  = 5,
  x10   = 6,
  x1    = 7  
}fnd_en_pin; // pin = 열거형 변수명 = main 에서 열거형 변수 선언 안 해도 됨
//pin_map = x1000;

struct FND_PIN_MAP{
  const char Fnd_A;  
  const char Fnd_B;
  const char Fnd_C;
  const char Fnd_D;
  const char Fnd_E;
  const char Fnd_F;
  const char Fnd_G;
  const char Fnd_Dp;  
}Fnd_Pin_Map = {8, 9, 10, 11, 12, 13, 18, 19};
struct FND_PIN_MAP *Fnd_Pin = &Fnd_Pin_Map;

void fnd_d_out(unsigned char data)
{
 d_out(Fnd_Pin -> Fnd_A, data%2);     // bit 0 = lsb
 d_out(Fnd_Pin -> Fnd_B, data/2%2);   // bit 1 
 d_out(Fnd_Pin -> Fnd_C, data/4%2);   // bit 2 
 d_out(Fnd_Pin -> Fnd_D, data/8%2);   // bit 3 
 d_out(Fnd_Pin -> Fnd_E, data/16%2);  // bit 4  
 d_out(Fnd_Pin -> Fnd_F, data/32%2);  // bit 5
 d_out(Fnd_Pin -> Fnd_G, data/64%2);  // bit 6
 d_out(Fnd_Pin -> Fnd_Dp, data/128%2); // bit 7 = msb
}

// 변수선언 
extern struct FND_V {
  char Scan; // 자리수 값 카운터 = 0b00010000;
  int  Fnd_Loop;
  char Dp_595_Digit;
}Fnd_Value = {0, 0, 0};
struct FND_V *Seg_V =  &Fnd_Value;

struct FLAG
{
  char Tg_Flag;
  char Tg_Flag_x1000;
  char Tg_Flag_x100;  
  char Tg_Flag_x1;
  char Dp_X1000_Flag;
  char Dp_X100_Flag;
  char Dp_X1_Flag;
  char Dp_flag;
}Flag_sts = {0,0,0,0,0,0,0,3};


#if COM_A // endif-2
   #if Digit_4  // endif-3
     #if En_font                
       void fnd_dis_en_font(char e_font1, char e_font2, char e_font3, char e_font4)          
     #elif Scan_Dev_Inc // 2024, 12, 17추가 = AIoT 1기       
       #define led_scan_pin  17  // A3 // 2024, 12, 17추가 = AIoT 1기
       void fnd_dev_dis_A_4(uint16_t d_buf, uint8_t led_buf) // 2024, 12, 17추가  
     #else       
       void fnd_dis_A_4(uint16_t d_buf)           
     #endif
        {
         #if Scan_Dev_Inc // 2024, 12, 17추가 = AIoT 1기
           Seg_V -> Scan = (Seg_V -> Scan > 5) ? 1 : Seg_V -> Scan + 1;  // 2024, 12, 17추가 = AIoT 1기
         #else 
           Seg_V -> Scan = (Seg_V -> Scan > 4) ? 1 : Seg_V -> Scan + 1;
         #endif

          // GPIO Pin으로 할 경우 예제 입니다.
          // 프로젝트에 맞게 수정하여 사용하세요
         // Seg_V -> Scan >>= 1;
         //if(Seg_V -> Scan == 0) Seg_V -> Scan = 0b00010000;          
         //(Seg_V -> Scan == 0) ? Seg_V -> Scan = 0b00001000 : Seg_V -> Scan >>= 1;

         switch((*Seg_V).Scan)
          {
           case 1:  // x1000                       
               #if Scan_Dev_Inc // 2024, 12, 17추가 = AIoT 1기
                  d_out(led_scan_pin, OFF); // 2024, 12, 17추가 = AIoT 1기                  
               #else // 2024, 12, 17추가 = AIoT 1기     
                  d_out(x1, OFF);
               #endif // 2024, 12, 17추가 = AIoT 1기  
                  #if Arduino_mode
                     #if En_font 
                       fnd_d_out(~fnd_font[e_font1]);
                      #else  
                       if(Flag_sts.Dp_X1000_Flag == 1) fnd_d_out((~fnd_font[d_buf/1000]) | 0x80); // dp ON data out                       
                       else fnd_d_out((~fnd_font[d_buf/1000]) & 0x7f); // dp off data out                       
                      #endif 
                  #elif MIC_mode
                       PORTD = ~fnd_font[d_buf/1000];
                  #endif
                  d_out(x1000, ON);
             break;

          case 2: // x100
          //case 0b00000100://2:  //x100
                  d_out(x1000, OFF);
                  #if Arduino_mode
                    #if En_font 
                       fnd_d_out(~fnd_font[e_font2]);
                    #else                                                                              
                       if(Flag_sts.Tg_Flag_x100 == 1) fnd_d_out((~fnd_font[d_buf%1000/100]) | 0x80); // dp on                   
                       else fnd_d_out((~fnd_font[d_buf%1000/100]) & 0x7f); // DP OFF + Data Out                                               
                    #endif 
                  #elif MIC_mode
                       PORTD = ~fnd_font[d_buf%1000/100];
                  #endif
                  d_out(x100, ON);
             break;
      
          case 3:  // x10
          //case 0b00000010://3:  // x10
                  d_out(x100, OFF);
                  #if Arduino_mode
                     #if En_font 
                       fnd_d_out(~fnd_font[e_font3]);
                      #else 
                       fnd_d_out(~fnd_font[d_buf%100/10]); // data out                       
                      #endif 
                  #elif MIC_mode
                       PORTD = ~fnd_font[d_buf%100/10];
                  #endif
                  d_out(x10, ON);
             break;

          case 4:   // x1 
          //case 0b00000001://4: // x1
                 d_out(x10, OFF);
                  #if Arduino_mode
                    #if En_font 
                       fnd_d_out(~fnd_font[e_font4]);
                    #else 
                        #if DP_X1 
                           if(Flag_sts.Tg_Flag_x1 == 1) fnd_d_out((~fnd_font[d_buf%10]) & 0x7f); // C-A : Dp ON + Data Out                       
                           else fnd_d_out((~fnd_font[d_buf%10]) | 0x80); // // C-A : Dp ON + Data Out                                              
                        #else
                          fnd_d_out(~fnd_font[d_buf%10]); // data out                        
                        #endif                        
                    #endif 
                  #elif MIC_mode
                       PORTD = ~fnd_font[d_buf%10];
                  #endif
                  d_out(x1, ON); 
             break;   

        #if Scan_Dev_Inc  
          case 5: // 2024, 12, 17추가 = AIoT 1기
                  // LED Data Out == Scan 방식
                  d_out(x1, OFF);
                  Led_Byte_Out(~led_buf); // 싱크방식이라서 Bit 반전해야 됨
                  d_out(led_scan_pin, ON);
             break;    
        #endif     
        }
      } //------------------------------------------------------------------
             
     void fnd_dis_A_gugudan(char dan, char gu, char mul)
      {
        Seg_V -> Scan = (Seg_V -> Scan > 4) ? 1 : Seg_V -> Scan + 1;

        switch((*Seg_V).Scan)
        {
          case 1: // x1000                 
                  d_out(x1, OFF);
                  #if Arduino_mode
                       fnd_d_out(~fnd_font[dan%10] & 0x7f); // data out                       
                  #elif MIC_mode
                       PORTD = ~(fnd_font[dan/1000] & 0x7f);
                  #endif
                  d_out(x1000, ON);
             break;

          case 2:  //x100
                  d_out(x1000, OFF);
                  #if Arduino_mode
                       fnd_d_out(~fnd_font[gu%10] & 0x7f); // data out                       
                  #elif MIC_mode
                       PORTD = ~(fnd_font[gu%10] & 0x7f);
                  #endif
                  d_out(x100, ON);
             break;
      
          case 3:  // x10
                  d_out(x100, OFF);
                  #if Arduino_mode
                       fnd_d_out(~fnd_font[mul/10]); // data out                       
                  #elif MIC_mode
                       PORTD = ~fnd_font[mul/10];
                  #endif
                  d_out(x10, ON);
             break;

          case 4: // x1
                 d_out(x10, OFF);
                  #if Arduino_mode
                       fnd_d_out(~fnd_font[mul%10]); // data out                       
                  #elif MIC_mode
                       PORTD = ~fnd_font[mul%10];
                  #endif
                  d_out(x1, ON); 
             break;   
        } 
      }  
   #elif Digit_6 // // endif-3
     fnd_dis_A_6(uint16_t d_buf) 
      {
        
      }
   #endif // endif-3-end -------------------------------------------

#elif COM_K // endif-2
   #if Digit_4  // endif-3
     
   #elif Digit_6 // // endif-3

   #endif // endif-3-end
//===========================================================================

#elif FND_595_IF // endif-2-end
 // Arduino 멀티펑션보드
 // A + 컴몬
enum F_595_Pin
 {
   f_data_pin = DATA,    // 8
   f_clk_pin = CLK,      // 7
   f_Lch_clk_Pin = LATCH // 4
 };
enum F_595_Pin Pin_595;

struct FND_595
{
  const char S_Data_Pin; 
  const char S_Clk_Pin;
  const char L_Clk_Pin; 
};
struct FND_595 Fnd_595_Pin = {f_data_pin, f_clk_pin, f_Lch_clk_Pin};
struct FND_595 *SEG_595_Pin = &Fnd_595_Pin;

 void fnd_dis_595(char scan_f, unsigned char data)
   {
     char k;

    // dp play == 0x01, 0x02, 0x04, 0x08;
    (Seg_V -> Dp_595_Digit == scan_f) ? data &= 0x7f : data |= 0x80;
         
     // Latch Clk Low
     d_out(SEG_595_Pin -> L_Clk_Pin, 0);  

    for(k = 0; k <= 7; k++)
     {
      if((data & 0x80) == 0x80) d_out(SEG_595_Pin -> S_Data_Pin, 1);
      else d_out(SEG_595_Pin -> S_Data_Pin, 0);

      d_out((*SEG_595_Pin).S_Clk_Pin, 1);       
      d_out((*SEG_595_Pin).S_Clk_Pin, 0);

      data <<= 1;
     }

    for(k=0; k <= 7; k++)
     {
      if((scan_f & 0x80) == 0x80) d_out(SEG_595_Pin -> S_Data_Pin, 1);
      else d_out(SEG_595_Pin -> S_Data_Pin, 0);

      d_out(SEG_595_Pin -> S_Clk_Pin, 1);       
      d_out(SEG_595_Pin -> S_Clk_Pin, 0);

      scan_f <<= 1;
     }

    d_out(SEG_595_Pin -> L_Clk_Pin, 1); // Latch Pulse
   }

  #if En_font 
   void En_Font_595_out(char e_x1000, char e_x100, char e_x10, char e_x1)
  #else
   void fnd_595_out(int data)
  #endif 
   {
     Seg_V -> Scan = (Seg_V -> Scan > 4) ? 1 : Seg_V -> Scan + 1;
         
    if((*Seg_V).Scan == 1)
     {
      #if En_font
        fnd_dis_595(0x01, ~ fnd_font[e_x1000]); 
      #else 
        fnd_dis_595(0x01, ~ fnd_font[data/1000]);
      #endif
     }
    else if((*Seg_V).Scan == 2)
     {
      #if En_font 
        fnd_dis_595(0x01, ~ fnd_font[e_x100]); 
      #else
        fnd_dis_595(0x02, ~fnd_font[data%1000/100]);
      #endif
     }
    else if((*Seg_V).Scan == 3) 
     {
      #if En_font
       fnd_dis_595(0x01, ~ fnd_font[e_x10]);  
      #else
       fnd_dis_595(0x04, ~fnd_font[data%100/10]);   // x10
      #endif
     } 
    else if((*Seg_V).Scan == 4) 
     {
      #if En_font 
       fnd_dis_595(0x01, ~ fnd_font[e_x1]); 
      #else
       fnd_dis_595(0x08, ~fnd_font[data%10]);     // x1
      #endif
     }
   }
#endif // endif-2-end

#endif  // } endif-1-end

