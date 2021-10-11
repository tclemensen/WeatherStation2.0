# 1 "/home/trond/source/WeatherStation2.0/readsensor.ino"
// It is assumed that you are using a ESP8266 board. For other boards, be aware some of these includes will be different
// Change to suit your own needs

# 5 "/home/trond/source/WeatherStation2.0/readsensor.ino" 2
# 6 "/home/trond/source/WeatherStation2.0/readsensor.ino" 2
# 7 "/home/trond/source/WeatherStation2.0/readsensor.ino" 2
# 8 "/home/trond/source/WeatherStation2.0/readsensor.ino" 2
# 9 "/home/trond/source/WeatherStation2.0/readsensor.ino" 2
# 10 "/home/trond/source/WeatherStation2.0/readsensor.ino" 2

// Setting various constants for connectivity
const char *ssid = "Telenor1289bag";
const char *passwd = "Medferd5Leksikonartikkel4";
const char *serverName = "http://myprojectblog.ddns.net/post-sensor-data.php";

String apiKeyValue = "hMRc34aXPaEMfByV";

String sensorName = "BME280";
String sensorLocation = "Test";

// Creating BME280 sensor object, communicating with I2C
Adafruit_BME280 bme;



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

    /* Attempting to start Wifi

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

    */
# 55 "/home/trond/source/WeatherStation2.0/readsensor.ino"
    startWiFi();
    delay(1000);
}

void loop()
{

    // readSensors();
    startWiFi();
    delay(1000);
    readSensors();
    delay(1000);
    stopWiFi();
    delay(30000);
}

void readSensors()
{

    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure();

    Serial.println("If you can see this - it works thus far");

    WiFiClient client;
    HTTPClient http;

    Serial.println("Wificlient and httpclient initialised");

    http.begin(client, serverName);

    Serial.println("HTTP Begin Successful!");

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
        Serial.print(". ");
    }

    // Displaying Wifi info to serial console.
    Serial.println("");
    Serial.println("WiFi Connected!");
    Serial.print("Device IP : ");
    Serial.println(WiFi.localIP());

    delay(100);
    if (WiFi.status() == WL_CONNECTED)
    {
        // readSensors();
        Serial.println("If you see this, then WiFi is Connected!");
    }
    else
    {
        Serial.println("WiFi connection failed!");
    }
}

void stopWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        WiFi.mode(WIFI_OFF);
        WiFi.forceSleepBegin();
        Serial.println("WiFi is down");
    }
}
