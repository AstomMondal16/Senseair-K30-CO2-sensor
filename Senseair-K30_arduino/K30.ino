#include "K30.h"

// Create an instance of the K30 sensor with SDA and SCL pins
K30 sensor(4, 5); // Adjust SDA and SCL pins as needed for your board

void setup() {
  Serial.begin(115200);
  Serial.println("Application Note AN-102: Interface Arduino to K-30");
}

void loop() {
  uint16_t co2_value = sensor.read_co2();
  if (co2_value > 0) {
    Serial.print("CO2 Value: ");
    Serial.println(co2_value);
  } else {
    Serial.println("Checksum failed / Communication failure");
  }

  delay(2000); // Wait for 2 seconds before the next reading
}
