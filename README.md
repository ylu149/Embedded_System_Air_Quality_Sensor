# Portable Air Quality Monitoring Device Setup Instructions

This guide will help you set up your Portable Air Quality Monitoring Device based on the BeagleBone platform, which is equipped to monitor temperature, humidity, atmospheric pressure, and IAQ (Indoor Air Quality Index). The device utilizes a BeagleBone Black, BME680 sensor, and LCD screen, along with color-coded LEDs to indicate air quality.

## Prerequisites
Ensure you have the following components:
- BeagleBone Black REV3
- HiLetgo BME680 Sensor
- Element14 BeagleBone 4.3” LCD Display Cape
- Kitronic 5642 Traffic Light
- Breadboard
- Jumper wires (Varying Lengths)
- 5V 2A Barrel Connector Charger

## Hardware Setup
1. **Recreate the Circuit:**
   Follow the wiring diagram below to connect your components correctly.
   
   ![Wiring Diagram](<Wiring Diagram.jpg>)

## Software Installation on Linux
1. **Install ARM GCC Compiler:**
   Download the `arm-linux-gnueabihf-gcc` compiler from [ARM Developer](https://developer.arm.com/downloads/-/gnu-a).

2. **Clone the Repository:**
   Open your terminal and run the following command to clone the device software repository:
   ```bash
   git clone https://github.com/hac17034/EC-535-Portable-Air-Quality-Monitoring-Device-.git
3. **Navigate to Sensor Code Directory:**
   Change to the "Sensor Code" directory using:
   ```bash
   cd "Sensor Code"
4. **Run makefile:**
   ```bash
   make

## Device Deployment

1. **Connect to the BeagleBone black, and upload the "sensor" file onto it (Can be done via MobaXtreme (Windows) or Picocom (Linux/Mac))**
2. **On BeagleBone Linux Kernal give execution permissions**
   ```bash
   chmod +x sensor
3. **Run Executable**
   ```bash
   ./sensor

## Software Architecture

1. **Software Architecture Flow Chart:**
    A flow chart of the software architecture is shown below.
   
![software arch](https://github.com/ylu149/Embedded_System_Air_Quality_Sensor/assets/112204184/a5f95f39-af2f-4622-95ce-f29a2f5ae449)

## Credit
Credit for bme680.c , bme680.h & bme680_defs goes to Bosch Sensortec. (Code was pulled off their official GitHub) 

Bosch Sensortec. (2016, June 22). *BME680 Sensor API*. GitHub. Retrieved from
https://github.com/boschsensortec/BME680_SensorAPI




   

   
