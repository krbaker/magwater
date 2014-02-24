#ifndef MAG3110
#define MAG3110

#define MAG_ADDR  0x0E //7-bit address for the MAG3110, doesn't change
#define MAG_X_REG  0x01 //Register for X MSB
#define MAG_Y_REG  0x03 //Register for Y MSB
#define MAG_Z_REG  0x04 //Register for z MSB
#define MAG_AUTO_RESTART  0x80 //Bit to enable auto-restart
#define MAG_ACTIVE_MODE   0x01 //Bit to enable active mode
#define MAG_CONFIG_REG1   0x10 //Config Register 1
#define MAG_CONFIG_REG2   0x11 //Config Register 2
#define MAG_BUFFER_DEPTH  4 // size of ring buffer for storing values (max 8 due to positions)

class mag3110 {
 public:
  mag3110();
  ~mag3110();
  void config(bool active_mode = true, bool auto_restart = true);
  int16_t readx();
  int16_t ready();
  int16_t readz();
  int16_t getx();
  int16_t gety();
  int16_t getz();
  byte available();
  void advance();
  byte fastread();

 private:
  int16_t read(byte start_offset);
  int16_t x[MAG_BUFFER_DEPTH];
  int16_t y[MAG_BUFFER_DEPTH];
  int16_t z[MAG_BUFFER_DEPTH];
  byte read_position;
  byte write_position;
  byte fill;
};

#endif
