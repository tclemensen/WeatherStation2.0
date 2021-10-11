# 1 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino"
// It is assumed that you are using a ESP8266 board. For other boards, be aware some of these includes will be different
// Change to suit your own needs

# 5 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino" 2
# 6 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino" 2
# 7 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino" 2
# 8 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino" 2
# 9 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino" 2
# 10 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino" 2

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
    /*

    //Check WiFi connection status

    if (WiFi.status() == WL_CONNECTED)

    {

        WiFiClient client;

        HTTPClient http;



        // Your Domain name with URL path or IP address with path

        http.begin(client, serverName);



        // Specify content-type header

        http.addHeader("Content-Type", "application/x-www-form-urlencoded");



        // Prepare your HTTP POST request data

        String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName + "&location=" + sensorLocation + "&temperature=" + String(bme.readTemperature()) + "&humidity=" + String(bme.readHumidity()) + "&pressure=" + String(bme.readPressure() / 100.0F) + "";

        Serial.print("httpRequestData: ");

        Serial.println(httpRequestData);



        // You can comment the httpRequestData variable above

        // then, use the httpRequestData variable below (for testing purposes without the BME280 sensor)

        //String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&temperature=24.75&humidity=49.54&pressure=1005.14";



        // Send HTTP POST request

        int httpResponseCode = http.POST(httpRequestData);



        // If you need an HTTP request with a content type: text/plain

        //http.addHeader("Content-Type", "text/plain");

        //int httpResponseCode = http.POST("Hello, World!");



        // If you need an HTTP request with a content type: application/json, use the following:

        //http.addHeader("Content-Type", "application/json");

        //int httpResponseCode = http.POST("{\"temperature\":\"19\",\"humidity\":\"67\",\"pressure\":\"78\"}");



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

    else

    {

        Serial.println("WiFi Disconnected");

    }

    //Send an HTTP POST request every 30 seconds */
# 109 "/home/trond/Source/Arduino/WeatherStation2.0/readsensor.ino"
    readSensors();
    delay(30000);
}

void readSensors()
{

    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure();

    if (WiFi.status() == WL_CONNECTED)
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
}
