#include "application.h"

// This #include statement was automatically added by the Spark IDE.
#include "flipflop.h"

// This #include statement was automatically added by the Spark IDE.
#include "mag3110.h"

/*
    MAG3110 Watermeter Reader
    Author: Keith Baker
    Email: kbaker at alumni dot ithaca dot edu
    
    Very loosely based off of: MAG3110 Breakout Example Code
                           by: Aaron Weiss, aaron at sparkfun dot com

    Track magnetic impeller of a water meter using a digital compass.

*/

mag3110 m = mag3110();
flipflop counter = flipflop();
volatile bool magready = true;

#define LED        D7
#define MAG_INT    D2

void magisr(void){
  magready = true;
}

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
  pinMode(MAG_INT, INPUT_PULLDOWN);
  m.config();          // turn the MAG3110 on
  Serial.println("Configured");
  attachInterrupt(MAG_INT, magisr, RISING);
  Serial.println("Interrupt Enabled");
}

void loop()
{
  if (magready){
    magready = false; //we know this interrupt has happened, make sure we can catch the next one
    digitalWrite(LED,HIGH);
    if (m.fastread()){
      Serial.println("I2C Read Error");
      magready = true; //we should try and re-read
    }
    digitalWrite(LED,LOW);
    if (digitalRead(MAG_INT)){
      magready = true;
    }
  }
  else if (m.available()){
    counter.append(m.getz());
    counter.debug();
    m.advance();
  }
}
