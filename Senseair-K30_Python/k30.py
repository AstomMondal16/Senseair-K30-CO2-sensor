import smbus2
import time

class K30CO2Sensor:
    def __init__(self, i2c_bus=1, co2_addr=0x68):
        self.bus = smbus2.SMBus(i2c_bus)  # Default I2C bus for Raspberry Pi is 1
        self.co2_addr = co2_addr

    def _calculate_checksum(self, buffer):
        return sum(buffer[:3]) & 0xFF

    def read_co2(self):
        try:
            # Write command to the sensor
            command = [0x22, 0x00, 0x08, 0x2A]
            write = smbus2.i2c_msg.write(self.co2_addr, command)
            self.bus.i2c_rdwr(write)

            # Wait for the sensor to process
            time.sleep(0.01)

            # Read response from sensor
            read = smbus2.i2c_msg.read(self.co2_addr, 4)
            self.bus.i2c_rdwr(read)
            buffer = list(read)

            # Validate checksum
            co2_value = (buffer[1] << 8) | buffer[2]
            checksum = self._calculate_checksum(buffer)
            if checksum == buffer[3]:
                return co2_value
            else:
                print("Checksum validation failed")
                return None
        except OSError as e:
            print("I2C communication error:", e)
            return None
