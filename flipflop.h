#ifndef FLIPFLOP
#define FLIPFLOP

class flipflop {
 public:
  flipflop(int16_t hystaresis = 50);
  ~flipflop();
  unsigned long append(int16_t new_point);
  void debug();

 private:
  int16_t min;
  int16_t max;
  int16_t real_min;
  int16_t real_max;
  int16_t hystaresis;
  bool direction;
  unsigned long count;
  byte current;
};

#endif
