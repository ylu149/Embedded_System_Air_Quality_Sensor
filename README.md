# Note for Video 

The video exceeded 100 MB (Github's maximum file size limit) and couldn't be pushed onto Github. Please use the YouTube link below to see the demo for the project.

https://www.youtube.com/watch?v=y9pn7zzBPrc

# EC-535 Portable Air Quality Monitoring Device Setup Instructions

This guide will help you set up your Portable Air Quality Monitoring Device based on the BeagleBone platform, equipped to monitor temperature, humidity, atmospheric pressure, and IAQ (Indoor Air Quality Index). The device utilizes a BeagleBone Black, BME680 sensor, and LCD screen, along with color-coded LEDs to indicate air quality.

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
4. **Run Executable**
   ```bash
   ./sensor
   
