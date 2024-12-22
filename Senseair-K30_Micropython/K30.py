from machine import Pin, I2C
import time

class K30CO2Sensor:
    def __init__(self, scl_pin, sda_pin, freq=100000, co2_addr=0x68):
        self.i2c = I2C(0, scl=Pin(scl_pin), sda=Pin(sda_pin), freq=freq)
        self.co2_addr = co2_addr

    def _calculate_checksum(self, buffer):
        return sum(buffer[0:3]) & 0xFF

    def read_co2(self):
        # Write request to sensor
        try:
            self.i2c.writeto(self.co2_addr, bytearray([0x22, 0x00, 0x08, 0x2A]))
        except OSError as e:
            print("I2C write error:", e)
            return None

        # Wait for the sensor to process
        time.sleep(0.01)

        # Read response from sensor
        try:
            buffer = self.i2c.readfrom(self.co2_addr, 4)
        except OSError as e:
            print("I2C read error:", e)
            return None

        # Validate checksum
        co2_value = (buffer[1] << 8) | buffer[2]
        checksum = self._calculate_checksum(buffer)
        if checksum == buffer[3]:
            return co2_value
        else:
            print("Checksum validation failed")
            return None

