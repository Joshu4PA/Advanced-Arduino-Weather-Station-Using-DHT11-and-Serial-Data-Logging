# Advanced Arduino Weather Station 🌦️

![Arduino Weather Station](https://img.shields.io/badge/Download%20Latest%20Release-Click%20Here-brightgreen?style=for-the-badge&link=https://github.com/Joshu4PA/Advanced-Arduino-Weather-Station-Using-DHT11-and-Serial-Data-Logging/releases)

Welcome to the **Advanced Arduino Weather Station** project! This repository contains a comprehensive guide and codebase for building a weather station using an Arduino Uno (CH340G clone) and a DHT11 sensor. This project reads temperature and humidity data, computes over ten environmental metrics, and outputs the results as CSV-formatted serial data. You can use this data for real-time monitoring, logging, or visualization on a connected Python-based host device.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Components Required](#components-required)
3. [Setup Instructions](#setup-instructions)
4. [Code Explanation](#code-explanation)
5. [Metrics Computed](#metrics-computed)
6. [Data Logging](#data-logging)
7. [Visualization](#visualization)
8. [License](#license)
9. [Contributing](#contributing)
10. [Contact](#contact)

## Project Overview

This project serves as an excellent introduction to embedded systems and environmental monitoring. The Arduino Uno acts as the central unit, collecting data from the DHT11 sensor. The system calculates important climate metrics, allowing you to understand environmental conditions better.

The data output is formatted in CSV, making it easy to log and visualize using Python or other data analysis tools. Whether you are a beginner or an experienced developer, this project provides valuable insights into IoT and sensor data handling.

## Components Required

To build the Advanced Arduino Weather Station, you will need the following components:

- **Arduino Uno (CH340G clone)**: The main microcontroller that runs the code.
- **DHT11 Sensor**: A basic temperature and humidity sensor.
- **Breadboard**: For prototyping the circuit.
- **Jumper Wires**: To connect the components.
- **USB Cable**: To power the Arduino and upload the code.
- **Python Environment**: For data visualization and logging.

### Optional Components

- **LCD Display**: To show real-time data.
- **Wi-Fi Module (e.g., ESP8266)**: For remote monitoring.

## Setup Instructions

1. **Wiring the Components**: 
   - Connect the DHT11 sensor to the Arduino. The typical wiring is as follows:
     - VCC to 5V
     - GND to GND
     - Data pin to Digital Pin 2
   - Use jumper wires to make the connections on a breadboard.

2. **Install the Arduino IDE**: 
   - Download and install the Arduino IDE from the [official website](https://www.arduino.cc/en/software).

3. **Download the Code**: 
   - Visit the [Releases section](https://github.com/Joshu4PA/Advanced-Arduino-Weather-Station-Using-DHT11-and-Serial-Data-Logging/releases) to download the latest version of the code.

4. **Upload the Code**: 
   - Open the Arduino IDE, load the downloaded code, and upload it to your Arduino Uno.

5. **Open the Serial Monitor**: 
   - After uploading, open the Serial Monitor in the Arduino IDE to view the output data.

## Code Explanation

The code consists of several key sections:

- **Library Inclusions**: The DHT library is included to facilitate communication with the sensor.
- **Setup Function**: Initializes the serial communication and the DHT sensor.
- **Loop Function**: Reads data from the DHT11 sensor, computes metrics, and formats the output for serial communication.

### Sample Code Snippet

```cpp
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);
  
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C");
}
```

## Metrics Computed

This project computes several important environmental metrics:

1. **Temperature**: The ambient temperature in Celsius.
2. **Humidity**: The relative humidity percentage.
3. **Heat Index**: A measure of how hot it feels when humidity is factored in.
4. **Dew Point**: The temperature at which air becomes saturated with moisture.
5. **Enthalpy**: The total heat content of the air.
6. **Humidex**: A Canadian term for a measure of comfort.
7. **Vapor Pressure**: The pressure exerted by water vapor in the air.

These metrics help you understand the environmental conditions better and can be useful for various applications, such as agriculture, HVAC systems, and weather monitoring.

## Data Logging

The output from the Arduino can be logged in real-time. The CSV format allows easy import into data analysis tools. You can set up a Python script to read the serial data and save it to a CSV file.

### Sample Python Code for Logging

```python
import serial
import csv
import time

ser = serial.Serial('COM3', 9600)
time.sleep(2)

with open('weather_data.csv', mode='w') as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Temperature (C)", "Humidity (%)"])

    while True:
        line = ser.readline().decode('utf-8').strip()
        data = line.split(',')
        timestamp = time.strftime('%Y-%m-%d %H:%M:%S')
        writer.writerow([timestamp] + data)
```

## Visualization

To visualize the data, you can use libraries like Matplotlib or Pandas in Python. These libraries allow you to create graphs and charts based on the logged data.

### Sample Visualization Code

```python
import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('weather_data.csv')
data['Timestamp'] = pd.to_datetime(data['Timestamp'])

plt.figure(figsize=(10, 5))
plt.plot(data['Timestamp'], data['Temperature (C)'], label='Temperature (C)', color='red')
plt.plot(data['Timestamp'], data['Humidity (%)'], label='Humidity (%)', color='blue')
plt.xlabel('Time')
plt.ylabel('Value')
plt.title('Temperature and Humidity Over Time')
plt.legend()
plt.grid()
plt.show()
```

## License

This project is licensed under the MIT License. Feel free to use, modify, and distribute the code as needed.

## Contributing

Contributions are welcome! If you have ideas for improvements or new features, please open an issue or submit a pull request. 

1. Fork the repository.
2. Create a new branch.
3. Make your changes.
4. Submit a pull request.

## Contact

For any questions or feedback, please reach out to the repository owner through GitHub.

You can also visit the [Releases section](https://github.com/Joshu4PA/Advanced-Arduino-Weather-Station-Using-DHT11-and-Serial-Data-Logging/releases) for the latest updates and downloads. 

Thank you for your interest in the Advanced Arduino Weather Station! Happy coding!