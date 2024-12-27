#include <Arduino_FreeRTOS.h>
#include <MsTimer2.h>

void time_irq(){
  Serial.println("tiemr 2");
}

void setup(){
MsTimer2::set(1000, time_irq);
MsTimer2::start();

  Serial.begin(115200);
  Serial.println("Setup");

  DDRD |= 0x0C;

  // vTaskDelay(1000 / portTICK_PERIOD_MS); 이 함수를 쓰지 않으면, 동시에 두개의 타스트가 겹칠때, 우선순위가 낮은 타스크는 실행 되지 않음,
  //따라서 vTaskDelay 를 사용할것. 이 함수를 사용하면, 타스크가 겹쳐도 우선순위대로 동작하는것 같음

 /*  
  xTaskCreate() 함수가 각각의 테스크를 만드는 함수이다.
  xTaskCreate(taskFunction, 테스크이름, 사용할 스택크기, 함수 실행 시 넘겨줄 인자, 테스크 우선 순위, 테스크 핸들)
  예를들어
  xTaskCreate(t1_Main, NULL, configMINIMAL_STACK_SIZE, NULL, 1, NULL); 

  taskFunction : t1t1_Main
  테스크이름 : NULL
  사용할 스택크기 : configMINIMAL_STACK_SIZE
  함수 실행 시 넘겨줄 인자 :NULL
  테스크 우선 순위 : 1(숫자가 높을 수록 높은 순위)
  테스크 핸들 : NULL
  xTaskCreate(thr1, "쓰레드1", 500, NULL, 1, NULL);
  xTaskCreate(thr2, "쓰레드2", 300, NULL, 2, NULL);
  xTaskCreate(thr1, "쓰레드1", 500, NULL, NULL, NULL);
  xTaskCreate(thr2, "쓰레드2", 300, NULL, NULL, NULL);
  xTaskCreate(thr1, "쓰레드1", 500, NULL, 1, NULL);
  xTaskCreate(thr2, "쓰레드2", 300, NULL, 1, NULL);
*/
  xTaskCreate(thr1, "쓰레드1", 500, NULL, 1, NULL);
  xTaskCreate(thr2, "쓰레드2", 300, NULL, 2, NULL);
} 

void loop(){
  Serial.println("Song");
  _delay_ms(1000);

} 

static void thr1(void* pvParameters){
  while(true){
    Serial.println("Thread 1");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    PORTD ^= (1<<2);
    //_delay_ms(1000);

  }
}

static void thr2(void* pvParameters){
  while(true){
    Serial.println("Thread 2");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    PORTD ^= (1<<3);
    //_delay_ms(200);
  }
}