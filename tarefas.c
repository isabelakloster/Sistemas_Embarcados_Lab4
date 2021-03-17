#include "system_tm4c1294.h" // CMSIS-Core
#include "driverleds.h" // device drivers
#include "cmsis_os2.h" // CMSIS-RTOS

osThreadId_t thread1_id, thread2_id, thread3_id, thread4_id;

struct parameters {
  uint32_t LED;
  uint32_t timeout;
};

void thread(void *arg){
  uint8_t state = 0;
  uint32_t tick;
  struct parameters *p = (struct parameters*)arg;
  
  while(1){
    tick = osKernelGetTickCount();
    
    state ^= p->LED;
    LEDWrite(p->LED, state);
    
    osDelayUntil(tick + p->timeout);
  } // while
} // thread

void main(void){
  LEDInit(LED2 | LED1 | LED3 | LED4);

  osKernelInitialize();
  
  struct parameters p1;
  struct parameters p2;
  struct parameters p3;
  struct parameters p4;
  p1.LED = LED1;
  p1.timeout = 200;
  p2.LED = LED2;
  p2.timeout = 300;
  p3.LED = LED3;
  p3.timeout = 500;
  p4.LED = LED4;
  p4.timeout = 700;


  thread1_id = osThreadNew(thread, (void*)&p1, NULL);
  thread2_id = osThreadNew(thread, (void*)&p2, NULL);
  thread3_id = osThreadNew(thread, (void*)&p3, NULL);
  thread4_id = osThreadNew(thread, (void*)&p4, NULL);

  if(osKernelGetState() == osKernelReady)
    osKernelStart();

  while(1);
} // main
