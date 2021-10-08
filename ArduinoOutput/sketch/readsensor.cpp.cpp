#include <Arduino.h>
#line 1 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.cpp"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Setting various constants for connectivity
const char *ssid = "ENTER_YOUR_SSID_HERE";
const char *passwd = "ENTER_YOUR_WIFI_PASSWORD_HERE";
const char *serverName = "http://EXAMPLE.NET/post-esp-data.php";

// Creating BME280 sensor object
Adafruit_BME280 bme;

#define SEALEVELPRESSURE_HPA (1013.25)

void setup()
{
    // Initialising serial port
    Serial.begin(115200);
    delay(100);

    // Attempting to start the BME280 sensor
    bool status = bme.begin(0x76);
    if (!status)
    {
        Serial.println("No BME280 sensor found. Check wiring!");
    }

    // Attempting to start Wifi
    WiFi.begin(ssid, passwd);
    Serial.print("Initialising ");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(". ");
    }

    // Displaying Wifi info to serial console.
    Serial.println("");
    Serial.println("WiFi Connected!");
    Serial.print("Device IP : ");
    Serial.println(WiFi.localIP());
}

void loop()
{
    delay(30000);
    readSensors();
}

void readSensors()
{
    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure();
}
