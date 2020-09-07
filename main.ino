#include <SparkFunESP8266WiFi_KMU.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <PMS.h>
#include <Adafruit_BME280_KMU.h>

#define SSID "WiFi 모듈이 연결 돼 있는 WiFi 이름"    // wifi ssid
#define PASSWORD "해당 WiFi 비밀번호"             // wifi password
#define SENSOR_NAME "AirSensor본인학번" /*AirSensor<<학번>>*/
#define HOST_NAME "api.thingspeak.com"
#define HOST_PORT (80)
#define API_KEY "api키 복사해서 붙여넣기"
#define WAIT (300000) //5분

#define DEBUG // 주석시 시리얼출력 없음.

ESP8266Client client;

SoftwareSerial Serial_dust(10, 11);
PMS Pms(Serial_dust);
PMS::DATA Data;

Adafruit_BME280 Bme; // I2C

float _temperature = 0;
float _humidity = 0;
float _pressure = 0;
unsigned int _pm1_0 = 0; //pm1.0
unsigned int _pm2_5 = 0; //pm2.5
unsigned int _pm10 = 0;  //pm10

void setup()
{
    // 데이터 전송성공실패 유무 led
    pinMode(LED_BUILTIN, OUTPUT);

#ifdef DEBUG
    Serial.begin(9600);
#endif

    dust_init();
    bme_init();

    wifi_init();
    connect_wifi();

#ifdef DEBUG
    displayConnectInfo();
#endif

    delay(1000);
}

void loop()
{

    read_dust();
    read_bme();

    send_data();

#ifdef DEBUG
    Serial.println(F("---------------------"));
#endif

    delay(WAIT);
}

void dust_init()
{
    Serial_dust.begin(9600);
    Serial_dust.listen();
    Pms.passiveMode(); // Switch to passive mode
    Pms.wakeUp();
}

void bme_init()
{
    Bme.begin();
}

void wifi_init()
{
    // esp8266.begin() verifies that the ESP8266 is operational
    // and sets it up for the rest of the sketch.
    // It returns either true or false -- indicating whether
    // communication was successul or not.
    // true
    int test = esp8266.begin();
    if (test != true)
    {

#ifdef DEBUG
        Serial.println(F("Error talking to ESP8266."));
#endif
        errorLoop(test);
    }

#ifdef DEBUG
    Serial.println(F("ESP8266 Shield Present"));
#endif
}

void connect_wifi()
{
    // The ESP8266 can be set to one of three modes:
    //  1 - ESP8266_MODE_STA - Station only
    //  2 - ESP8266_MODE_AP - Access point only
    //  3 - ESP8266_MODE_STAAP - Station/AP combo
    // Use esp8266.getMode() to check which mode it's in:
    int retVal = esp8266.getMode();
    if (retVal != ESP8266_MODE_STA)
    { // If it's not in station mode.
        // Use esp8266.setMode([mode]) to set it to a specified
        // mode.
        retVal = esp8266.setMode(ESP8266_MODE_STA);
        if (retVal < 0)
        {

#ifdef DEBUG
            Serial.println(F("Error setting mode."));
#endif
            errorLoop(retVal);
        }
    }

#ifdef DEBUG
    Serial.println(F("Mode set to station"));
#endif

    // esp8266.status() indicates the ESP8266's WiFi connect
    // status.
    // A return value of 1 indicates the device is already
    // connected. 0 indicates disconnected. (Negative values
    // equate to communication errors.)
    retVal = esp8266.status();
    if (retVal <= 0)
    {

#ifdef DEBUG
        Serial.print(F("Connecting to "));
        Serial.println(SSID);
#endif
        // esp8266.connect([ssid], [psk]) connects the ESP8266
        // to a network.
        // On success the connect function returns a value >0
        // On fail, the function will either return:
        //  -1: TIMEOUT - The library has a set 30s timeout
        //  -3: FAIL - Couldn't connect to network.
        retVal = esp8266.connect(SSID, PASSWORD);
        if (retVal < 0)
        {

#ifdef DEBUG
            Serial.println(F("Error connecting"));
#endif
            errorLoop(retVal);
        }
    }
}

void displayConnectInfo()
{
    char connectedSSID[24];
    memset(connectedSSID, 0, 24);
    // esp8266.getAP() can be used to check which AP the
    // ESP8266 is connected to. It returns an error code.
    // The connected AP is returned by reference as a parameter.
    int retVal = esp8266.getAP(connectedSSID);
    if (retVal > 0)
    {
        Serial.print(F("Connected to: "));
        Serial.println(connectedSSID);
    }

    // esp8266.localIP returns an IPAddress variable with the
    // ESP8266's current local IP address.
    IPAddress myIP = esp8266.localIP();
    Serial.print(F("My IP: "));
    Serial.println(myIP);
}

void read_dust()
{
    Serial_dust.listen();
    Pms.requestRead();
    if (Pms.readUntil(Data))
    {
        _pm1_0 = Data.PM_SP_UG_1_0;
        _pm2_5 = Data.PM_SP_UG_2_5;
        _pm10 = Data.PM_SP_UG_10_0;
#ifdef DEBUG
        Serial.print(F("PM 1.0 (ug/m3)SP: "));
        Serial.println(Data.PM_SP_UG_1_0);

        Serial.print(F("PM 2.5 (ug/m3)SP: "));
        Serial.println(Data.PM_SP_UG_2_5);

        Serial.print(F("PM 10.0 (ug/m3)SP: "));
        Serial.println(Data.PM_SP_UG_10_0);

        Serial.println();
#endif
    }
    else
    {
        _pm1_0 = 0;
        _pm2_5 = 0;
        _pm10 = 0;
#ifdef DEBUG
        Serial.println(F("PMS No data."));
#endif
    }
}

void read_bme()
{
    _temperature = Bme.readTemperature();
    _humidity = Bme.readHumidity();
    _pressure = (Bme.readPressure() / 100.0F);

#ifdef DEBUG
    Serial.print(F("Temperature: "));
    Serial.print(Bme.readTemperature());
    Serial.println(" *C");
    Serial.print(F("Pressure: "));
    Serial.print(Bme.readPressure() / 100.0F);
    Serial.println(F(" hPa"));
    Serial.print(F("Humidity: "));
    Serial.print(Bme.readHumidity());
    Serial.println(F(" %"));
#endif
}

void send_data()
{

    int retVal = client.connect(HOST_NAME, HOST_PORT);
    if (retVal <= 0)
    {
        Serial.println(F("Failed to connect to server."));
        digitalWrite(LED_BUILTIN, LOW); // 서버 연결실패시 led 꺼짐
        return;
    }
    digitalWrite(LED_BUILTIN, HIGH); // 서버 연결성공시 led 켜짐
    
    char param_tem[20];
    char param_hum[20];
    char param_pre[20];
    char param_pm1[20];
    char param_pm2_5[20];
    char param_pm10[20];
    
    dtostrf(_temperature, 4, 2, param_tem);
    dtostrf(_humidity, 4, 2, param_hum);
    dtostrf(_pressure, 5, 2, param_pre);
    
    char *paramTpl = "?api_key=%s&field1=%s&field2=%s&field3=%s&field4=%d&field5=%d&field6=%d"; //보낼 필드명 정의
    char param[100];                                                                            //param 사이즈 크기 정의
    sprintf(param, paramTpl, API_KEY, param_tem, param_hum, param_pre, _pm1_0, _pm2_5, _pm10);
    Serial.println(param);

    // This will send the request to the server
    char *headerTpl = "GET /update%s HTTP/1.1\r\n"
                      "Host: %s\r\n"
                      "Cache-Control: no-cache\r\n"
                      "Content-length: 0\r\n\r\n";
    char header[220]; //header 사이즈 크기 정의
    sprintf(header, headerTpl, param, HOST_NAME);

    // This will send the request to the server
    client.print(header);

    // 서버에서 리턴되는 결과 출력
    //  while (client.available())
    //    Serial.write(client.read()); // read() gets the FIFO char

    if (client.connected())
        client.stop(); // stop() closes a TCP connection.
}

// errorLoop prints an error code, then loops forever.
void errorLoop(int error)
{
    Serial.print(F("Error: "));
    Serial.println(error);
    Serial.println(F("Looping forever."));
    for (;;)
        ;
}
