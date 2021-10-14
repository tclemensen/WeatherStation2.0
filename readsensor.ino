// It is assumed that you are using a ESP8266 board. For other boards, be aware some of these includes will be different
// Change to suit your own needs

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

// Setting various constants for connectivity
const char *ssid = "Telenor1289bag";
const char *passwd = "Medferd5Leksikonartikkel4";
const char *serverName = "http://myprojectblog.ddns.net/post-sensor-data.php";

String apiKeyValue = "hMRc34aXPaEMfByV";

String sensorName = "BME280";
String sensorLocation = "Test";

// Creating BME280 sensor object, communicating with I2C
Adafruit_BME280 bme;

#define SEALEVELPRESSURE_HPA (1013.25) // Defined standard sea level pressure.

void setup()
{
    // Initialising serial port
    Serial.begin(115200);
    delay(100);

    // Attempting to start the BME280 sensor at I2C address 0x76
    bool status = bme.begin(0x76);
    if (!status)
    {
        Serial.println("No BME280 sensor found. Check wiring!");
    }

    startWiFi();
    delay(1000);
}

void loop()
{
    startWiFi();
    delay(1000);
    readSensors();
    delay(1000);
    stopWiFi();
    delay(30000);
}

void readSensors()
{
    WiFiClient client;
    HTTPClient http;

    http.begin(client, serverName);

    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation + "&temperature=" + String(bme.readTemperature()) + "&humidity=" + String(bme.readHumidity()) + "&pressure=" + String(bme.readPressure() / 100.0F) + "";

    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);

    if (httpResponseCode > 0)
    {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
    }
    else
    {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }

    // Free resources
    http.end();
}

void startWiFi()
{
    // This is probably not the best way of doing this
    // More research is needed.

    WiFi.begin(ssid, passwd);
    Serial.print("Initialising ");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(". "); // Just pushing some .... to the serial console to indicate that something is happening...
    }

    // Displaying Wifi info to serial console.
    Serial.println("");
    Serial.println("WiFi Connected!");
    Serial.print("Device IP : ");
    Serial.println(WiFi.localIP());

    delay(100);
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("If you see this, then WiFi is Connected!");
    }
    else
    {
        Serial.println("WiFi connection failed!");
    }
}

void stopWiFi()
{
    // Puts the ESP8266 into "Modem Sleep" powersaving mode.

    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.mode(WIFI_OFF);
        WiFi.forceSleepBegin();
        Serial.println("WiFi is down");
    }
}