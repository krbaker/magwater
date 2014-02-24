// This #include statement was automatically added by the Spark IDE.
#include "mag3110.h"

/*
   MAG3110 Breakout Example Code

   by: Aaron Weiss, aaron at sparkfun dot com
       SparkFun Electronics 2011
   date: 9/6/11
   license: beerware, if you use this code and happen to meet me, you
           can by me a beer

   The code reads the raw 16-bit x, y, and z values and prints them
   out. This sketch does not use the INT1 pin, nor does it poll for
   new data.

*/

mag3110 m = mag3110();
volatile bool magready = true;

#define LED        D7
#define MAG_INT    D2

void magisr(void){
  digitalWrite(LED,HIGH);
  magready = true;
  digitalWrite(LED,LOW);
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
  //m = mag3110();
  m.config();          // turn the MAG3110 on
  Serial.println("Configured");
  attachInterrupt(D2, magisr, RISING);
  Serial.println("Interrupt Enabled");
  RGB.control(true);
}

void loop()
{
  if (magready){
    RGB.color(255, 0, 0);
    if (not m.fastread()){
      magready = false;
    }
    else {
      Serial.println("I2C Read Error");
    }
    RGB.color(0, 255, 0);
  }
  else if (m.available()){
    RGB.color(0, 255, 255);
    print_values();
    m.advance();
    RGB.color(0, 0, 255);
  }
  else {
    RGB.color(255, 255, 255);
  }
}

void print_values(void)
{
  Serial.print("x=");
  Serial.print(m.getx());
  Serial.print(",y=");
  Serial.print(m.gety());
  Serial.print(",z=");
  Serial.println(m.getz());
}
