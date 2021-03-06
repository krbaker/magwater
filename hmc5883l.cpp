#include "application.h"
#include "hmc5883l.h"

hmc5883l::hmc5883l() {
  read_position = 0;
  write_position = 0;
  fill = 0;
}

hmc5883l::~hmc5883l() {}

byte hmc5883l::fastread(void){
  Wire.beginTransmission(HMC_ADDR); // transmit to device 0x0E
  Wire.write(HMC_MODE);             // x MSB reg
  Wire.write(0x01);                 // Send single read
  Wire.endTransmission();           // actually send
  //delayMicroseconds(2);             //needs at least 1.3us free time between start and stop
  last_read = millis();

  Wire.beginTransmission(HMC_ADDR); // transmit to device 0x0E
  Wire.write(HMC_X_REG);              // x MSB reg
  Wire.endTransmission();       // actually send
  //delayMicroseconds(2); //needs at least 1.3us free time between start and stop

  if (Wire.requestFrom(HMC_ADDR, 6, true) != 6) return 1;
  x[write_position] = Wire.read() << 8; // receive the byte
  x[write_position] = x[write_position] | Wire.read(); // receive the byte
  y[write_position] = Wire.read() << 8; // receive the byte
  y[write_position] = y[write_position] | Wire.read(); // receive the byte
  z[write_position] = Wire.read() << 8; // receive the byte
  z[write_position] = z[write_position] | Wire.read(); // receive the byte
  write_position = write_position + 1;
  if (write_position >= HMC_BUFFER_DEPTH){
    write_position = 0;
  } // Move the write position into the next spot so its clearly ready
  fill ++;
  return 0;
}

void hmc5883l::config(){
  last_read = millis();
}

bool hmc5883l::ready(){
  ready(millis());
}

bool hmc5883l::ready(unsigned long t){
  if ((last_read + HMC_REFRESH) < t){
    return true;
  }
  return false;
}

int16_t hmc5883l::getx(){
  return x[read_position];
}

int16_t hmc5883l::gety(){
  return y[read_position];
}

int16_t hmc5883l::getz(){
  return z[read_position];
}

byte hmc5883l::available(){
  return fill;
}

void hmc5883l::advance(){
  read_position = read_position + 1;
  if (read_position >= HMC_BUFFER_DEPTH){
    read_position = 0;
  }
  fill --;
}

