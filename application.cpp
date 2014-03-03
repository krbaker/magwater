#include "application.h"

// This #include statement was automatically added by the Spark IDE.
#include "flipflop.h"

// This #include statement was automatically added by the Spark IDE.
#include "hmc5883l.h"

#include "sense.h"

/*
    HMC5883l Watermeter Reader
    Author: Keith Baker
    Email: kbaker at alumni dot ithaca dot edu
    
    Very loosely based off of: MAG3110 Breakout Example Code
                           by: Aaron Weiss, aaron at sparkfun dot com

    Track magnetic impeller of a water meter using a digital compass.

*/
#define LED        D7
#define SENSE_KEY  "YRs5Wv4N-5JKqmk2I_hZDw"
#define SENSE_ID   52732

hmc5883l hmc = hmc5883l();
flipflop counter = flipflop();
unsigned long last = millis();
unsigned long now = millis();
unsigned int mps = 0;
unsigned long last_count = 0;
float avg = 0;
bool blink = false;

sense sclient = sense(SENSE_KEY);

void setup()
{
  Serial.begin(115200);  // start serial for output
  Serial.println("Cloud!");

  //let us know we are connected to cloud so we can re-flash bad code
  pinMode(LED, OUTPUT);
  digitalWrite(LED,HIGH);
  unsigned long time = millis();
  while (millis() < time + 10000 or SPARK_FLASH_UPDATE){
     SPARK_WLAN_Loop();
  }
  digitalWrite(LED,LOW);

  Spark.disconnect(); // We don't need any cloud after we allow re-flash, takes a ton of cycles
  //to late, hold on tight!
  Serial.println("Starting...");
  Wire.begin(false);        // join i2c bus at high speed
  hmc.config();        // turn the HMC5883l on
  Serial.println("Configured");
  RGB.control(true);
}

void loop()
{
  now = millis();
  if (hmc.ready(now)){
    digitalWrite(LED,HIGH);
    if (hmc.fastread()){
      Serial.println("I2C Read Error");
    }
    digitalWrite(LED,LOW);
  }
  else if (hmc.available()){
    counter.append(hmc.getz());
    //counter.debug();
    hmc.advance();
    mps ++;
  }
  else if (now - last > 60000){
    last = now;
    int delta = counter.count - last_count; 
    last_count = counter.count;
    avg = ((avg * 59.0) + delta) / 60.0;
    Serial.print(delta);
    Serial.print(" "); 
    Serial.print(avg); 
    Serial.print(" ");
    Serial.println(mps);
    if (blink){
      blink = false;
    }
    else {
      blink = true;
    }
    RGB.color(delta / 8, (int)(avg / 8), (int)blink * 255);
    mps = 0;
    sclient.post(SENSE_ID, delta);
  }
  else {
    sclient.work();
  }
}
