#include "K30.h"

// Constructor to initialize the I2C communication with the specified SDA and SCL pins
K30::K30(uint8_t scl_pin, uint8_t sda_pin, uint8_t co2_addr) {
  Wire.begin(sda_pin, scl_pin); // Initialize I2C with specified SDA and SCL pins
  this->co2_addr = co2_addr;
}

// Method to calculate checksum from the buffer (byte[0] + byte[1] + byte[2])
void K30::_calculate_checksum(byte* buffer) {
  return (buffer[0] + buffer[1] + buffer[2]) & 0xFF;
}

// Method to read CO2 data from the sensor
uint16_t K30::read_co2() {
  // Write request to sensor
  Wire.beginTransmission(co2_addr);
  Wire.write(0x22); // Start byte
  Wire.write(0x00);
  Wire.write(0x08);
  Wire.write(0x2A);
  if (Wire.endTransmission() != 0) {
    Serial.println("I2C write error");
    return 0;
  }

  // Wait for the sensor to process
  delay(10); // wait 10ms

  // Read response from sensor
  Wire.requestFrom(co2_addr, 4);
  if (Wire.available() == 4) {
    byte buffer[4];
    for (int i = 0; i < 4; i++) {
      buffer[i] = Wire.read();
    }

    // Validate checksum
    uint16_t co2_value = (buffer[1] << 8) | buffer[2];
    byte checksum = _calculate_checksum(buffer);
    if (checksum == buffer[3]) {
      return co2_value;
    } else {
      Serial.println("Checksum validation failed");
      return 0;
    }
  } else {
    Serial.println("I2C read error");
    return 0;
  }
}
