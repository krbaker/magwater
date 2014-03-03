#include "sense.h"
#include "application.h"


sense::sense(char in_key[]){
  to_post = false;
  key = in_key;
}

sense::~sense(){}

void sense::work(){
  //keep ourselves connected
  //using if,else-if so we only do a bit of work each round
  if (!client.connected()){
    Serial.println("Reconnecting");
    client.connect(SENSE_ENDPOINT, 80);
  }
  else if(to_post){
    do_post();
  }
}

void sense::do_post(){
  String data = "{\"feed_id\":" + String(id) + ", \"value\":" + String(value) + '}';
  client.print("POST /events/ HTTP/1.1\n");
  client.print("Host: ");
  client.print(SENSE_ENDPOINT);
  client.print("\n");
  client.print("Content-Type: application/json\n");
  client.print("sense_key: ");
  client.print(key);
  client.print("\n");
  client.print("Connection: close\n");
  client.print("User-Agent: ArdunioWater\n");
  client.print("Content-Length: ");
  client.print(data.length());
  client.print("\n\n");
  client.print(data);
  while (client.connected()) {
    client.flush();
  }
  to_post = false;
}

void sense::post(int in_id, int in_value){
  id = in_id;
  value = in_value;
  to_post = true;
}

