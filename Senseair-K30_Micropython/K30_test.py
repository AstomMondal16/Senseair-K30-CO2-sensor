from k30 import K30CO2Sensor
import time

def main():
    print("Application Note AN-102: Interface Pico W to K-30")
    sensor = K30CO2Sensor(scl_pin=1, sda_pin=0)  # Adjust pins as needed

    while True:
        co2_value = sensor.read_co2()
        if co2_value is not None:
            print("CO2 Value:", co2_value)
        else:
            print("Checksum failed / Communication failure")
        time.sleep(2)

if __name__ == "__main__":
    main()
