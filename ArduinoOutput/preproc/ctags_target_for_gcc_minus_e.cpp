# 1 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino"
# 2 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino" 2
# 3 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino" 2
# 4 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino" 2
# 5 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino" 2
# 6 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino" 2
# 7 "/home/trond/source/WeatherStation2.0/WeatherStation2.0/readsensor.ino" 2

// Setting various constants for connectivity
const char *ssid = "Telenor1289bag";
const char *passwd = "Medferd5Leksikonartikkel4";
const char *serverName = "http://myprojectblog.ddns.net/post-esp-data.php";

// Creating BME280 sensor object
Adafruit_BME280 bme;



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
