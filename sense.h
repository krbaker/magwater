#ifndef SENSE
#define SENSE

#include "spark_wiring_tcpclient.h"

#define SENSE_ENDPOINT "api.sen.se"

class sense {
 public:
  sense(char in_key[]);
  ~sense();
  void work();
  void post(int in_id, int in_value);

 private:
  char *key;
  int id;
  int value;
  bool to_post;
  TCPClient client;
  void do_post();
};

#endif
