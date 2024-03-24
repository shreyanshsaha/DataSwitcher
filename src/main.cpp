#include <Arduino.h>
#include "DataSwitcher.h"
int NEXT_SCREEN_PIN = 34;
int PREV_SCREEN_PIN = 35;

int lastIndex = 0;
int idx = 0;
int data[10];

DataSwitcher<int> switcher(data, 10);


void setup(){ 
  DataSwitcher<int>::size = 10;
  DataSwitcher<int>::index = &idx;

  Serial.begin(115200);
  Serial.println("Started");
  data[0] = 1;
  data[1] = 2;
  data[2] = 3;
  data[3] = 4;
  data[4] = 5;
  data[5] = 6;
  data[6] = 7;
  data[7] = 8;
  data[8] = 9;
  data[9] = 10;

  switcher.setPrevButtonPin(PREV_SCREEN_PIN);
  switcher.setNextButtonPin(NEXT_SCREEN_PIN);
  switcher.setIndex(&idx);
  switcher.setup();

  Serial.println(data[idx]);
}

void loop(){
  if(lastIndex!=idx){
    Serial.println(data[idx]);
    lastIndex=idx;
  }
}