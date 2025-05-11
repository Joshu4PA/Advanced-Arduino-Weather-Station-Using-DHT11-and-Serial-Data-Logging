#include <DHT.h>

#define DHTPIN 2         // Pin where the DHT11 is connected
#define DHTTYPE DHT11    // DHT11 sensor
#define LED_PIN 13       // On-board LED pin for Arduino Uno

DHT dht(DHTPIN, DHTTYPE);

void blinkLed(int times, int delayMs) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(delayMs);
    digitalWrite(LED_PIN, LOW);
    delay(delayMs);
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(LED_PIN, OUTPUT); // Set LED pin as output
  delay(2000); // Allow sensor startup time
}

void loop() {
  float temp = dht.readTemperature();  // Celsius
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("nan,nan,nan,nan,nan,nan,nan,nan,nan,nan,nan,nan");
    delay(1000);
    return;
  }

  // Calculations
  float heatIndex = dht.computeHeatIndex(temp, hum, false);
  float dewPoint = temp - ((100 - hum) / 5.0);
  float absHumidity = 216.7 * ((hum / 100.0) * 6.112 * exp((17.62 * temp) / (243.12 + temp)) / (273.15 + temp));
  float specificHumidity = (0.622 * (hum / 100.0)) / (1 + (0.622 * (hum / 100.0))); // Approximate
  float mixingRatio = (622 * (hum / 100.0)) / (1000 - (hum / 100.0));
  float vaporPressure = hum / 100.0 * 6.112 * exp((17.62 * temp) / (243.12 + temp));
  float satVaporPressure = 6.112 * exp((17.62 * temp) / (243.12 + temp));
  float wetBulb = temp * atan(0.151977 * sqrt(hum + 8.313659)) + atan(temp + hum) - atan(hum - 1.676331) + 0.00391838 * pow(hum, 1.5) * atan(0.023101 * hum) - 4.686035;
  float humidex = temp + 0.5555 * (vaporPressure - 10.0);
  float enthalpy = 1.006 * temp + (2501 + 1.86 * temp) * hum / 100.0;

  // Blink LED 3 times quickly
  blinkLed(3, 60);

  // Send data
  Serial.print(temp, 2); Serial.print(",");
  Serial.print(hum, 2); Serial.print(",");
  Serial.print(heatIndex, 2); Serial.print(",");
  Serial.print(dewPoint, 2); Serial.print(",");
  Serial.print(absHumidity, 2); Serial.print(",");
  Serial.print(specificHumidity, 5); Serial.print(",");
  Serial.print(mixingRatio, 2); Serial.print(",");
  Serial.print(vaporPressure, 2); Serial.print(",");
  Serial.print(satVaporPressure, 2); Serial.print(",");
  Serial.print(wetBulb, 2); Serial.print(",");
  Serial.print(humidex, 2); Serial.print(",");
  Serial.println(enthalpy, 2);

  delay(2000); // Wait before next read
}
