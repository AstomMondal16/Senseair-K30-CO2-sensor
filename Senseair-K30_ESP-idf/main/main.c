#include "k30.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "MAIN";

void app_main()
{
    // Initialize I2C
    ESP_ERROR_CHECK(i2c_master_init());

    while (1)
    {
        // Read and print CO2 value from the sensor
        int16_t co2 = read_co2();
        if (co2 >= 0) {
            ESP_LOGI(TAG, "CO2 Concentration: %d ppm", co2);
        } else {
            ESP_LOGE(TAG, "Failed to read CO2 concentration");
        }

        // Wait for a while before reading again
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}
