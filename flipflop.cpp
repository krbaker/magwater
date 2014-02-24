#include "application.h"
#include "flipflop.h"

flipflop::flipflop(int16_t in_hystaresis) {
  count = 0;
  direction = true; // We start going...  up
  hystaresis = in_hystaresis;
  min = 32000;
  max = -32000;
}

flipflop::~flipflop() {}

void flipflop::debug(void){
  Serial.print("delta=");
  Serial.print(real_max - real_min);
  Serial.print(", min=");
  Serial.print(real_min);
  Serial.print(", max=");
  Serial.print(real_max);
  Serial.print(", dir=");
  Serial.println(direction);
}

unsigned long flipflop::append(int16_t new_point){

  //set mins and maxes if needed
  if (new_point > max){
    max = new_point;
  }
  if (new_point < min){
    min = new_point;
  }
  if (direction and (new_point > (min + hystaresis ) ) ){
    real_min = min;
    direction = false;
    count++;
    max = new_point;
  }
  if (not direction and (new_point < (max - hystaresis ) ) ){
    real_max = max;
    direction = true;
    count++;
    min = new_point;
  }
  return count;
}
