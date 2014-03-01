#include "application.h"

// This #include statement was automatically added by the Spark IDE.
#include "flipflop.h"

// This #include statement was automatically added by the Spark IDE.
#include "hmc5883l.h"

/*
    HMC5883l Watermeter Reader
    Author: Keith Baker
    Email: kbaker at alumni dot ithaca dot edu
    
    Very loosely based off of: MAG3110 Breakout Example Code
                           by: Aaron Weiss, aaron at sparkfun dot com

    Track magnetic impeller of a water meter using a digital compass.

*/

hmc5883l hmc = hmc5883l();
flipflop counter = flipflop();
unsigned long last = millis();
unsigned long now = millis();
byte mps = 0;
unsigned long last_count = 0;

#define LED        D7

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

  //to late, hold on tight!
  Serial.println("Starting...");
  Wire.begin(true);        // join i2c bus at high speed
  hmc.config();        // turn the HMC5883l on
  Serial.println("Configured");
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
  if (now - last > 1000){
    last = now;
    Serial.print(counter.count - last_count);
    last_count = counter.count;
    Serial.print(" ");
    Serial.println(mps);
    mps = 0;
  }

}
