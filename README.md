
# Arduino Weather Station

**A weather station project utilizing an Arduino microcontroller to monitor and display environmental conditions such as temperature, humidity, pressure, light intensity, and time. The data is displayed on an LCD screen for easy viewing.**

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Components](#components)
- [Libraries Used](#libraries-used)
- [Installation](#installation)
- [How It Works](#how-it-works)
- [Version 2.0 - Improved Code](#version-20---improved-code)
- [Future Improvements](#future-improvements)
- [Contributing](#contributing)
- [License](#license)

---

## Overview

This Arduino-based project creates a weather station that measures and displays environmental data such as temperature, humidity, atmospheric pressure, and light intensity. The LCD screen shows real-time data readings, making it a simple and effective way to monitor environmental conditions.

---

## Features

- **Real-Time Environmental Data**: Monitors temperature, humidity, pressure, and light intensity.
- **Time and Date Tracking**: Keeps track of the current time and date using an RTC module.
- **Data Display**: Outputs data readings to an LCD screen for easy access.
- **Compact and Efficient**: Integrates multiple sensors into a compact Arduino setup.

---

## Components

- **Microcontroller**: Arduino Uno
- **Sensors**:
  - DHT11 for temperature and humidity
  - BMP180 for pressure
  - BH1750 for light intensity
- **Modules**:
  - RTC Module (DS3231) for date and time tracking
  - LCD Display for data visualization
- **Additional Components**: Breadboard, wires, and power supply

---

## Libraries Used

This project requires several libraries for sensor interfacing and display control:

- **RTClib**: For real-time clock (RTC) functionality
- **DHT**: For DHT11 temperature and humidity sensor
- **Adafruit BMP085**: For BMP180 pressure sensor
- **BH1750**: For light sensor data processing
- **LiquidCrystal_I2C**: For I2C LCD display handling

---

## Installation

To set up the project:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/your-repo/arduino-weather-station.git
    cd arduino-weather-station
    ```

2. **Open the Project in Arduino IDE**:
   - Ensure the Arduino IDE is installed. Download it [here](https://www.arduino.cc/en/software).
   - Open the `.ino` file in the Arduino IDE.

3. **Install Required Libraries**:
   - Navigate to **Sketch > Include Library > Manage Libraries** in the Arduino IDE.
   - Search for and install:
      - `RTClib`
      - `DHT`
      - `Adafruit BMP085`
      - `BH1750`
      - `LiquidCrystal_I2C`

4. **Upload the Code**:
   - Connect your Arduino Uno to your computer.
   - In **Tools > Board**, select **Arduino Uno** and choose the correct port.
   - Click **Upload** to transfer the code to the Arduino.

5. **Assemble the Circuit**:
   - Follow the wiring guide included in this repository to connect the sensors and LCD to the Arduino Uno.

---

## How It Works

The system utilizes an Arduino Uno to collect environmental data from various sensors:

1. **Temperature & Humidity**: The DHT11 sensor provides temperature and humidity readings.
2. **Pressure**: The BMP180 sensor measures atmospheric pressure, which can also help estimate altitude.
3. **Light Intensity**: The BH1750 light sensor detects ambient light levels.
4. **Date & Time**: The DS3231 RTC module keeps track of the date and time.
5. **Display**: All data is displayed in real time on an LCD screen connected to the Arduino.

---

## Version 2.0 - Improved Code

An optimized version of the Weather Station code (Version 2.0) has been added, which includes:

- **Enhanced Code Readability**: Improved comments and structure for easier understanding.
- **Optimized Code Efficiency**: Refactored code to reduce redundant operations and enhance sensor readings.
- **Error Handling**: Improved handling for cases when sensors fail to read data, with appropriate serial error messages.

Both the original and optimized code versions are available in this repository for reference and testing.

---

## Future Improvements

- **Additional Sensors**: Integration of wind speed, UV, or additional environmental sensors for more comprehensive weather data.
- **Data Logging**: Store data on an SD card for long-term tracking and analysis.
- **Remote Monitoring**: Enable remote access through a Wi-Fi or Bluetooth module.
- **Enhanced Display Options**: Add support for an OLED display or touchscreen for better visualization.

---

## Contributing

Contributions are welcome! Please submit pull requests or open issues for enhancements or bug fixes.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

