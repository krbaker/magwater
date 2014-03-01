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

#define LED        D7

void setup()
{
  Serial.begin(9600);  // start serial for output
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
  Wire.begin();        // join i2c bus (address optional for master)
  hmc.config();        // turn the HMC5883l on
  Serial.println("Configured");
}

void loop()
{
  if (hmc.ready()){
    digitalWrite(LED,HIGH);
    if (m.fastread()){
      Serial.println("I2C Read Error");
    }
    digitalWrite(LED,LOW);
  }
  else if (m.available()){
    counter.append(m.getz());
    counter.debug();
    m.advance();
  }
}
