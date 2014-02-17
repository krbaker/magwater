#include "mag3110.h"

/*
  MAG3110 Test Code
  by: Keith Baker (kbaker at alumni dit ithaca dit edu) Feb 2014
  Adapted from Aaron Weiss, aaron at sparkfun dot com
      SparkFun Electronics 2011
  date: 9/6/11
  license: beerware, if you use this code and happen to meet me, you
           can by me a beer

  The code reads the raw 16-bit x, y, and z values and prints them 
  out forever.
*/

mag3110 m;
byte available = 0;

#define LED        D7
#define MAG_INT    D2

void magisr(void){
  //  detachInterrupt(MAG_INT);
  //  Serial.println("INT!");
  m.fastread();
  //  attachInterrupt(MAG_INT, magisr, RISING);
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
  m = mag3110();
  m.config();          // turn the MAG3110 on
  Serial.println("Configured");
  attachInterrupt(D2, magisr, RISING);
  m.fastread();
  Serial.println("Interrupt Enabled");
}

void loop()
{
  available = m.available();
  if (available){
    print_values();
    m.advance();
  }
}

void print_values(void)
{
  Serial.print("available=");
  Serial.print(available);
  Serial.print(",x=");
  Serial.print(m.getx());
  Serial.print(",y=");
  Serial.print(m.gety());
  Serial.print(",z=");
  Serial.println(m.getz());
}
