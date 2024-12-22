#include <stdio.h>
#include <string.h>
#include "driver/i2c.h"
#include "esp_log.h"
#include "esp_err.h"
#include "freertos/portmacro.h"
#include "k30.h"

static const char *TAG = "K30_SENSOR";

// Command to read CO2 concentration
static uint8_t co2_read_command[CO2_READ_CMD_LEN] = {0x22, 0x00, 0x08, 0x2A};

/**
 * @brief I2C master initialization
 */
esp_err_t i2c_master_init(void)
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    esp_err_t err = i2c_param_config(I2C_MASTER_NUM, &conf);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C parameter configuration failed: %s", esp_err_to_name(err));
        return err;
    }
    err = i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "I2C driver installation failed: %s", esp_err_to_name(err));
    }
    return err;
}

/**
 * @brief Function to read CO2 value from the K30 sensor
 */
int16_t read_co2(void)
{
    int16_t co2_value = 0;
    uint8_t response[CO2_RESP_LEN] = {0};
    esp_err_t err;

    // Write CO2 read command to the sensor
    err = i2c_master_write_to_device(I2C_MASTER_NUM, K30_SENSOR_ADDR, co2_read_command, CO2_READ_CMD_LEN, 1000 / portTICK_PERIOD_MS);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to send CO2 read command: %s", esp_err_to_name(err));
        return -1;
    }

    // Wait 38 ms for the sensor to process the command and generate a response
    vTaskDelay(38 / portTICK_PERIOD_MS);

    // Read 4 bytes from the sensor
    err = i2c_master_read_from_device(I2C_MASTER_NUM, K30_SENSOR_ADDR, response, CO2_RESP_LEN, 1000 / portTICK_PERIOD_MS);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read CO2 response: %s", esp_err_to_name(err));
        return -1;
    }

    // Calculate CO2 value from the received data
    co2_value = (response[1] << 8) | response[2];

    // Verify checksum: sum of the first three bytes should equal the fourth byte
    uint8_t checksum = (response[0] + response[1] + response[2]) & 0xFF;
    if (checksum != response[3]) {
        ESP_LOGE(TAG, "Checksum error: expected %d, got %d", checksum, response[3]);
        return -1;
    }

    return co2_value;
}
