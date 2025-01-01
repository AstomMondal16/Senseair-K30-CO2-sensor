from k30 import K30CO2Sensor
import time

def main():
    # Initialize the K30 driver
    sensor = K30CO2Sensor(i2c_bus=1, co2_addr=0x68)  # Default I2C bus on Pi is 1

    while True:
        co2_value = sensor.read_co2()
        if co2_value is not None:
            print("CO2 Value:", co2_value)
        else:
            print("Checksum failed / Communication failure")
        time.sleep(2)  # Wait for the next reading

if __name__ == "__main__":
    main()
