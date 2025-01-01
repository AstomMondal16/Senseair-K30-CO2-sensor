
This repository provides a Python driver for interfacing with the K30 CO2 sensor using the Raspberry Pi. It uses the I2C protocol for communication to read CO2 concentration values.

---

## Features

- Reads CO2 concentration in ppm (parts per million).
- Includes checksum validation for reliable data.
- Designed to work seamlessly with the Raspberry Pi GPIO pins.

---

## Requirements

### Hardware
- Raspberry Pi (any model with I2C support).
- K30 CO2 sensor.
- TTL to I2C converter (if your K30 sensor has a TTL interface).

### Software
- Python 3.x
- Required libraries: `smbus2`, `i2c-tools`

---

## Hardware Connections

| Raspberry Pi Pin | Function         | Description      |
|-------------------|------------------|------------------|
| GPIO Pin 3 (SDA) | SDA (I2C Data)   | Connect to SDA   |
| GPIO Pin 5 (SCL) | SCL (I2C Clock)  | Connect to SCL   |
| GPIO Pin 1 (3V3) | Power (3.3V)     | Connect to VCC   |
| GPIO Pin 6 (GND) | Ground           | Connect to GND   |

If your K30 sensor uses TTL, connect it to a TTL-to-I2C converter and then to the Raspberry Pi.

---

## Setup

### 1. Enable I2C on Raspberry Pi
Run the Raspberry Pi configuration tool:

'''bash
sudo raspi-config'''

Navigate to:

Interfacing Options → I2C → Enable
Reboot your Raspberry Pi to apply the changes.

