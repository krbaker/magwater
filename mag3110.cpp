#include "mag3110.h"

mag3110::mag3110(){
  read_position = 0;
  write_position = 0;
  fill = 0;
}

mag3110::~mag3110(){}

void mag3110::fastread(){
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(MAG_X_REG);              // x MSB reg
  Wire.endTransmission();       // stop transmitting

  delayMicroseconds(2); //needs at least 1.3us free time between start and stop
  byte response = Wire.requestFrom(MAG_ADDR, 6);
  if (response == 6){  // request 6 bytes, if we get them all, great, if not ignore
    x[write_position] = Wire.read() << 8; // receive the byte
    x[write_position] = x[write_position] | Wire.read(); // receive the byte
    y[write_position] = Wire.read() << 8; // receive the byte
    y[write_position] = y[write_position] | Wire.read(); // receive the byte
    z[write_position] = Wire.read() << 8; // receive the byte
    z[write_position] = z[write_position] | Wire.read(); // receive the byte
    write_position = (write_position + 1) % MAG_BUFFER_DEPTH;          // Move the write position into the next spot so its clearly ready
    fill ++;
  }
}

void mag3110::config(bool active_mode, bool auto_restart){
  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x11);              // cntrl register2
  Wire.write(0x80);              // send 0x80, enable auto resets
  Wire.endTransmission();       // stop transmitting

  delay(15);

  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(0x10);              // cntrl register1
  Wire.write(1);                 // send 0x01, active mode
  Wire.endTransmission();       // stop transmitting
}

int mag3110::getx(){
  return x[read_position];
}

int mag3110::gety(){
  return y[read_position];
}

int mag3110::getz(){
  return z[read_position];
}

byte mag3110::available(){
  return fill;
}

void mag3110::advance(){
  read_position = (read_position + 1) % MAG_BUFFER_DEPTH;
  fill --;
}

int mag3110::readx(){
  return mag3110::read(MAG_X_REG);
}

int mag3110::ready(){
  return mag3110::read(MAG_Y_REG);
}

int mag3110::readz(){
  return mag3110::read(MAG_Z_REG);
}

int mag3110::read(byte start_offset){

  Wire.beginTransmission(MAG_ADDR); // transmit to device 0x0E
  Wire.write(start_offset);              // z MSB reg
  Wire.endTransmission();       // stop transmitting

  delayMicroseconds(2); //needs at least 1.3us free time between start and stop

  Wire.requestFrom(MAG_ADDR, 2); // request 2 bytes
  while(Wire.available() < 2)    // slave may send less than requested
    {
    }
  int result = Wire.read() << 8; // receive the high byte
  result |= Wire.read();
  return result;
}
