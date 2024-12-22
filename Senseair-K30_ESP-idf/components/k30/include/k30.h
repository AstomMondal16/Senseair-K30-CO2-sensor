#ifndef K30_SENSOR_H
#define K30_SENSOR_H

#include "esp_err.h"

// I2C configuration for K30 sensor
#define I2C_MASTER_SCL_IO 41               // GPIO number for I2C master clock
#define I2C_MASTER_SDA_IO 42              // GPIO number for I2C master data
#define I2C_MASTER_FREQ_HZ 100000          // I2C master clock frequency
#define I2C_MASTER_NUM I2C_NUM_0           // I2C port number for master dev
#define I2C_MASTER_TX_BUF_DISABLE 0        // I2C master doesn't need buffer
#define I2C_MASTER_RX_BUF_DISABLE 0        // I2C master doesn't need buffer
#define K30_SENSOR_ADDR 0x68               // K30 CO2 sensor I2C address
#define CO2_READ_CMD_LEN 4                 // Length of the CO2 read command
#define CO2_RESP_LEN 4                     // Length of the response from the sensor

// I2C Master initialization function
esp_err_t i2c_master_init(void);

// Function to read CO2 concentration
int16_t read_co2(void);

#endif // K30_SENSOR_H
