#ifndef K30_H
#define K30_H

#include <Wire.h>

class K30 {
  public:
    // Constructor to initialize the sensor with SDA and SCL pins, and optional CO2 address
    K30(uint8_t scl_pin, uint8_t sda_pin, uint8_t co2_addr = 0x68);
    
    // Method to read the CO2 value from the sensor
    uint16_t read_co2();
  
  private:
    uint8_t co2_addr;  // Sensor I2C address
    void _calculate_checksum(byte* buffer);
};

#endif // K30_H
