# Advanced-Arduino-Weather-Station-Using-DHT11-and-Serial-Data-Logging
An Arduino Uno (CH340G clone) reads temperature and humidity from a DHT11 sensor and computes 10+ environmental metrics (heat index, dew point, enthalpy, humidex, vapor pressures, etc.), outputting them as CSV-formatted serial data for real-time monitoring, logging, or visualization on a connected Python-based host device.

Here is the fully revised, detailed, and clearly worded explanation of both the **Arduino sketch** and the **Python script**:

---

### Arduino Sketch 

This Arduino sketch reads real-time temperature and humidity data from a **DHT11** sensor and calculates a set of derived atmospheric metrics. Every two seconds, it outputs a comma-separated string of these values through the serial port at **9600 baud**, making it ideal for integration with data logging or visualization tools.

The program begins by including the `DHT.h` library and defining the sensor pin and type (`DHT11`). A `DHT` object is instantiated to facilitate communication with the sensor hardware. In the `setup()` function, the serial port is initialized and the DHT sensor is started, followed by a short delay to ensure sensor stability before readings begin.

In the `loop()`, the sketch reads the **temperature (°C)** and **relative humidity (%)** from the DHT11. If either value is invalid (`NaN`), the program prints a line of `"nan"` values across all expected outputs, waits one second, and retries. When valid data is available, the sketch performs the following environmental calculations:

* **Heat Index:** Represents perceived temperature, using the built-in DHT function.
* **Dew Point:** Approximates the temperature at which condensation occurs, calculated with a linear formula.
* **Absolute Humidity (g/m³):** Mass of water vapor per unit volume of air, based on temperature and relative humidity.
* **Specific Humidity:** Approximates the mass ratio of water vapor to total air mass.
* **Mixing Ratio (g/kg):** Water vapor mass per kilogram of dry air, commonly used in meteorological contexts.
* **Vapor Pressure (hPa):** Partial pressure exerted by the water vapor in the air.
* **Saturation Vapor Pressure (hPa):** Maximum vapor pressure possible at a given temperature.
* **Wet Bulb Temperature (°C):** Empirical approximation of the lowest temperature air can reach via evaporative cooling.
* **Humidex:** Canadian-derived comfort index combining temperature and humidity to reflect perceived warmth.
* **Enthalpy (kJ/kg):** Total heat content of the air, factoring both sensible heat and latent heat from humidity.

The results are printed to the serial port as a **CSV (Comma-Separated Values)** line with each value formatted to two decimal places, except for specific humidity, which is printed with five decimal places for precision. This structured output can be parsed easily by external scripts for display, storage, or further analysis.

The sketch repeats every **2 seconds**, ensuring continuous environmental monitoring. This makes it well-suited for DIY weather stations, classroom experiments, or embedded environmental sensing systems.

---

### Python Visualization Script 

This Python script serves as a **real-time terminal interface** to display data sent by the Arduino-based weather station. It provides an interactive and color-enhanced view of sensor readings using the **`colorama`** library for ANSI color formatting and **`pyserial`** for communication over a USB serial connection.

At startup, the script imports all necessary libraries and initializes the terminal color settings. It automatically scans available serial ports, printing them to the terminal, and checks if the user-defined port (e.g., `/dev/tty.usbserial-1410`) is connected. If not, the program gracefully exits with a detailed error message.

The script defines a set of utility functions to:

* Print stylized borders for improved readability
* Display log messages with timestamps and color-coded severity
* Parse incoming serial data
* Handle and display parsing or connection errors clearly

Once connected, the main loop begins. It continuously reads a line from the serial port, decodes it, and parses it into **12 expected float values** (in order: temperature, humidity, heat index, dew point, absolute humidity, specific humidity, mixing ratio, vapor pressure, saturation vapor pressure, wet bulb temperature, humidex, and enthalpy). If successful, the script:

* Clears the terminal display
* Prints a decorative header with the timestamp
* Displays all current sensor readings in a neat, color-coded table
* Updates a persistent log panel below the data table with status messages

If the serial reading or parsing fails (due to disconnection or invalid data), the error is logged and shown in red. The script also handles **Ctrl+C** (keyboard interrupt) to safely exit and display a goodbye message with the total uptime of the session.

This Python script enhances user experience by turning raw serial data into a **live, structured, and visually intuitive dashboard**, making it easy to monitor and interpret environmental conditions in real time.
