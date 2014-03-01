#ifndef HMC5883L
#define HMC5883L

#define HMC_ADDR  0x3C //7-bit address for the HMC5883L, doesn't change

#define HMC_CONFIG_REG    0x00 //Config Register
#define HMC_GAIN_REG      0x01 //Gain   Register
#define HMC_MODE          0x02 //Mode   Register
#define HMC_X_REG         0x03 //Register for X MSB
#define HMC_Y_REG         0x05 //Register for Y MSB
#define HMC_Z_REG         0x07 //Register for z MSB
#define HMC_BUFFER_DEPTH  4    // size of ring buffer for storing values (max 8 due to positions)

#define HMC_REFRESH       6    //number of milliseconds we have to wait to read again

class hmc5883l {
 public:
  hmc5883l();
  ~hmc5883l();
  void config();
  int16_t getx();
  int16_t gety();
  int16_t getz();
  byte available();
  bool ready();
  void advance();
  byte fastread();

 private:
  unsigned long last_read;
  int16_t x[HMC_BUFFER_DEPTH];
  int16_t y[HMC_BUFFER_DEPTH];
  int16_t z[HMC_BUFFER_DEPTH];
  byte read_position;
  byte write_position;
  byte fill;
};

#endif
